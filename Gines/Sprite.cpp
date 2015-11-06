#include "Sprite.h"


Sprite::Sprite()
{

}


Sprite::~Sprite()
{

}

void Sprite::initialize(glm::vec2 pos, int width, int height)
{
	position = pos;
	width = width;
	height = height;
}