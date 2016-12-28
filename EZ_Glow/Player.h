#pragma once
#include "BaseEntity.h"
#include "CSGO_Structs.h"

class Player :
	public BaseEntity
{
public:
	Player(MemoryManagment *Mem, DWORD BaseAddr);
	Player();
	~Player();

	int GetHealth();
	float GetFlashDuration();
	int GetGlowIndex();
	bool IsAlive();

	void SetFlashDuration(float value);

protected:
	int health = -1;
	int glowIndex = -1;
	float flashDuration = -1;
};

