#include <Windows.h>
#include <iostream>

#include "SDK/Utils/Console/Console.hpp"
#include "SDK/Wrapper/Il2CPP/IL2CPP.hpp"
#include "Hooks/Hooks.hpp"

void mainThread(LPVOID lpParam) {
    Console::AttachConsole();
    Il2CppWrapper::ThreadAttach();
    Hooks::Load();

    while (!GetAsyncKeyState(VK_END))
        Sleep(100);

    Hooks::Unload();
    //Il2CppWrapper::ThreadDetach(); /* Crashes */
    Console::DetachConsole();
    FreeLibraryAndExitThread(static_cast<HMODULE>(lpParam), EXIT_SUCCESS);
}

int __stdcall DllMain(HMODULE hModule, DWORD dwCallReason, LPVOID lpReserved) {
    if (dwCallReason == DLL_PROCESS_ATTACH) {
        if (HANDLE hThread = CreateThread(nullptr, NULL, (LPTHREAD_START_ROUTINE)mainThread, hModule, NULL, nullptr))
            CloseHandle(hThread);
    }

    return TRUE;
}

