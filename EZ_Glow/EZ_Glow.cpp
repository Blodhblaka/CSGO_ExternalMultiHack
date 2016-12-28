// EZ_Glow.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MemoryManagment.h"
#include "Offsets.h"
#include <iostream> 
#include <thread>
#include "Threads.h"

using namespace std;

int main()
{
	SetConsoleTitle(L"Merry Christmass :)");
	MemoryManagment Mem("csgo.exe");
	cout << "> Wainting for csgo!" << endl;

	while (!Mem.Initialize()) {
		Sleep(300);
	}
	Threads::Init(&Mem);
	return 0;
}

