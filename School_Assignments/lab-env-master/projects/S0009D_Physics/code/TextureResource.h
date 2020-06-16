#pragma once
#include "GL/glew.h"

class TextureResource
{
public:
	TextureResource();
	~TextureResource();

	void loadFromFile(const char* filename);
	void generateHandle();
	void bindTexture();

private:

	GLuint texture;
};

