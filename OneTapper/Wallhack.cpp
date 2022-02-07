#pragma once 

#include "Wallhack.h"
#include "Offsets.h"
#include "LocalPlayer.h"

void RunWallHack()
{
	DWORD cliendModule = (DWORD)(GetModuleHandle(L"client.dll"));
	DWORD localPlayer = *(DWORD*)LocalPlayer::Get();
	DWORD glowObjectManager = *(DWORD*)(cliendModule + hazedumper::signatures::dwGlowObjectManager);
	DWORD entityList = *(DWORD*)(cliendModule + hazedumper::signatures::dwEntityList);

	int localTeam = *(int*)(localPlayer + hazedumper::netvars::m_iTeamNum);

	for (int ctr = 0; ctr < 32; ++ctr) 
	{
		DWORD entity = *(DWORD*)((entityList) + ctr + 0x10);

		if (entity == NULL)
			continue;

		int glowIndex = *(int*)(entity + hazedumper::netvars::m_iGlowIndex);
		int entityTeam = *(int*)(entity + hazedumper::netvars::m_iTeamNum);

		if (entityTeam == localTeam)  
		{
			*(float*)(glowObjectManager + glowIndex * 0x38 + 0x4) = 0.f; 
			*(float*)(glowObjectManager + glowIndex * 0x38 + 0x8) = 1.f;
			*(float*)(glowObjectManager + glowIndex * 0x38 + 0xC) = 0.f;
			*(float*)(glowObjectManager + glowIndex * 0x38 + 0x10) = 1.7f;
		}
		else 
		{
			*(float*)(glowObjectManager + glowIndex * 0x38 + 0x4) = 1.f;
			*(float*)(glowObjectManager + glowIndex * 0x38 + 0x8) = 0.f;
			*(float*)(glowObjectManager + glowIndex * 0x38 + 0xC) = 1.7f;
			*(float*)(glowObjectManager + glowIndex * 0x38 + 0x10) = 0.f;
		}

		*(bool*)(glowObjectManager + glowIndex * 0x38 + 0x24) = true;
		*(bool*)(glowObjectManager + glowIndex * 0x38 + 0x25) = false;

	}
};