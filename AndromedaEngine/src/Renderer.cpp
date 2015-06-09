#include "Renderer.h"
#include "SpriteBatch.h"
#include "Camera.h"
#include "GLSL_ShaderProgram.h"
#include "Video.h"
#include "Scene.h"
#include "Vector.h"

namespace AndromedaEngine
{
	Renderer::Renderer(Scene& scene)
	{
		//Initialize shaders
		shaderProgram = new GLSL_ShaderProgram();
		InitShaders();
		//Initialize sprite batching
		spriteBatch = new SpriteBatch();
		spriteBatch->Init();

		this->scene = &scene;
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
		Video::ClearScreen();
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
		//std::cout << Camera::mainCamera->GetScale() << std::endl;
		glUniformMatrix4fv(11, 1, GL_FALSE, &cameraMatrix[0][0]);

		SpriteBatching();

		Vector2 pos = Vector2(-0.5f, 0);
		//DrawSquare(pos, 0.001f);

		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Renderer::DrawSquare(Vector2 origin, float size)
	{
		Vector2 vertices[12] = {
			//First polygon
			origin.x, origin.y,
			origin.x + size, origin.y,
			origin.x, origin.y + size,

			//Second polygon
			origin.x + size, origin.y,
			origin.x + size, origin.y + size,
			origin.x, origin.y + size,
		};

		GLuint VBO = 0;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		//glEnableVertexAttribArray(1);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, NULL, NULL);
		//glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, NULL, NULL);

		glDisableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Renderer::RenderEnd()
	{
		//Unuse shader program
		shaderProgram->Unuse();
		//Swap back to front buffer
		Video::SwapBuffer();
	}

	//Renders the sprites on the screen
	void Renderer::SpriteBatching()
	{
		//Prepare sprite batch
		spriteBatch->Begin();
		//Add all textures to sprite batch
		scene->UpdateSpriteRenderers();
		//Add batch together
		spriteBatch->End();

		//Render the batch to screen
		spriteBatch->RenderCurrentBatch();
	}

	SpriteBatch* Renderer::GetSpriteBatch()
	{
		return spriteBatch;
	}
}