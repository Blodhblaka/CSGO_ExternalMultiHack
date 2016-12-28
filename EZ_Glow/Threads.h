#pragma once
#include "EntityList.h"
#include "CSGO_Structs.h"
#include <Windows.h>
#include "Options.h"
#include <map>

using namespace std;

//TODO: Move this enum somewhere
enum GLOW_MODE
{
	NONE,
	SOLID_COLOR,
	HEALTH_BASED_COLOR
};

std::map<GLOW_MODE, char*> m;

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
				std::cout << "Glow mode: " << m[(GLOW_MODE)Options::glowMode] << endl;
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

	void Init(MemoryManagment *Mem) {
		cout << "> Updating Offsets!" << endl;
		Offsets::UpdateOffsets(Mem);
		cout << "> Done Enoy!" << endl;

		m[NONE] = "None";
		m[SOLID_COLOR] = "Solid";
		m[HEALTH_BASED_COLOR] = "Health";

		EntityList EntList(Mem);

		thread UpdateThread(Update, &EntList);
		thread TriggerThread(Trigger, &EntList);
		thread GlowThread(Glow, &EntList, Mem);

		UpdateThread.join();
	}

}