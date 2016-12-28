#include "MemoryManagment.h"


MemoryManagment::MemoryManagment(char* proccessName) :
	proccessName(proccessName)
{
	
}


MemoryManagment::~MemoryManagment()
{
}

bool MemoryManagment::Initialize() {
	if ((proccessHandle = GetProcessByName()) == NULL)
		return false;

	if ((clientModuleBase = GetModuleBase("client.dll", &clientModuleSize)) == NULL)
		return false;

	return true;
}

DWORD MemoryManagment::FindPattern(char *pattern, char *mask, DWORD moduleBaseAddr, int moduleSize)
{
	int patternSize = strlen(mask);
	char buffer[100];
	for (DWORD i = 0; i < moduleSize - patternSize; i++)
	{
		bool found = true;
		ReadProcessMemory(proccessHandle, (LPVOID)(moduleBaseAddr + i), &buffer, patternSize, NULL);
		for (int l = 0; l < patternSize; l++)
		{
			found = mask[l] == '?' || buffer[l] == pattern[l];
			if (!found)
				break;
		}

		if (found)
			return i;
	}
	return 0;
}

//Bit of a copy-paste ...New to C++ :!(
HANDLE MemoryManagment::GetProcessByName()
{
	DWORD pid = 0;

	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 process;
	ZeroMemory(&process, sizeof(process));
	process.dwSize = sizeof(process);

	if (Process32First(snapshot, &process))
	{
		do
		{
			char str[25];
			wcstombs(str, process.szExeFile, 25);
			if (_stricmp(str, proccessName) == 0)
			{
				pid = process.th32ProcessID;
				proccesId = pid;
				break;
			}
		} while (Process32Next(snapshot, &process));
	}

	CloseHandle(snapshot);

	if (pid != 0)
	{
		return OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	}



	return NULL;
}


DWORD MemoryManagment::GetModuleBase(LPSTR lpModuleName, int *sizeOut)
{
	MODULEENTRY32 lpModuleEntry = { 0 };
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, proccesId);
	if (!hSnapShot)
		return NULL;
	lpModuleEntry.dwSize = sizeof(lpModuleEntry);
	BOOL bModule = Module32First(hSnapShot, &lpModuleEntry);
	while (bModule)
	{
		char str[25];
		wcstombs(str, lpModuleEntry.szModule, 25);

		if (_stricmp(str, lpModuleName) == 0)
		{
			CloseHandle(hSnapShot);
			*sizeOut = lpModuleEntry.modBaseSize;
			return (DWORD)lpModuleEntry.modBaseAddr;
		}
		bModule = Module32Next(hSnapShot, &lpModuleEntry);
	}
	CloseHandle(hSnapShot);
	return NULL;
}

