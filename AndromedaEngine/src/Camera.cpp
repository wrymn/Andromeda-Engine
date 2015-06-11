#include <iostream>
#include "Camera.h"
#include "Video.h"
#include "Time.h"

#define CAMERA_CONSOLE_DEBUG 0
#define CAMERA_CONSOLE_DEBUG_INTERVAL 5

namespace AndromedaEngine
{
	Camera* Camera::mainCamera = NULL;

	Camera::Camera() : position(0, 0), cameraMatrix(1), scale(1), needsMatrixUpdate(true), screenWidth(Video::GetScreenWidth()), screenHeight(Video::GetScreenHeight()), orthoMatrix(1.0f), cameraDebugCounter(CAMERA_CONSOLE_DEBUG_INTERVAL){}
	Camera::Camera(float screenWidth, float screenHeight) : position(0, 0), cameraMatrix(1), scale(1), needsMatrixUpdate(true), screenWidth(screenWidth), screenHeight(screenHeight), orthoMatrix(1.0f), cameraDebugCounter(CAMERA_CONSOLE_DEBUG_INTERVAL){}
	Camera::~Camera(){}

	//Updates the Camera
	void Camera::Update()
	{
		if (needsMatrixUpdate)
		{
			//Transalte the matrix
			orthoMatrix = glm::ortho(0.0f, (float)screenWidth, 0.0f, (float)screenHeight, 0.01f, 100.0f);
			glm::vec3 translate(-position.x + screenWidth / 2, -position.y + screenHeight / 2, 0);
			cameraMatrix = glm::translate(orthoMatrix, translate);

			//Scale the matrix
			glm::vec3 scale(scale, scale, 0);
			cameraMatrix = glm::scale(glm::mat4(1.0f), scale) * cameraMatrix;

			needsMatrixUpdate = false;
		}

		screenWidth = Video::GetScreenWidth();
		screenHeight = Video::GetScreenHeight();

		//Update debug camera info
		DebugToConsole();
	}

	//Creates and returns new camera
	Camera* Camera::CreateCamera()
	{
		return new Camera();
	}

	//Converts screen position to world position
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

	void Camera::DebugToConsole()
	{
		if (CAMERA_CONSOLE_DEBUG)
		{
			cameraDebugCounter += Time::deltaTime;
			if (cameraDebugCounter > CAMERA_CONSOLE_DEBUG_INTERVAL)
			{
				std::cout << std::endl;
				std::cout << "**** MAIN CAMERA DEBUG ****" << std::endl;
				std::cout << "Position: (" << position.x << ", " << position.y << ")" << std::endl;
				std::cout << "Scale: " << scale << std::endl;
				std::cout << "Screen Size: (" << screenWidth << ", " << screenHeight << ")" << std::endl;
				std::cout << "Camera Matrix: " << std::endl;
				std::cout << "(" << cameraMatrix[0][0] << "," << cameraMatrix[0][1] << "," << cameraMatrix[0][2] << "," << cameraMatrix[0][3] << ")" << std::endl;
				std::cout << "(" << cameraMatrix[1][0] << "," << cameraMatrix[1][1] << "," << cameraMatrix[1][2] << "," << cameraMatrix[1][3] << ")" << std::endl;
				std::cout << "(" << cameraMatrix[2][0] << "," << cameraMatrix[2][1] << "," << cameraMatrix[2][2] << "," << cameraMatrix[2][3] << ")" << std::endl;
				std::cout << "(" << cameraMatrix[3][0] << "," << cameraMatrix[3][1] << "," << cameraMatrix[3][2] << "," << cameraMatrix[3][3] << ")" << std::endl;
				std::cout << "***************************" << std::endl;
				std::cout << std::endl;
				//cameraMatrix[3][0] = 0;
				//cameraMatrix[3][1] = 0;
				cameraDebugCounter = 0;
			}
		}
	}
}
