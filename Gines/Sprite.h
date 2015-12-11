#pragma once

#include <glm\glm.hpp>
#include <GL\glew.h>
#include <cstddef>
#include "GLTexture.h"
#include "Vertex.h"
#include "Component.h"

struct AABB {

};

namespace gines
{
	class Sprite : public Component
	{
	public:
		Sprite();
		~Sprite();

	void initialize(glm::vec2 pos, int w, int h, std::string path);
		void render();
		void setPosition(glm::vec2& newPosition);
		void setPosition(float _x, float _y);
		void setRotation(float newRotation);
		void rotate(float incrementation);
		void setOrigin(float _x, float _y);
		void setOrigin(glm::vec2& vec);

	private:
		glm::vec2 position;
		glm::vec2 origin;//Center of rotation, drawing point, default left corner
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
