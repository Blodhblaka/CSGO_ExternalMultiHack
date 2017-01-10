#include "EntityList.h"



EntityList::EntityList(MemoryManagment *Mem)
	:Mem(Mem)
{
	local = LocalPlayer(Mem, Mem->Read<DWORD>(Mem->clientModuleBase + Offsets::LocalPlayer));
	for (int i = 0; i < 64; i++)
	{
		players[i] = Player(Mem, Mem->Read<DWORD>(Mem->clientModuleBase + Offsets::EntityList + ((i - 1) * 0x10)));
	}
}


EntityList::~EntityList()
{
}

void EntityList::ReloadEntities()
{
	local = LocalPlayer(Mem, Mem->Read<DWORD>(Mem->clientModuleBase + Offsets::LocalPlayer));
	for (int i = 0; i < 64 ; i++)
	{
		players[i] = Player(Mem, Mem->Read<DWORD>(Mem->clientModuleBase + Offsets::EntityList + ((i - 1) * 0x10)));
	}
}
