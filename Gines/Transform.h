#pragma once

#include <glm/vec2.hpp>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>
#include "Component.h"

class Transform : public MonoComponent
{
public:
	Transform();
	~Transform(){};

	void update();

	//Rotate object relative to current rotation
	void rotateDeg(float degree);

	//Set absolute rotation
	void setRotationDeg(float newDegree);

	//Rotate object relative to current rotation
	void rotate(float radian);

	//Set absolute rotation
	void setRotation(float newRadian);

	//Move object relative to current position
	void move(glm::vec2& move);

	//Set absolute position
	void setPosition(glm::vec2& newPosition);

	//Non-Uniform scale
	void setScale(glm::vec2& newScale);

	//Uniform scale
	void setScale(float newScale);


	glm::vec2 getPosition() { return position; }
	glm::vec2 getScale() { return scale; }
	float getRotation() { return rotation; }
	float getRotationDeg() { return rotation * (180 / M_PI); }

	//Misc
	void print();

private:
	float clampRotation();
	glm::vec2 position;
	glm::vec2 scale;
	float rotation;
};
#endif
