#ifndef SPRITE_H
#define SPRITE_H

#include <glm\glm.hpp>
#include <GL\glew.h>
#include <cstddef>
#include "GLTexture.h"
#include "Vertex.h"
#include "Component.h"
namespace gines
{
	class Sprite : public Component
{
public:
	Sprite();
	~Sprite();

	void initialize(glm::vec2 pos, int w, int h, std::string path);
	void draw();

private:
	glm::vec2 position;
	int width;
	int height;

	////
	GLuint vboID;
	GLTexture tex;
	////

};
}
#endif
