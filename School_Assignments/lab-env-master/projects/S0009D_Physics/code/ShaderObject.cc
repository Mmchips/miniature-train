#include "ShaderObject.h"
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

//using namespace std;

ShaderObject::ShaderObject()
{
}


ShaderObject::~ShaderObject()
{
}

std::string readFile(const char* filePath)
{
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	if (!fileStream.is_open())
	{
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
		return "";
	}

	std::string line = "";
	while (!fileStream.eof())
	{
		std::getline(fileStream, line);
		content.append(line + "\n");
	}

	fileStream.close();
	return content;
}

GLuint ShaderObject::loadShader(const char *vertex_path, const char *frag_path)
{
	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);

	//Read shaders
	std::string vertShaderStr = readFile(vertex_path);
	std::string fragShaderStr = readFile(frag_path);
	const char *vertShaderSrc = vertShaderStr.c_str();
	const char *fragShaderSrc = fragShaderStr.c_str();

	GLint result = GL_FALSE;
	GLint shaderLogSize;
	
	//Compile vertex shader
	glShaderSource(vertShader, 1, &vertShaderSrc, NULL);
	glCompileShader(vertShader);

	//Check vertex shader
	glGetShaderiv(vertShader, GL_COMPILE_STATUS, &result);
	
	glGetShaderiv(vertShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
	if (shaderLogSize > 0)
	{
		GLchar* buf = new GLchar[shaderLogSize];
		glGetShaderInfoLog(vertShader, shaderLogSize, NULL, buf);
		printf("[SHADER COMPILE ERROR]: %s", buf);
		delete[] buf;
	}

	//Compile fragment shader
	glShaderSource(fragShader, 1, &fragShaderSrc, NULL);
	glCompileShader(fragShader);

	//Check fragment shader
	glGetShaderiv(fragShader, GL_COMPILE_STATUS, &result);

	glGetShaderiv(fragShader, GL_INFO_LOG_LENGTH, &shaderLogSize);
	if (shaderLogSize > 0)
	{
		GLchar* buf = new GLchar[shaderLogSize];
		glGetShaderInfoLog(fragShader, shaderLogSize, NULL, buf);
		printf("[SHADER COMPILE ERROR]: %s", buf);
		delete[] buf;
	}

	//Linking the program
	program = glCreateProgram();
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);

	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &shaderLogSize);
	if (shaderLogSize > 0)
	{
		GLchar* buf = new GLchar[shaderLogSize];
		glGetProgramInfoLog(program, shaderLogSize, NULL, buf);
		printf("[PROGRAM LINK ERROR]: %s", buf);
		delete[] buf;
	}

	glDeleteShader(vertShader);
	glDeleteShader(fragShader);

	return program;
}

void ShaderObject::applyShader()
{
	glUseProgram(program);
}

void ShaderObject::modifyMat(char *matName, float *floatArr)
{
	if (locations.find(matName) == locations.end())
	{
		locations[matName] = glGetUniformLocation(program, matName);
	}
	glUniformMatrix4fv(locations.find(matName)->second, 1, GL_TRUE, floatArr);
}

void ShaderObject::modifyVec(char *vecName, float *floatArr)
{
	if (locations.find(vecName) == locations.end())
	{
		locations[vecName] = glGetUniformLocation(program, vecName);
	}
	glUniform4fv(locations.find(vecName)->second, 1, floatArr);
}