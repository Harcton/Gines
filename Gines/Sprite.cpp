#include <glm/gtc/type_ptr.hpp>//glm::value_ptr
#include "Sprite.h"
#include "Camera.h"
#include "GLSLProgram.h"
#include "GameObject.h"

namespace gines
{
	extern GLSLProgram colorProgram;

	Sprite::Sprite()
	{
		////
		vboID = 0;
		////
	}


	Sprite::~Sprite()
	{
		////
		if (vboID != 0)
		{
			glDeleteBuffers(1, &vboID);
		}
		////
	}

	void Sprite::setPosition(glm::vec2& newPosition)
	{
		if (position != newPosition)
		{
			doPositionUpdate = true;
			position = newPosition;
		}
	}
	void Sprite::setPosition(float _x, float _y)
	{
		if (position.x != _x || position.y != _y)
		{//If check may be insufficient due to foating point inaccuracy
			doPositionUpdate = true;
			position.x = _x;
			position.y = _y;
		}
	}
	void Sprite::setRotation(float newRotation)
	{
		if (rotation != newRotation)
		{
			rotation = newRotation;
			doRotationUpdate = true;
		}
	}
	void Sprite::rotate(float incrementation)
	{
		rotation += incrementation;
		doRotationUpdate = true;

	}
	void Sprite::updatePosition()
	{
		/////////////////////////
		if (vboID == 0)
		{
			glGenBuffers(1, &vboID);
		}

		VertexPositionColorTexture vertexData[6];

		vertexData[0].position.x = position.x + gameObject->transform().getPosition().x + width;
		vertexData[0].position.y = position.y + gameObject->transform().getPosition().y + height;
		vertexData[0].uv = glm::vec2(1.0f, 1.0f);

		vertexData[1].position.x = x;
		vertexData[1].position.y = y + height;
		vertexData[1].uv = glm::vec2(0.0f, 1.0f);

		vertexData[2].position.x = x;
		vertexData[2].position.y = y;
		vertexData[2].uv = glm::vec2(0.0f, 0.0f);

		vertexData[3].position.x = x;
		vertexData[3].position.y = y;
		vertexData[3].uv = glm::vec2(0.0f, 0.0f);

		vertexData[4].position.x = x + width;
		vertexData[4].position.y = y;
		vertexData[4].uv = glm::vec2(1.0f, 0.0f);

		vertexData[5].position.x = x + width;
		vertexData[5].position.y = y + height;
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

		doPositionUpdate = false;
	}
	void Sprite::updateRotation()
	{
		doRotationUpdate = false;
	}

	void Sprite::initialize(glm::vec2 pos, int w, int h)
	{
		position = pos;
		width = w;
		height = h;

		doRotationUpdate = true;
		doPositionUpdate = true;
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
					doPositionUpdate = true;
				}
				if (gameObjectRotation != gameObject->transform().getRotation())
				{//Game object has rotated
					gameObjectRotation = gameObject->transform().getRotation();
					doRotationUpdate = true;
				}
			}

			if (doPositionUpdate)
			{
				updatePosition();
			}
			if (doRotationUpdate)
			{
				updateRotation();
			}

			glUniformMatrix4fv(colorProgram.getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(cameras[c]->getCameraMatrix()));

			glBindBuffer(GL_ARRAY_BUFFER, vboID);

			glEnableVertexAttribArray(0);


			//Position attribute pointer
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)offsetof(VertexPositionColorTexture, position));

			//Color attribute pointer
			glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)offsetof(VertexPositionColorTexture, color));

			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexPositionColorTexture), (void*)offsetof(VertexPositionColorTexture, uv));

			glDrawArrays(GL_TRIANGLES, 0, 6);


			glDisableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
	//////

}