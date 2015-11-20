#pragma once
#include "Component.h"
/*
This component type is dependant on the objects transform, for example:
	-Text rendering
	-Sprite rendering
	-Physics component, like a collision box
*/
class TransformableComponent : public Component
{
public:
	TransformableComponent();
	~TransformableComponent();

protected:
	Transform* transform;
};