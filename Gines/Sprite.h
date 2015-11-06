#ifndef SPRITE_H
#define SPRITE_H

#include <glm\glm.hpp>
#include <GL\glew.h>

class Sprite
{
public:
	Sprite();
	~Sprite();

	void initialize(glm::vec2 pos, int width, int height);

private:
	glm::vec2 position;
	int width;
	int height;

};

#endif
