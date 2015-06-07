#include <fstream>
#include <windows.h>
#include <string>
#include <iostream>
#include "GLSL_ShaderProgram.h"
#include "Errors.h"

namespace AndromedaEngine
{

	GLSL_ShaderProgram::GLSL_ShaderProgram()
	{
		programID = 0;
		vertexShaderID = 0;
		fragmentShaderID = 0;
	}


	GLSL_ShaderProgram::~GLSL_ShaderProgram()
	{
	}

	//CREATED AND COMPILES SHADERS
	void GLSL_ShaderProgram::CreateShaders(const std::string& vertexFilePath, const std::string& fragmentFilePath)
	{
		//Creates the shaders
		vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		Error(vertexShaderID == 0 ? true : false, "Vertex shader could not be created", true);
		fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
		Error(fragmentShaderID == 0 ? true : false, "Vertex shader could not be created", true);

		//Compile the shaders
		CompileShader(vertexFilePath, vertexShaderID);
		CompileShader(fragmentFilePath, fragmentShaderID);

		//Link shaders
		LinkShaders();
	}

	//COMPILES THE SHADERS
	void GLSL_ShaderProgram::CompileShader(const std::string& filePath, GLuint& shaderID)
	{
		//Load the shader code
		std::fstream shaderFile(filePath);
		Error(shaderFile.fail(), "Failed to open " + filePath, true);

		std::string fileContents = "";
		std::string line;

		while (std::getline(shaderFile, line))
			fileContents += line + "\n";

		shaderFile.close();

		//Put shader code into Source
		const char* contentsPtr1 = fileContents.c_str();
		glShaderSource(shaderID, 1, &contentsPtr1, 0);
		glCompileShader(shaderID);

		//Check for errors
		GLint success = 0;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (success != GL_TRUE)
		{
			GLint compileInfoLength = 0;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &compileInfoLength);

			GLchar* buffer = new GLchar[compileInfoLength];
			GLsizei bufferSize;
			glGetShaderInfoLog(shaderID, compileInfoLength, &bufferSize, buffer);
			Error("Compilation of shaders failed with error: " + (std::string)buffer, false);
			delete[]buffer;

		}
	}

	//LINKS THE SHADERS AND CREATE SHADER PROGRAM
	void GLSL_ShaderProgram::LinkShaders()
	{
		programID = glCreateProgram();
		glAttachShader(programID, vertexShaderID);
		glAttachShader(programID, fragmentShaderID);
		glLinkProgram(programID);

		glDetachShader(programID, vertexShaderID);
		glDetachShader(programID, fragmentShaderID);
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}

	void GLSL_ShaderProgram::Use()
	{
		glUseProgram(programID);
	}
	void GLSL_ShaderProgram::Unuse()
	{
		glUseProgram(0);
	}


	//FINDS UNIFORM VARIALBLE INSIDE SHADER PROGRAM WE CREATED
	GLuint GLSL_ShaderProgram::getUniformLocation(const std::string& uniformName)
	{
		GLuint location = glGetUniformLocation(programID, uniformName.c_str());
		//Error(location == GL_INVALID_INDEX, "Uniform shader variable: " + uniformName + " could not be found in shader program!", true);

		return location;
	}
}