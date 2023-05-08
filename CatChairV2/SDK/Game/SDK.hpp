#pragma once
#include "Unity/UnityEngine.hpp"

class BaseNetworkable {
public:
	CLASS("", "BaseNetworkable");
	/* Originals */

	/* Fields */

	/* Methods */
};

class BaseEntity : public BaseNetworkable {
public:
	CLASS("", "BaseEntity");
	/* Originals */

	/* Fields */

	/* Methods */
};

class InputState {
public:
	CLASS("", "InputState");
	/* Originals */

	/* Fields */

	/* Methods */
};

class BaseCombatEntity : public BaseEntity {
public:
	CLASS("", "BaseCombatEntity");
	/* Originals */

	/* Fields */

	/* Methods */
};

class BasePlayer : public BaseCombatEntity {
public:
	CLASS("", "BasePlayer");
	/* Originals */
	static inline void(*oClientInput)(BasePlayer*, InputState*) = nullptr;

	/* Fields */
	MEMBER(int, userID);

	/* Methods */
};