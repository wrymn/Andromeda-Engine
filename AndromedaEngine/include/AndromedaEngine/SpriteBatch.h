#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <vector>
#include "Vector.h"
#include "Vertex.h"


namespace AndromedaEngine
{
	enum class SpriteSortType
	{
		NONE,
		FRONT_TOP_BACK,
		BACK_TO_FRONT,
		TEXTURE
	};

	//This is like a single sprite
	struct SpriteTexture
	{
		GLuint texture;
		float depth;

		//Only 4 verts out of 6 since 2 of them are the same
		Vertex topLeft;
		Vertex buttomleft;
		Vertex topRight;
		Vertex buttomRight;
	};

	class RenderBatch
	{
	public:
		GLuint offset;
		GLuint numVertices; // 6
		GLuint texture;

		RenderBatch(GLuint offset, GLuint numVertices, GLuint texture) : offset(offset), numVertices(numVertices), texture(texture){};
	};

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void Init();

		//Sets up the batch
		void Begin(SpriteSortType sortType = SpriteSortType::TEXTURE);
		//Called after all textures are added into current batch
		void End();
		//Renders the batch on screen 
		void RenderCurrentBatch();

		//Adds sprite to the batch
		void AddSprite(const glm::vec4& destRect, const glm::vec4& uvRect, const GLuint& texture, float depth, const Color& color);

	private:
		void CreateRenderBatches();
		void CreateVertexArray();
		//Sort the sprites by "Depth"
		void SortSpriteTextures();

		static bool compareFrontToBack(SpriteTexture* a, SpriteTexture* b);
		static bool compareBackToFront(SpriteTexture* a, SpriteTexture* b);
		static bool compareTexture(SpriteTexture* a, SpriteTexture* b);

		GLuint vbo;
		GLuint vao;

		SpriteSortType sortType;
		//Stores the list of all added textures(Even same ones)
		std::vector<SpriteTexture*> spriteTextures;
		//Stores all the textures which are distinct,
		//to render only one type of texture per loop
		std::vector<RenderBatch> renderBatches;
	};
}
