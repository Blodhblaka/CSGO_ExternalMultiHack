#pragma once
#include "EntityList.h"
#include "CSGO_Structs.h"
#include <Windows.h>
#include "Options.h"
#include "Utils.h"
#include <map>

using namespace std;

//TODO: Move this enum somewhere
enum GLOW_MODE
{
	NONE,
	SOLID_COLOR,
	HEALTH_BASED_COLOR
};

std::map<GLOW_MODE, char*> glowModeMap;

void Shoot()
{
	mouse_event(MOUSEEVENTF_LEFTDOWN, NULL, NULL, NULL, NULL);
	Sleep(10);
	mouse_event(MOUSEEVENTF_LEFTUP, NULL, NULL, NULL, NULL);
}


namespace Threads {

	//TODO: Synchronize these threads

	void Update(EntityList *EntList)
	{
		while (true) {
			EntList->ReloadEntities();
			if (GetAsyncKeyState(VK_F7) & 1) {
				Options::glowMode++;
				if (Options::glowMode > 2)
					Options::glowMode = 0;
				cout << "Glow mode: " << glowModeMap[(GLOW_MODE)Options::glowMode] << endl;
			}
			Sleep(50);
		}
	}

	void Trigger(EntityList *EntList) 
	{
		while (true) {
			if (GetAsyncKeyState(0x4) & 0x8000)
				if (EntList->local.GetCrossId() > 0 && EntList->local.GetCrossId() < 64)
					if (EntList->local.GetTeam() != EntList->players[EntList->local.GetCrossId()].GetTeam())
						Shoot();

			Sleep(50);
		}
	}

	void Glow(EntityList *EntList, MemoryManagment *Mem)
	{
		while (true) {
			while (Options::glowMode == GLOW_MODE::NONE)
				Sleep(200);

			DWORD glowManagerBase = Mem->Read<DWORD>(Mem->clientModuleBase + Offsets::ObjBase);
			for (int i = 0; i < 64; i++)
			{
				if (!EntList->players[i].GetDormant() && EntList->players[i].IsAlive() && EntList->players[i].GetIndex() != EntList->local.GetIndex())
				{
					DWORD addr = glowManagerBase + (EntList->players[i].GetGlowIndex() * 0x38 + 4);
					glow_t originalGlowObj = Mem->Read<glow_t>(addr);
					if(Options::glowMode == GLOW_MODE::SOLID_COLOR)
						originalGlowObj.color = EntList->players[i].GetTeam() == EntList->local.GetTeam() ? Color(0, 0, 1, 1) : Color(1, 0, 0, 1);
					else 
						originalGlowObj.color = EntList->players[i].GetTeam() == EntList->local.GetTeam() ? Color(0, 0, 1, 1) : Color((255 - EntList->players[i].GetHealth() * 2.55f) / 255, (EntList->players[i].GetHealth() * 2.55f) / 255, 0, 1);
					originalGlowObj.m_bRenderWhenOccluded = true;
					Mem->Write(addr, originalGlowObj);
				}
			}
			Sleep(1);
		}
	}

	void Misc(EntityList *EntList) 
	{
		while (true) {

			if (Options::noFlash)
				EntList->local.SetFlashDuration(0.f);

			if (Options::bHop) 
				if (GetAsyncKeyState(VK_SPACE) & 0x8000) {
					if (!(EntList->local.GetFlags() & (int)EntityFlags::FL_ONGROUND))
						EntList->local.SetJump(4);
					else EntList->local.SetJump(5);
				}

			if(Options::radar)
				for each (Player player in EntList->players)
				{
					if (player.GetIndex() == EntList->local.GetIndex())
						continue;

					if (!player.IsAlive())
						continue;

					if (player.GetDormant())
						continue;

					player.SetSpotted(true);
				}


			Sleep(5);
		}
	}

	void Aimbot(EntityList* EntList)
	{
		while (true) {
			if (GetAsyncKeyState(VK_MENU) & 0x8000)
			{
				Vector bestAimAngle;
				float bestFov = Options::aimbotFov;

				for each (Player player in EntList->players)
				{
					if (player.GetIndex() == EntList->local.GetIndex())
						continue;

					if (!player.IsAlive())
						continue;

					if (player.GetDormant())
						continue;

					if (player.GetTeam() == EntList->local.GetTeam())
						continue;

					Vector headPosition = player.GetBonePosition(8);
					
					if (headPosition.IsEmpty())
						continue;

					Vector aimAngle;
					Utils::CalcAngle(EntList->local.GetEyePosition(), headPosition, aimAngle);

					float fov = Utils::GetFov(EntList->local.GetViewAngles(), aimAngle);

					if (fov < bestFov) {
						bestAimAngle = aimAngle;
						bestFov = fov;
					}
				}


				if (!bestAimAngle.IsEmpty()) {
					Vector newViewAngles;
					Utils::Clamp(bestAimAngle);
					
					Vector delta = EntList->local.GetViewAngles() - bestAimAngle;
					Utils::Clamp(delta);


					newViewAngles = EntList->local.GetViewAngles() - delta / Options::smoothFactor;
					
					if(Utils::Clamp(newViewAngles))
						EntList->local.SetViewAngles(newViewAngles);
				}
			}

			Sleep(1);
		}
	}

	void Init(MemoryManagment *Mem) {
		cout << "> Updating Offsets!" << endl;
		Offsets::UpdateOffsets(Mem);
		cout << "> Done Enjoy!" << endl;

		glowModeMap[NONE] = "None";
		glowModeMap[SOLID_COLOR] = "Solid";
		glowModeMap[HEALTH_BASED_COLOR] = "Health";

		EntityList EntList(Mem);

		thread UpdateThread(Update, &EntList);
		thread TriggerThread(Trigger, &EntList);
		thread GlowThread(Glow, &EntList, Mem);
		thread MiscThread(Misc, &EntList);
		thread AimbotThread(Aimbot, &EntList);

		UpdateThread.join();
	}

}