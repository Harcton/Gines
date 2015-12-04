#pragma once

#include <glm/vec2.hpp>
#include <iostream>
#include "Component.h"


namespace gines
{
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
		void move(float x, float y);

		//Set absolute position
		void setPosition(glm::vec2& newPosition);
		void setPosition(float x, float y);

		//Non-Uniform scale
		void setScale(glm::vec2& newScale);
		void setScale(float x, float y);

		//Uniform scale
		void setScale(float newScale);


		glm::vec2 getPosition() { return position; }
		glm::vec2 getScale() { return scale; }
		float getRotation() { return rotation; }
		float getRotationDeg() { return rotation * (180 / M_PI); }

	private:
		void clampRotation(float& rotation);
		glm::vec2 position;
		glm::vec2 scale;
		float rotation;
	};
}