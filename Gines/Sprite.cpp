#include <glm/gtc/type_ptr.hpp>//glm::value_ptr
#include "Sprite.h"
#include "ResourceManager.h"
#include "Camera.h"
#include "GLSLProgram.h"
#include "GameObject.h"

namespace gines
{
	extern GLSLProgram colorProgram;

	Sprite::Sprite() : position(0, 0), rotation(0), width(0), height(0), doBufferUpdate(true)
	{	
	}


	Sprite::~Sprite()
	{
		glDeleteBuffers(1, &vboID);
	}

	void Sprite::initialize(glm::vec2 pos, int w, int h, std::string path)
	{
		glGenBuffers(1, &vboID);
		tex = gines::ResourceManager::getTexture(path);
		position = pos;
		width = w;
		height = h;

		doBufferUpdate = true;
	}

	void Sprite::setPosition(glm::vec2& newPosition)
	{
		if (position != newPosition)
		{
			doBufferUpdate = true;
			position = newPosition;
		}
	}
	void Sprite::setPosition(float _x, float _y)
	{
		if (position.x != _x || position.y != _y)
		{//If check may be insufficient due to foating point inaccuracy
			doBufferUpdate = true;
			position.x = _x;
			position.y = _y;
		}
	}
	void Sprite::setRotation(float newRotation)
	{
		if (rotation != newRotation)
		{
			rotation = newRotation;
			doBufferUpdate = true;
		}
	}
	void Sprite::rotate(float incrementation)
	{
		rotation += incrementation;
		doBufferUpdate = true;
	}
	void Sprite::updateBuffer()
	{
	
		/////////////////////////	

		VertexPositionColorTexture vertexData[6];

		vertexData[0].position.x = position.x + width;
		vertexData[0].position.y = position.y + height;
		vertexData[0].uv = glm::vec2(1.0f, 1.0f);

		vertexData[1].position.x = position.x;
		vertexData[1].position.y = position.y + height;
		vertexData[1].uv = glm::vec2(0.0f, 1.0f);

		vertexData[2].position.x = position.x;
		vertexData[2].position.y = position.y;
		vertexData[2].uv = glm::vec2(0.0f, 0.0f);

		vertexData[3].position.x = position.x;
		vertexData[3].position.y = position.y;
		vertexData[3].uv = glm::vec2(0.0f, 0.0f);

		vertexData[4].position.x = position.x + width;
		vertexData[4].position.y = position.y;
		vertexData[4].uv = glm::vec2(1.0f, 0.0f);

		vertexData[5].position.x = position.x + width;
		vertexData[5].position.y = position.y + height;
		vertexData[5].uv = glm::vec2(1.0f, 1.0f);

		for (int i = 0; i < 6; i++)
		{
			vertexData[i].color.r = 1;
			vertexData[i].color.g = 0;
			vertexData[i].color.b = 1;
			vertexData[i].color.a = 1;
		}

		vertexData[1].color.r = 0;
		vertexData[1].color.g = 0;
		vertexData[1].color.b = 1;
		vertexData[1].color.a = 1;


		vertexData[4].color.r = 1;
		vertexData[4].color.g = 0;
		vertexData[4].color.b = 0;
		vertexData[4].color.a = 1;

		glBindBuffer(GL_ARRAY_BUFFER, vboID);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		/////////////////////////

		doBufferUpdate = false;
	}


	//////
	void Sprite::draw()
	{
		for (unsigned c = 0; c < cameras.size(); c++)
			if (cameras[c]->isEnabled())
		{
			cameras[c]->enableViewport();
			if (gameObject != nullptr)
			{
				if (gameObjectPosition != gameObject->transform().getPosition())
				{//Game object has moved
					gameObjectPosition = gameObject->transform().getPosition();
					doBufferUpdate = true;
				}
				if (gameObjectRotation != gameObject->transform().getRotation())
				{//Game object has rotated
					gameObjectRotation = gameObject->transform().getRotation();
					doBufferUpdate = true;
				}
			}

			if (doBufferUpdate)
			{
				updateBuffer();
			}

			glUniformMatrix4fv(colorProgram.getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(cameras[c]->getCameraMatrix()));

			glBindTexture(GL_TEXTURE_2D, tex.id);

			glBindBuffer(GL_ARRAY_BUFFER, vboID);

			glEnableVertexAttribArray(0);
			glEnableVertexAttribArray(1);
			glEnableVertexAttribArray(2);



			//Position attribute pointer
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)offsetof(VertexPositionColorTexture, position));

			//Color attribute pointer
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)offsetof(VertexPositionColorTexture, color));

			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)offsetof(VertexPositionColorTexture, uv));

			glDrawArrays(GL_TRIANGLES, 0, 6);


			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
	//////

}