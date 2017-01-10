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

void Player::SetSpotted(bool value)
{
	Mem->Write<bool>(BaseAddr + Offsets::bSpotted, value);
}


bool Player::IsAlive() {
	return GetHealth() > 0;
}

Vector Player::GetBonePosition(int boneId)
{
	Vector bone;
	DWORD boneMatrix = Mem->Read<DWORD>(BaseAddr + Offsets::boneMatrix);

	bone.x = Mem->Read<float>(boneMatrix + (0x30 * boneId) + 0x0C);
	bone.y = Mem->Read<float>(boneMatrix + (0x30 * boneId) + 0x1C);
	bone.z = Mem->Read<float>(boneMatrix + (0x30 * boneId) + 0x2C);
	return bone;
}

Vector Player::GetEyePosition()
{
	if (eyePosition.IsEmpty()) {
		eyePosition = GetPosition();
		eyePosition.z += Mem->Read<Vector>(BaseAddr + Offsets::viewOffset).z;
	}
	return eyePosition;
}

