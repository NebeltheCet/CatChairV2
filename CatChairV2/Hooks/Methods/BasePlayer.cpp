#include "../Hooks.hpp"
#include <stdio.h>

void Hooks::Methods::hkClientInput(BasePlayer* _this, InputState* inputState) {
	printf("function call[%s]\n", __FUNCTION__);
	if (!_this)
		return _this->oClientInput(_this, inputState);

	_this->oClientInput(_this, inputState);
}