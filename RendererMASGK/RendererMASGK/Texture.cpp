#include "stdafx.h"
#include "Texture.h"




Texture::Texture(int width, int height) : width{ width }, height{ height }
{
	size = height * width;

	arr = new float3[size];
}

Texture::~Texture()
{
	delete[] arr;
}
float3 & Texture::operator[](unsigned int at)
{
	if (at >= size || at < 0) { throw std::exception("Texture: array out of bounds"); }

	return arr[at];
}

const float3 & Texture::operator[](unsigned int at) const
{
	if (at >= size || at < 0) { throw std::exception("Texture: array out of bounds"); }
	
	return arr[at];
}

