// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"

std::atomic_bool Mod_running = true;
void Logger(const char* fmt, ...)
{
	printf(fmt);
}
DWORD WINAPI ControlThread(LPVOID lpParam)
{
	if (AllocConsole()) {
		freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);
		SetConsoleTitleW(L"" Mod_Menu_Name);
		SetConsoleCP(CP_UTF8);
		SetConsoleOutputCP(CP_UTF8);
	}
	Hooking::Start((HMODULE)lpParam); // this always loadng first



	while (Mod_running)
	{
		if (GetAsyncKeyState(VK_DELETE)) { Mod_running = false; }
	}

	Hooking::Cleanup();

}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ControlThread, hModule, NULL, NULL);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


