#include "stdafx.h"
#include "Texture.h"




Texture::Texture() : width{ 0 }, height{ 0 }, size{ 0 }{}

Texture::Texture(int width, int height) : width{ width }, height{ height }, size{ height*width }
{
	//arr = new float3[size];
	vec = std::vector<float3>(size);
}

Texture::Texture(const Texture & other) : width{ other.width }, height{ other.height }, size{ other.size }
{
	//arr = new float3[size];
	vec = std::vector<float3>(size);
	for (int i = 0; i < size; ++i)
	{
		vec[i] = other.vec[i];
		//arr[i] = float3{ other.arr[i] };
	}
}

Texture::~Texture()
{
	//delete[] arr;
}
float3 & Texture::operator[](unsigned int at)
{
	if (at >= size || at < 0) { throw std::exception("Texture: array out of bounds"); }

	return vec[at];
}

const float3 & Texture::operator[](unsigned int at) const
{
	if (at >= size || at < 0) { throw std::exception("Texture: array out of bounds"); }
	
	return vec[at];
}

