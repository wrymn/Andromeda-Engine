#pragma once

namespace AndromedaEngine
{
	class SpriteBatch;
	class Scene;
	class GLSL_ShaderProgram;
	class Vector2;

	class Renderer
	{
	private:
		//The shader program instance, holds shader program
		GLSL_ShaderProgram* shaderProgram;
		//The sprite batch holding all sprites of current level
		SpriteBatch* spriteBatch;
		//The scene instance the renderer renders to
		Scene* scene;

	public:
		//Renders the current sprite batch on screen
		void Render();
		//Returns sprite batch class which holds all textures
		SpriteBatch* GetSpriteBatch();
		
		void DrawSquare(Vector2 origin, float size);

	private:
		//Runs before everything is rendered to screen
		void RenderStart();
		//Renders the game
		void RenderGame();
		//Runs after everything is rendered
		void RenderEnd();
		//Draws entities on screen
		void SpriteBatching();

		//Initializes shaders bound to this renderer
		void InitShaders();

	public:
		Renderer(Scene& scene);
		~Renderer();
	};
}