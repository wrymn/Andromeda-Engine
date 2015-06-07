#pragma once
#include <string>
#include <GL\glew.h>
#include <iostream>

namespace AndromedaEngine
{
	class GLSL_ShaderProgram
	{
	public:
		GLSL_ShaderProgram();
		~GLSL_ShaderProgram();

		//Creates and compiles shaders from filePath. Creates Shader Program.
		void CreateShaders(const std::string& vertexFilePath, const std::string& fragmentFilePath);
		void Use();
		void Unuse();

		GLuint getUniformLocation(const std::string& uniformName);
	private:
		void CompileShader(const std::string& filePath, GLuint& shaderID);
		void LinkShaders();
		GLuint programID;
		GLuint vertexShaderID;
		GLuint fragmentShaderID;

	};
}