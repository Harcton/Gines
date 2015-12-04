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
	}

	//Set absolute rotation using degrees
	//Preferably use radians, as it is more efficient
	void Transform::setRotationDeg(float newDegree) {
		float radian = newDegree * (M_PI / 180);
		rotation = radian;
		clampRotation(rotation);
	}

	//Rotate object relative to current rotation using radians
	void Transform::rotate(float radian) {
		rotation += radian;
		clampRotation(rotation);
	}

	//Set absolute rotation using radians
	void Transform::setRotation(float newRadian) {
		rotation = newRadian;
		clampRotation(rotation);
	}

	//Move object relative to current position
	void Transform::move(glm::vec2& move) {
		position += move;
	}

	void Transform::move(float x, float y) {
		position.x += x;
		position.y += y;
	}

	//Set absolute position
	void Transform::setPosition(glm::vec2& newPosition) {
		position = newPosition;
	}

	void Transform::setPosition(float x, float y) {
		position = glm::vec2(x, y);
	}

	//Non-Uniform scale
	void Transform::setScale(glm::vec2& newScale) {
		scale *= newScale;
	}

	void Transform::setScale(float x, float y) {
		scale *= glm::vec2(x, y);
	}

	//Uniform scale
	void Transform::setScale(float newScale) {
		scale *= glm::vec2(newScale, newScale);
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
}