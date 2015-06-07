#include "Renderer.h"
#include "SpriteBatch.h"
#include "Camera.h"
#include "GLSL_ShaderProgram.h"
#include "Video.h"

namespace AndromedaEngine
{
	Renderer::Renderer()
	{
		//Initialize shaders
		shaderProgram = new GLSL_ShaderProgram();
		InitShaders();
		//Initialize sprite batching
		spriteBatch = new SpriteBatch();
		spriteBatch->Init();
	}

	Renderer::~Renderer(){}

	//Initializes shaders
	void Renderer::InitShaders()
	{
		shaderProgram->CreateShaders("shaders/VertexShader.vert", "shaders/FragmentShader.frag");
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////

	void Renderer::Render()
	{
		RenderStart();
		RenderGame();
		RenderEnd();
	}

	void Renderer::RenderStart()
	{
		//Clear buffers first
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Use shader program
		shaderProgram->Use();
	}

	void Renderer::RenderGame()
	{
		//Activate sprite textures
		glActiveTexture(GL_TEXTURE0);
		glUniform1f(10, 0); // 0 for GL_TEXTURE0 in glActiveTexture(), sets the sprite texture

		//Set the camera matrix
		glm::mat4 cameraMatrix = Camera::mainCamera->GetCameraMatrix();
		glUniformMatrix4fv(11, 1, GL_FALSE, &cameraMatrix[0][0]);

		SpriteBatching();

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Renderer::RenderEnd()
	{
		//Unuse shader program
		shaderProgram->Unuse();
		//Swap back to front buffer
		Video::SwapBuffer();
	}

	void Renderer::SpriteBatching()
	{
		spriteBatch->Begin();
		spriteBatch->End();
		spriteBatch->RenderBatchF();
	}

	SpriteBatch* Renderer::GetSpriteBatch()
	{
		return spriteBatch;
	}
}