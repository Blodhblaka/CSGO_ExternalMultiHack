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
	SetConsoleTitle("Blod's multihack cpp edition");
	MemoryManagment Mem("csgo.exe");
	cout << "> Waiting for csgo!" << endl;

	while (!Mem.Initialize()) {
		Sleep(300);
	}
	Threads::Init(&Mem);
	return 0;
}

