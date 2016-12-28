#pragma once
#include <Windows.h>
#include <tlhelp32.h>
#include <iostream>
#include <cstdlib>


class MemoryManagment
{
public:
	MemoryManagment(char* proccesName);
	~MemoryManagment();

	bool Initialize();
	DWORD FindPattern(char *pattern, char *mask, DWORD moduleBaseAddr, int moduleSize);

	template<class T>
	inline T Read(DWORD address);

	template<class T>
	inline void Write(DWORD address, T value);


	int clientModuleSize;
	DWORD clientModuleBase;
private:
	char* proccessName;
	HANDLE proccessHandle;
	int proccesId;

	HANDLE GetProcessByName();
	DWORD GetModuleBase(LPSTR lpModuleName, int* sizeOut);

};


template<class T>
T MemoryManagment::Read(DWORD address) {
	T temp;
	ReadProcessMemory(proccessHandle, (LPVOID)address, &temp, sizeof(T), NULL);
	return temp;
}

template<class T>
void MemoryManagment::Write(DWORD address, T value)
{
	WriteProcessMemory(proccessHandle, (LPVOID)address, &value, sizeof(T), NULL);
}