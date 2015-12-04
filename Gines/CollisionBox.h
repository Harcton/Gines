#pragma once
#include <glm/vec2.hpp>
#include "Component.h"

namespace gines
{
	class CollisionBox : public Component
	{
	public:
		CollisionBox();
		~CollisionBox();

		//Colllision
		bool isColliding(CollisionBox& other);
		bool isColliding(glm::vec2& point);

		//Position
		void setPosition(glm::vec2& vec) { position = vec; }
		void setPosition(float x, float y) { position.x = x; position.y = y; }
		void move(float x, float y) { position.x += x; position.y += y; }
		void move(glm::vec2& vec) { position += vec; }

		//Origin
		void setOrigin(glm::vec2& vec){ origin = vec; }
		void setOrigin(float x, float y){ origin.x = x; origin.y = y; }

		//Size
		void setWidth(float w) { size.x = w; }
		void setHeight(float h){ size.y = h; }
		void setSize(float w, float h){ size.x = w; size.y = h; }
		void setSize(glm::vec2& newSize){ size = newSize; }

	private:
		glm::vec2 size;
		glm::vec2 position;
		glm::vec2 origin;
	};

}