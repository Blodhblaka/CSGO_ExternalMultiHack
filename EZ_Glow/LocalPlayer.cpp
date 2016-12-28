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
