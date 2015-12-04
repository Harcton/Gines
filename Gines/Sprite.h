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
		void setPosition(glm::vec2& newPosition);
		void setPosition(float _x, float _y);
		void setRotation(float newRotation);
		void rotate(float incrementation);

	private:
		glm::vec2 position;
		float rotation;
		int width;
		int height;
		GLuint vboID;
		GLTexture tex;

		//Game object tracking
		void updateBuffer();
		bool doBufferUpdate;
		glm::vec2 gameObjectPosition;	//Previous position of game object
		float gameObjectRotation;		//Previous rotation of game object

	};
}
#endif
