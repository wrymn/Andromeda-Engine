#include "Sprite.h"
#include "Vertex.h"
#include "ImageLoader.h"
//#include <cstddef>
#include <iostream>
#include "ResourceManager.h"


namespace AndromedaEngine
{
	Sprite::Sprite()
	{
		bufferObject = 0;
	}

	//INITIALIZE THE SPRITE
	void Sprite::Init(float x, float y, float width, float height, std::string texturePath)
	{
		this->x = x;
		this->y = y;
		this->width = width;
		this->height = height;


		texture = ResourceManager::getTexture(texturePath);

		//Create vertices
		Vertex vertexData[6];

		vertexData[0].position = { x, y };
		vertexData[0].color = { 100, 0, 0, 255 };
		vertexData[0].uv = { 0, 0 };

		vertexData[1].position = { x + width, y + height };
		vertexData[1].color = { 255, 255, 255, 255 };
		vertexData[1].uv = { 1, 1 };

		vertexData[2].position = { x, y + height };
		vertexData[2].color = { 0, 200, 0, 255 };
		vertexData[2].uv = { 0, 1 };

		vertexData[3].position = { x + width, y + height };
		vertexData[3].color = { 255, 255, 200, 255 };
		vertexData[3].uv = { 1, 1 };

		vertexData[4].position = { x, y };
		vertexData[4].color = { 100, 0, 0, 255 };
		vertexData[4].uv = { 0, 0 };

		vertexData[5].position = { x + width, y };
		vertexData[5].color = { 255, 255, 255, 255 };
		vertexData[5].uv = { 1, 0 };

		//1.  Create Buffer object
		if (bufferObject == 0)
			glGenBuffers(1, &bufferObject);
		//2. Bind buffer object to binding point
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject);
		//3. Send our data to GPU
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);
		//4. Once DATA is on GPU, we can draw it in Draw() function

		//Unbidind our object from binding point
		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	//DRAW THE SPRITE
	void Sprite::Draw()
	{
		glBindTexture(GL_TEXTURE_2D, texture.id);

		//Give GL info about buffer. 0 = e.g only position
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, bufferObject);

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

		//Draw verticles
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//CLEAN
	Sprite::~Sprite()
	{
		if (bufferObject != 0)
			glDeleteBuffers(1, &bufferObject);
	}
}