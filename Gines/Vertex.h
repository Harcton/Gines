#ifndef VERTEX_H
#define VERTEX_H

#include <GL/glew.h>
#include <glm\glm.hpp>

struct VertexPositionColorTexture
{
	glm::vec2 position;
	glm::vec4 color;
	glm::vec2 uv;
};

struct VertexPositionColor
{
	glm::vec2 position;
	glm::vec4 color;
};

#endif