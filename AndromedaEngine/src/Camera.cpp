#include "Camera.h"
#include <iostream>

namespace AndromedaEngine
{
	Camera* Camera::mainCamera;

	Camera::Camera() : position(0, 0), cameraMatrix(1), scale(1), needsMatrixUpdate(true), screenWidth(500), screenHeight(500), orthoMatrix(1.0f){}
	Camera::~Camera(){}

	//Updates the Camera
	void Camera::Update()
	{
		if (needsMatrixUpdate)
		{
			//Transalte the matrix
			glm::vec3 translate(-position.x + screenWidth / 2, -position.y + screenHeight / 2, 0);
			cameraMatrix = glm::translate(orthoMatrix, translate);

			//Scale the matrix
			glm::vec3 scale(scale, scale, 0);
			cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * cameraMatrix;

			needsMatrixUpdate = false;
		}
	}

	//Initializes the Camera
	void Camera::Init(float screenWidth, float screenHeight)
	{
		this->screenWidth = screenWidth;
		this->screenHeight = screenHeight;

		//Set the camera size
		orthoMatrix = glm::ortho(0.0f, screenWidth, 0.0f, screenHeight);
	}

	Vector2 Camera::ScreenToWorldCoords(Vector2 screenPosition)
	{
		//Invert Y coordinates
		screenPosition.y = screenHeight - screenPosition.y;
		//0 is the center
		screenPosition -= Vector2(screenWidth / 2, screenHeight / 2);
		//Scale the coordinates 
		screenPosition /= scale;
		//Translate with camera position
		screenPosition += position;

		return screenPosition;
	}
}
