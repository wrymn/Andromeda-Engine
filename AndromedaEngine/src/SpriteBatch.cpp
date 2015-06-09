#include <algorithm>
#include <iostream>
#include "SpriteBatch.h"
#include "Vector.h"

namespace AndromedaEngine
{
	SpriteBatch::SpriteBatch() : vbo(0), vao(0) {}
	SpriteBatch::~SpriteBatch(){}

	void SpriteBatch::Init()
	{
		CreateVertexArray();
	}

	void SpriteBatch::Begin(SpriteSortType sortType)
	{
		this->sortType = sortType;
		//Clear the lists first
		renderBatches.clear();
		for (unsigned int i = 0; i < spriteTextures.size(); i++)
			delete spriteTextures[i];
		
		spriteTextures.clear();
	}

	void SpriteBatch::End()
	{
		SortSpriteTextures();
		CreateRenderBatches();
	}

	void SpriteBatch::AddSprite(const glm::vec4& destRect, const glm::vec4& uvRect, const GLuint& texture, float depth, const Color& color)
	{
		SpriteTexture* newSprite = new SpriteTexture();
		newSprite->texture = texture;
		newSprite->depth = depth;

		newSprite->topLeft.position = { destRect.x, destRect.y + destRect.w };
		newSprite->topLeft.color = color;
		newSprite->topLeft.uv = { uvRect.x, uvRect.y + uvRect.w };

		newSprite->buttomleft.position = { destRect.x, destRect.y };
		newSprite->buttomleft.color = color;
		newSprite->buttomleft.uv = { uvRect.x, uvRect.y };

		newSprite->topRight.position = { destRect.x + destRect.z, destRect.y + destRect.w};
		newSprite->topRight.color = color;
		newSprite->topRight.uv = { uvRect.x + uvRect.z, uvRect.y + uvRect.w };

		newSprite->buttomRight.position = { destRect.x + destRect.z, destRect.y };
		newSprite->buttomRight.color = color;
		newSprite->buttomRight.uv = { uvRect.x + uvRect.z, uvRect.y };


		spriteTextures.push_back(newSprite);
	}

	void SpriteBatch::RenderCurrentBatch()
	{
		glBindVertexArray(vao);
		for (int i = 0; i < renderBatches.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, renderBatches[i].texture);

			glDrawArrays(GL_TRIANGLES, renderBatches[i].offset, renderBatches[i].numVertices);
		}
		glBindVertexArray(0);
	}

	void SpriteBatch::CreateRenderBatches()
	{
		//Create vertices for the Sprites
		std::vector<Vertex> vertices;
		//Resize memory for performance
		vertices.resize(spriteTextures.size() * 6);


		//If there is nothing inside spriteTextures size() == 0
		if (spriteTextures.empty())
			return;

		//Create first render batch
		int offset = 0;
		int currentVertex = 0;
		//Add the texture to the RenderBatch
		renderBatches.emplace_back(offset, 6, spriteTextures[0]->texture); //Passes parameters without creating instance
		vertices[currentVertex++] = spriteTextures[0]->buttomleft;
		vertices[currentVertex++] = spriteTextures[0]->topRight;
		vertices[currentVertex++] = spriteTextures[0]->topLeft;
		vertices[currentVertex++] = spriteTextures[0]->topRight;
		vertices[currentVertex++] = spriteTextures[0]->buttomleft;
		vertices[currentVertex++] = spriteTextures[0]->buttomRight;
		offset += 6;

		for (int cg = 1; cg < spriteTextures.size(); cg++)
		{
			//`Don`t add texture, which is already in batch. Textures were sorted first by TEXTURE to be near each other for this to work
			if (spriteTextures[cg]->texture != spriteTextures[cg - 1]->texture)
				renderBatches.emplace_back(offset, 6, spriteTextures[cg]->texture); //Passes parameters without creating instance
			else
				renderBatches.back().numVertices += 6;
			vertices[currentVertex++] = spriteTextures[cg]->buttomleft;
			vertices[currentVertex++] = spriteTextures[cg]->topRight;
			vertices[currentVertex++] = spriteTextures[cg]->topLeft;
			vertices[currentVertex++] = spriteTextures[cg]->topRight;
			vertices[currentVertex++] = spriteTextures[cg]->buttomleft;
			vertices[currentVertex++] = spriteTextures[cg]->buttomRight;
			offset += 6;
		}

		//Bind VBO
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		//Instead of rewriting data stored in VBO, clear it and then upload it in subData
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		//Upload the data 
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex),vertices.data());// vertices.data() - adress of first element
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteBatch::CreateVertexArray()
	{
		//Create Vertex Array Object - VAO
		glGenVertexArrays(1, &vao);
		glBindVertexArray(vao);
		//Create Vertex Buffer Object - VBO
		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		
		//Give GL info about buffer. 0 = e.g only position
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//Position parameters
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		//Color parameters
		// 1st param - index where to start in our data
		// 2st param - num of values for this data
		// 3st param - type
		// 4st param - normalize? (0.0 - 1.0)
		// 5st param - size
		// 6st param - offset in bytes
		glVertexAttribPointer(1, 3, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		//This disables all previous bounds and enabled attribs
		glBindVertexArray(0);
	}

	//Sorts the textures in our Vector by its depth
	void SpriteBatch::SortSpriteTextures()
	{
		switch (sortType)
		{
		case SpriteSortType::BACK_TO_FRONT:
			// stable_sort makes sure same elemts are in right order
			std::stable_sort(spriteTextures.begin(), spriteTextures.end(), compareFrontToBack);
			break;
		case SpriteSortType::FRONT_TOP_BACK:
			std::stable_sort(spriteTextures.begin(), spriteTextures.end(), compareBackToFront);
			break;
		case SpriteSortType::TEXTURE:
			std::stable_sort(spriteTextures.begin(), spriteTextures.end(), compareTexture);
			break;
		}

	}

	bool SpriteBatch::compareFrontToBack(SpriteTexture* a, SpriteTexture* b)
	{
		return (a->depth < b->depth);
	}
	bool SpriteBatch::compareBackToFront(SpriteTexture* a, SpriteTexture* b)
	{
		return (a->depth > b->depth);
	}
	bool SpriteBatch::compareTexture(SpriteTexture* a, SpriteTexture* b)
	{
		return (a->texture < b->texture);
	}
}