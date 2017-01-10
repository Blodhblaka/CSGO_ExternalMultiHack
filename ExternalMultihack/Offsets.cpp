#include "Offsets.h"

namespace Offsets {

	 DWORD LocalPlayer;
	 DWORD ObjBase;
	 DWORD EntityList;


	 DWORD health = 0xFC;
	 DWORD teamNum = 0xF0;
	 DWORD dormant = 0xE9;
	 DWORD bSpotted = 0x939;
	 DWORD index = 0x64;
	 DWORD vecOrigin = 0x134;
	 DWORD flashDuration = 0xA308;
	 DWORD crossId = 0xAA70;
	 DWORD glowIndex = 0xA320;
	 DWORD flags = 0x100;
	 DWORD forceJump = 0x4F5EB58;
	 DWORD boneMatrix = 0x2698;
	 DWORD viewOffset = 0x104;
	 DWORD clientState = 0x5C7524;
	 DWORD viewAngles = 0x4D0C;


	void GetLocalPlayer(MemoryManagment *mem)
	{
		DWORD Addr = mem->FindPattern("\xA3\x00\x00\x00\x00\xC7\x05\x00\x00\x00\x00\x00\x00\x00\x00\xE8\x00\x00\x00\x00\x59\xC3\x6A", "x????xx????????x????xxx", mem->clientModuleBase, mem->clientModuleSize) + 1;
		LocalPlayer = mem->Read<DWORD>(mem->clientModuleBase + Addr) - mem->clientModuleBase + 0x2C;
	}

	void GetObjectBase(MemoryManagment *mem)
	{
		DWORD Addr = mem->FindPattern("\xE8\x00\x00\x00\x00\x83\xC4\x04\xB8\x00\x00\x00\x00\xC3\xcc", "x????xxxx????xx", mem->clientModuleBase, mem->clientModuleSize) + 9;
		ObjBase = mem->Read<DWORD>(mem->clientModuleBase + Addr) - mem->clientModuleBase;
	}

	void GetEntityList(MemoryManagment *mem)
	{
		DWORD Addr = mem->FindPattern("\xBB\x00\x00\x00\x00\x83\xFF\x01\x0F\x8C\x00\x00\x00\x00\x3B\xF8", "x????xxxxx????xx", mem->clientModuleBase, mem->clientModuleSize) + 1;
		EntityList = mem->Read<DWORD>(mem->clientModuleBase + Addr) - mem->clientModuleBase;
	}

	void UpdateOffsets(MemoryManagment *mem)
	{
		GetLocalPlayer(mem);
		GetObjectBase(mem);
		GetEntityList(mem);
	}
}