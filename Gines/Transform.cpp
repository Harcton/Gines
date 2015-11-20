#include "Transform.h"

//TRANSFORM
Transform::Transform() :
position(0, 0), scale(0, 0), rotation(0)
{

}

//Rotate object relative to current rotation using degrees
//Preferably use radians, as it is more efficient
void Transform::rotateDeg(float degree) {
	float radian = degree * (M_PI / 180);
	rotation += radian;
	rotation = clampRotation();
}

//Set absolute rotation using degrees
//Preferably use radians, as it is more efficient
void Transform::setRotationDeg(float newDegree) {
	float radian = newDegree * (M_PI / 180);
	rotation = radian;
	rotation = clampRotation();
}

//Rotate object relative to current rotation using radians
void Transform::rotate(float radian) {
	rotation += radian;
	rotation = clampRotation();
}

//Set absolute rotation using radians
void Transform::setRotation(float newRadian) {
	rotation = newRadian;
	rotation = clampRotation();
}

//Move object relative to current position
void Transform::move(glm::vec2& move) {
	position += move;
}

//Set absolute position
void Transform::setPosition(glm::vec2& newPosition) {
	position = newPosition;
}

//Non-Uniform scale
void Transform::setScale(glm::vec2& newScale) {
	scale = newScale;
}

//Uniform scale
void Transform::setScale(float newScale) {
	scale = glm::vec2(scale.x * newScale, scale.y * newScale);
}

float Transform::clampRotation() {
	if (rotation > 2 * M_PI) {
		rotation -= 2 * M_PI;
	}
	else if (rotation < 0) {
		rotation += 2 * M_PI;
	}
	return rotation;
}

void Transform::update() {

	//std::cout << "\nTransform update()";
}

void Transform::print() {
	std::cout << "\nTransform:";
	std::cout << "\n\tX, Y: " << position.x << ", " << position.y;
	std::cout << "\n\txScale, yScale: " << scale.x << ", " << scale.y;
	std::cout << "\n\tRotation: " << rotation;
	std::cout << std::endl;
}