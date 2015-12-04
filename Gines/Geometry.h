#pragma once
#include <glm/vec2.hpp>
#include <math.h>

namespace gines
{
	glm::vec2 rotatePoint(glm::vec2& point, float rotation);
	glm::vec2 rotatePoint(float x, float y, float rotation);
	float getMagnitude(glm::vec2& vec);
}