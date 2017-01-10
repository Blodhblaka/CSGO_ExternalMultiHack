#pragma once
#include <Windows.h>
#include "MemoryManagment.h"
namespace Offsets {
	extern DWORD LocalPlayer;
	extern DWORD ObjBase;
	extern DWORD EntityList;


	extern DWORD health;
	extern DWORD teamNum;
	extern DWORD dormant;
	extern DWORD bSpotted;
	extern DWORD index;
	extern DWORD vecOrigin;
	extern DWORD flashDuration;
	extern DWORD crossId;
	extern DWORD glowIndex;
	extern DWORD flags;
	extern DWORD forceJump;
	extern DWORD boneMatrix;
	extern DWORD viewOffset;
	extern DWORD clientState;
	extern DWORD viewAngles;

	extern void GetLocalPlayer(MemoryManagment *mem);
	extern void GetObjectBase(MemoryManagment *mem);
	extern void GetEntityList(MemoryManagment *mem);
	extern void UpdateOffsets(MemoryManagment *mem);
}
