#include <windows.h>
#include <iostream>

#include "Hack.h"
#include "Wallhack.h"

BOOL isAimBotOn = false;
BOOL isWallHackOn = false;

DWORD WINAPI MainThread(PVOID base) 
{
	while (!(GetAsyncKeyState(VK_DELETE) & 0x8000))
	{
		if (GetAsyncKeyState(VK_NUMPAD1) & 0x8000)
			isAimBotOn = !isAimBotOn;

		if (GetAsyncKeyState(VK_NUMPAD2) & 0x8000)
			isWallHackOn = !isWallHackOn;

		if (isAimBotOn) 
		{
			Run();
		}

		if (isWallHackOn) 
		{
			RunWallHack();
		}

		Sleep(1);
	}
	FreeLibraryAndExitThread(static_cast<HMODULE>(base), 0);
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH) 
	{
		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE) MainThread, hModule, NULL, NULL);
	}
	return TRUE;
}