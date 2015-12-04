#include "Geometry.h"

namespace gines
{

	glm::vec2 rotatePoint(glm::vec2& point, float rotation)
	{
		glm::vec2 returnVec;
		returnVec.x = point.x * cos(rotation) - point.y * sin(rotation);
		returnVec.y = point.x * sin(rotation) + point.y * cos(rotation);
		return returnVec;
	}
	glm::vec2 rotatePoint(float x, float y, float rotation)
	{
		glm::vec2 returnVec;
		returnVec.x = x * cos(rotation) - y * sin(rotation);
		returnVec.y = x * sin(rotation) + y * cos(rotation);
		return returnVec;
	}
	float getMagnitude(glm::vec2& vec)
	{
		return sqrt(vec.x*vec.x + vec.y*vec.y);
	}
}