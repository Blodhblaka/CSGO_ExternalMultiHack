#include "LocalPlayer.h"



LocalPlayer::LocalPlayer(MemoryManagment *Mem, DWORD BaseAddr)
	: Player(Mem, BaseAddr)
{
}

LocalPlayer::LocalPlayer()
{
}


LocalPlayer::~LocalPlayer()
{
}

int LocalPlayer::GetCrossId()
{
	if (crossId == -1)
		crossId = Mem->Read<int>(BaseAddr + Offsets::crossId);
	return crossId;
}

int LocalPlayer::GetFlags()
{
	if (flags == -1)
		flags = Mem->Read<int>(BaseAddr + Offsets::flags);
	return flags;
}

void LocalPlayer::SetJump(int value) {
	Mem->Write<int>(Mem->clientModuleBase + Offsets::forceJump, value);
}

Vector LocalPlayer::GetViewAngles()
{
	if (viewAngles.IsEmpty()) {
		if (clientState == 0)
			clientState = Mem->Read<DWORD>(Mem->engineModuleBase + Offsets::clientState);
		viewAngles = Mem->Read<Vector>(clientState + Offsets::viewAngles);
	}
	return viewAngles;
}

void LocalPlayer::SetViewAngles(Vector viewAngles)
{
	if (clientState == 0)
		clientState = Mem->Read<DWORD>(Mem->engineModuleBase + Offsets::clientState);
	Mem->Write<Vector>(clientState + Offsets::viewAngles, viewAngles);
}
