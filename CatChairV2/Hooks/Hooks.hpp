#pragma once
#include "../SDK/Game/SDK.hpp"

namespace Hooks {
	namespace Methods {
		void hkClientInput(BasePlayer* _this, InputState* inputState);
	}

	namespace Custom {
		bool HookFunc(void* pTarget, void* pDetour, void** ppOriginal, const char* hookName);
	}

	void Load();
	void Unload();
}