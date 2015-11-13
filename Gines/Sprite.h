#ifndef SPRITE_H
#define SPRITE_H

#include <glm\glm.hpp>
#include <GL\glew.h>
#include <cstddef>

#include "Vertex.h"

class Sprite
{
public:
	Sprite();
	~Sprite();

	void initialize(glm::vec2 pos, int width, int height);
	void draw();

private:
	glm::vec2 position;
	int width;
	int height;

	////
	float x;
	float y;
	GLuint vboID;
	////

};

#endif
