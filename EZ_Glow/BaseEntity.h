#pragma once
#include "MemoryManagment.h"
#include "Vector.h"
#include "Offsets.h"

class BaseEntity
{
public:
	BaseEntity(MemoryManagment* Mem, DWORD BaseAddr);
	BaseEntity();
	~BaseEntity();

	int GetIndex();
	int GetTeam();
	Vector GetPosition();
	bool GetDormant();

	void SetSpotted(bool value);

protected:
	MemoryManagment *Mem;
	DWORD BaseAddr;
	int index = -1;
	int team = -1;
	bool dormant;
	Vector position;

};

