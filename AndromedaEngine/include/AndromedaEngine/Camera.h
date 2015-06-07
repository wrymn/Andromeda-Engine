#pragma once
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include "Vector.h"

namespace AndromedaEngine
{
	class Camera
	{
	public:
		//Main game camera 
		static Camera* mainCamera;

	public:
		//Creates and returns new camera
		static Camera* CreateCamera();
		void Update();

		//Set the camera position
		void SetPosition(const Vector2& newPosition) { position = newPosition; needsMatrixUpdate = true; };
		//Set the camera scale
		void SetScale(float newScale) { scale = newScale; needsMatrixUpdate = true; };
		//Get the camera position
		Vector2 GetPosition() { return position; };
		//Get the camera scale
		float GetScale() { return scale; };
		//Get camera matrix
		glm::mat4 GetCameraMatrix() { return cameraMatrix; };
		//Converts screen position to world position
		Vector2 ScreenToWorldCoords(Vector2 screenPosition);
	private:
		int screenWidth, screenHeight;
		//Whether the camera needs matrix update
		bool needsMatrixUpdate;
		float scale;
		Vector2 position;
		glm::mat4 cameraMatrix;

		glm::mat4 orthoMatrix;
	public:
		Camera();
		Camera(float screenWidth, float screenHeight);
		~Camera();
	};
}

