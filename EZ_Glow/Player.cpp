#include "Player.h"



Player::Player(MemoryManagment *Mem, DWORD BaseAddr)
	: BaseEntity(Mem, BaseAddr)
{
}

Player::Player()
{
}


Player::~Player()
{
}

int Player::GetHealth()
{
	if (health == -1)
		health = Mem->Read<int>(BaseAddr + Offsets::health);
	return health;
}

float Player::GetFlashDuration()
{
	if (flashDuration == -1)
		flashDuration = Mem->Read<float>(BaseAddr + Offsets::flashDuration);
	return flashDuration;
}

int Player::GetGlowIndex()
{
	if (glowIndex == -1)
		glowIndex = Mem->Read<int>(BaseAddr + Offsets::glowIndex);
	return glowIndex;
}

void Player::SetFlashDuration(float value)
{
	Mem->Write<float>(BaseAddr + Offsets::flashDuration, value);
}


bool Player::IsAlive() {
	return GetHealth() > 0;
}

