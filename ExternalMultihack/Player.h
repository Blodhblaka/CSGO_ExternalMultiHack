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
	Vector GetBonePosition(int boneId);
	Vector GetEyePosition();

	void SetFlashDuration(float value);
	void SetSpotted(bool value);

protected:
	int health = -1;
	int glowIndex = -1;
	float flashDuration = -1;
	Vector eyePosition;
};

