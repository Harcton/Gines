#ifndef CAMERA_H
#define CAMERA_H
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <vector>
#include "Component.h"

namespace gines
{	
	class Camera : public Component
	{
	public:
		Camera();
		~Camera();

		void update();

		void setScale(float);
		void setViewport(glm::vec2& bottomLeftPosition, glm::vec2& size);

		glm::vec2 getPosition();
		float getScale();
		glm::mat4 getCameraMatrix();
		bool isEnabled(){ return enabled; }
		void enable(){ enabled = true; }
		void disable(){ enabled = false; }
		void enableViewport();

	private:
		bool enabled;
		bool doMatrixUpdate;
		float scale;
		glm::mat4 orthoMatrix;
		glm::mat4 cameraMatrix;
		glm::vec2 gameObjectPosition;//Game object position tracking
		glm::vec2 viewportPosition;
		glm::vec2 viewportSize;
	};
	extern std::vector<gines::Camera*> cameras;//Vector of all cameras the application has
}

#endif
