#pragma once
#include "../../Wrapper/Il2CPP/IL2CPP.hpp"

class Object {
public:
	CLASS("UnityEngine", "Object");
	/* Originals */

	/* Fields */

	/* Methods */
};

class GameObject : public Object {
public:
	CLASS("UnityEngine", "GameObject");
	/* Originals */

	/* Fields */

	/* Methods */
};

class Transform;
class Component : public Object {
public:
	CLASS("UnityEngine", "Component");
	/* Originals */

	/* Fields */

	/* Methods */
};

class Transform : public Component {
public:
	CLASS("UnityEngine", "Transform");
	/* Originals */

	/* Fields */

	/* Methods */
};