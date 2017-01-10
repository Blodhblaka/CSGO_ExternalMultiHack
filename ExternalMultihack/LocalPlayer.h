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
	int GetFlags();

	void SetJump(int value);
	Vector GetViewAngles();
	void SetViewAngles(Vector viewAngles);
protected:
	int crossId = -1;
	int flags = -1;
	Vector viewAngles;
	DWORD clientState = 0;
};

