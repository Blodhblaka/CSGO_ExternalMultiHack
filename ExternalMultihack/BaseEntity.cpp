#include "BaseEntity.h"



BaseEntity::BaseEntity(MemoryManagment *Mem, DWORD BaseAddr)
	: Mem(Mem), BaseAddr(BaseAddr)
{
}

BaseEntity::BaseEntity()
{
}


BaseEntity::~BaseEntity()
{
}

int BaseEntity::GetIndex()
{
	if (index == -1)
		index = Mem->Read<int>(BaseAddr + Offsets::index);
	return index;
}

int BaseEntity::GetTeam()
{
	if (team == -1)
		team = Mem->Read<int>(BaseAddr + Offsets::teamNum);
	return team;
}

Vector BaseEntity::GetPosition()
{
	if (position.IsEmpty())
		position = Mem->Read<Vector>(BaseAddr + Offsets::vecOrigin);
	return position;
}

bool BaseEntity::GetDormant()
{
	return Mem->Read<bool>(BaseAddr + Offsets::dormant);
}

void BaseEntity::SetSpotted(bool value)
{
	Mem->Write<bool>(BaseAddr + Offsets::bSpotted, value);
}


