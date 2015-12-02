#include "Transform.h"

namespace gines
{
	//TRANSFORM
	Transform::Transform() :
		position(0, 0), scale(0, 0), rotation(0)
	{}

	//Rotate object relative to current rotation using degrees
	//Preferably use radians, as it is more efficient
	void Transform::rotateDeg(float degree) {
		float radian = degree * (M_PI / 180);
		rotation += radian;
		clampRotation(rotation);
		//sprite.updateRotation(rotation);
	}

	//Set absolute rotation using degrees
	//Preferably use radians, as it is more efficient
	void Transform::setRotationDeg(float newDegree) {
		float radian = newDegree * (M_PI / 180);
		rotation = radian;
		clampRotation(rotation);
		//sprite.updateRotation(rotation);
	}

	//Rotate object relative to current rotation using radians
	void Transform::rotate(float radian) {
		rotation += radian;
		clampRotation(rotation);
		//sprite.updateRotation(rotation);
	}

	//Set absolute rotation using radians
	void Transform::setRotation(float newRadian) {
		rotation = newRadian;
		clampRotation(rotation);
		//sprite.updateRotation(rotation);
	}

	//Move object relative to current position
	void Transform::move(glm::vec2& move) {
		position += move;
		//sprite.updatePosition(position);
	}

	void Transform::move(float x, float y) {
		position += glm::vec2(x, y);
		//sprite.updatePosition(position);
	}

	//Set absolute position
	void Transform::setPosition(glm::vec2& newPosition) {
		position = newPosition;
		//sprite.updatePosition(position);
	}

	void Transform::setPosition(float x, float y) {
		position = glm::vec2(x, y);
		//sprite.updatePosition(position);
	}

	//Non-Uniform scale
	void Transform::setScale(glm::vec2& newScale) {
		scale *= newScale;
		//sprite.updateScale(scale);
	}

	void Transform::setScale(float x, float y) {
		scale *= glm::vec2(x, y);
		//sprite.updateScale(scale);
	}

	//Uniform scale
	void Transform::setScale(float newScale) {
		scale *= glm::vec2(newScale, newScale);
		//sprite.updateScale(scale);
	}

	void Transform::clampRotation(float& rotation) {
		while (rotation < 0 || rotation > 2 * M_PI)
		{
			if (rotation > 2 * M_PI) {
				rotation -= 2 * M_PI;
			}
			if (rotation < 0) {
				rotation += 2 * M_PI;
			}
		}
	}

	void Transform::update() {

		//std::cout << "\nTransform update()";
	}

	void Transform::print() {
		std::cout << "\nTransform:";
		std::cout << "\n\tX, Y: " << position.x << ", " << position.y;
		std::cout << "\n\txScale, yScale: " << scale.x << ", " << scale.y;
		std::cout << "\n\tRotation: " << rotation;
		std::cout << "\n";
	}
}