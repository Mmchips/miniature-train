#pragma once
#ifndef GLSHADER_H
#define GLSHADER_H

#include "GL/glew.h"
#include <map>

class ShaderObject
{
public:
	ShaderObject();
	~ShaderObject();

	GLuint loadShader(const char *vertex_path, const char *frag_path);
	void applyShader();
	void modifyMat(char *matName, float *floatArr);
	void modifyVec(char *vecName, float *floatArr);

	GLuint program;
	std::map<char*, GLuint> locations;
};

#endif
