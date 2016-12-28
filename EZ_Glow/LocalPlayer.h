#pragma once
#include "Player.h"
class LocalPlayer :
	public Player
{
public:
	LocalPlayer(MemoryManagment *Mem, DWORD BaseAddr);
	LocalPlayer();
	~LocalPlayer();

	int GetCrossId();

protected:
	int crossId = -1;
};

