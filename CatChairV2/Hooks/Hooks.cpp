#include "Hooks.hpp"
#include "../SDK/Libraries/MinHook/MinHook.h"
#include <stdio.h>
#include "../SDK/Wrapper/Il2CPP/IL2CPP.hpp"

bool Hooks::Custom::HookFunc(void* pTarget, void* pDetour, void** ppOriginal, const char* hookName) {
	MH_STATUS createStatus = MH_CreateHook(pTarget, pDetour, ppOriginal);
	if (createStatus != MH_OK) {
		printf("failed to hook %s[0x%p]\n", hookName, (uintptr_t)pTarget);
		return false;
	}

	printf("successfully hooked %s[0x%p]\n", hookName, (uintptr_t)pTarget);
	return true;
}

void Hooks::Load() {
	MH_Initialize();

	/* Hook Targets */
	void* clientInputTarget = *reinterpret_cast<void**>(Il2CppWrapper::GetClassFromName("", "BasePlayer")->GetMethodFromName("ClientInput"));

	/* Create Hooks */
	Custom::HookFunc(clientInputTarget, &Methods::hkClientInput, (void**)&BasePlayer::oClientInput, "hkClientInput");

	MH_EnableHook(MH_ALL_HOOKS);
}

void Hooks::Unload() {
	MH_DisableHook(MH_ALL_HOOKS);
	MH_RemoveHook(MH_ALL_HOOKS);

	MH_Uninitialize();
}