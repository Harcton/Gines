#include "Component.h"
#include <iostream>



//TRANSFORM
Transform::Transform() :
position(0, 0), scale(0, 0), rotation(0)
{

}
//Rotate object relative to current rotation
void Transform::rotate(float rotate)
{

}

//Set absolute rotation
void Transform::setRotation(float rotation)
{

}

//Move object relative to current position
void Transform::move(glm::vec2& move)
{

}

//Set absolute position
void Transform::setPosition(glm::vec2& position)
{

}

//Non-Uniform scale
void Transform::setScale(glm::vec2& newScale)
{
	scale = newScale;
}

void Transform::update()
{
	//std::cout << "\nTransform update()";
}

void Transform::print()
{
	std::cout << "\nTransform:";
	std::cout << "\n\tX, Y: " << position.x << ", " << position.y;
	std::cout << "\n\txScale, yScale: " << scale.x << ", " << scale.y;
	std::cout << "\n\tRotation: " << rotation;
	std::cout << std::endl;
}