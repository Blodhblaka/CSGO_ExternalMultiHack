#pragma once
#include "MemoryManagment.h"
#include "BaseEntity.h"
#include "Player.h"
#include "LocalPlayer.h"


class EntityList
{
public:
	EntityList(MemoryManagment *Mem);
	~EntityList();

	void ReloadEntities();

	LocalPlayer local;
	Player players[64];
private:
	MemoryManagment *Mem;
};

