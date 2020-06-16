#include <iostream>
#include "TextureResource.h"
#include "stb_image.h"


TextureResource::TextureResource()
{
}


TextureResource::~TextureResource()
{
}

void TextureResource::generateHandle()
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

}

void TextureResource::bindTexture()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);

}

void TextureResource::loadFromFile(const char* filename)
{
	generateHandle();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, n;
	unsigned char* image;
	image = stbi_load(filename, &width, &height, &n, 4);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	bindTexture();
	glGenerateMipmap(GL_TEXTURE_2D);
	glGenerateTextureMipmap(texture);
}