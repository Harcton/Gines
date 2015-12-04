#include "Camera.h"
#include "GameObject.h"
#include "Transform.h"
#include <gl\glew.h>
extern int WINDOW_WIDTH;
extern int WINDOW_HEIGHT;

namespace gines
{
	std::vector<gines::Camera*> cameras;

	Camera::Camera() : enabled(true), doMatrixUpdate(true), scale(1), orthoMatrix(1.0f), cameraMatrix(1.0f), gameObjectPosition(0, 0), viewportPosition(0), viewportSize(0)
	{
		cameras.push_back(this);
	}
	Camera::~Camera()
	{
		for (unsigned i = 0; i < cameras.size(); i++)
		{
			if (cameras[i] == this)
			{
				cameras.erase(cameras.begin() + i);
				break;
			}
		}
	}
	void Camera::setViewport(glm::vec2& position, glm::vec2& size)
	{
		viewportPosition = position;
		viewportSize = size;
		orthoMatrix = glm::ortho(0.0f, (float)WINDOW_WIDTH, 0.0f, (float)WINDOW_HEIGHT);
		//orthoMatrix = glm::ortho(position.x, (float)WINDOW_WIDTH, position.y, (float)WINDOW_HEIGHT);
		//orthoMatrix = glm::ortho(position.x, viewportSize.x, position.y, viewportSize.y);
	}
	void Camera::update()
	{
		if (gameObjectPosition != gameObject->transform().getPosition())
		{
			gameObjectPosition = gameObject->transform().getPosition();
			doMatrixUpdate = true;
		}

		if (doMatrixUpdate == false)
			return;

		//Translate
		//glm::vec3 translate(screenPortPosition.x - screenPortSize.x*0.5f - gameObject->transform().getPosition().x,
		//	/******************/screenPortPosition.y - screenPortSize.y*0.5f - gameObject->transform().getPosition().y, 0.0f);
		glm::vec3 translate(-gameObject->transform().getPosition().x + viewportSize.x*0.5f/ (viewportSize.x / WINDOW_WIDTH),// + viewportSize.x * (1 - (WINDOW_WIDTH - viewportSize.x) / viewportSize.x)
			/**************/-gameObject->transform().getPosition().y + viewportSize.y*0.5f/ (viewportSize.y / WINDOW_HEIGHT), 0.0f);//  + viewportSize.y * (1 - (WINDOW_HEIGHT - viewportSize.y) / viewportSize.y)
		//glm::vec3 translate(WINDOW_WIDTH / 2 - gameObject->transform().getPosition().x, WINDOW_HEIGHT / 2 - gameObject->transform().getPosition().y, 0.0f);
		cameraMatrix = glm::translate(orthoMatrix, translate);

		//Scale
		glm::vec3 scl(scale, scale, 0.0f);// *(screenPortSize.x / WINDOW_WIDTH)   *(screenPortSize.y / WINDOW_HEIGHT)
		cameraMatrix = glm::scale(glm::mat4(1.0f), scl) * cameraMatrix;

		////Fix zoom
		//translate = glm::vec3(screenWidth / 2, screenHeight / 2, 0.0f);
		//cameraMatrix = glm::translate(cameraMatrix, translate);

		doMatrixUpdate = false;
	}
	void Camera::enableViewport()
	{
		glViewport(viewportPosition.x, viewportPosition.y, viewportSize.x, viewportSize.y);
	}

	void Camera::setScale(float newScale){ scale = newScale; doMatrixUpdate = true; }
	float Camera::getScale(){ return scale; }
	glm::mat4 Camera::getCameraMatrix(){ return cameraMatrix; }

}