#include <vector>
#include "CollisionBox.h"
#include "Geometry.h"
#include "Gameobject.h"

namespace gines
{
	std::vector<CollisionBox*> collisionBoxes;
	CollisionBox::CollisionBox() : size(0, 0), position(0, 0), origin(0)
	{
		//Push to collision boxes vector
		collisionBoxes.push_back(this);
	}
	CollisionBox::~CollisionBox()
	{
		//Remove from collision boxes vector
		for (unsigned i = 0; i < collisionBoxes.size(); i++)
		{
			if (collisionBoxes[i] == this)
			{
				collisionBoxes.erase(collisionBoxes.begin() + i);
			}
		}
	}
	bool CollisionBox::isColliding(CollisionBox& other)
	{
		//TODO: SAT
		//Until then... AABB
		glm::vec2 bottomLeft = position - origin + gameObject->transform().getPosition();
		glm::vec2 otherBottomLeft = other.position - other.origin + other.gameObject->transform().getPosition();
		if (bottomLeft.x + size.x < otherBottomLeft.x)
			return false;
		if (bottomLeft.x > otherBottomLeft.x + other.size.x)
			return false;
		if (bottomLeft.y + size.y < otherBottomLeft.y)
			return false;
		if (bottomLeft.y > otherBottomLeft.y + other.size.y)
			return false;

		return true;
	}
	bool CollisionBox::isColliding(glm::vec2& point)
	{
		float x1 = position.x - origin.x + gameObject->transform().getPosition().x;
		if (point.x < x1)
			return false;
		if (point.x > x1 + size.x)
			return false;
		float y1 = position.y - origin.y + gameObject->transform().getPosition().y;
		if (point.y < y1)
			return false;
		if (point.y > y1 + size.y)
			return false;
		return true;
	}
}