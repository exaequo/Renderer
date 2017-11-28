#pragma once
class Texture
{
public:
	Texture(int width, int height);
	~Texture();
	float3& operator[](unsigned int);
	const float3& operator[](unsigned int) const;

private:
	int width;
	int height;
	int size;
	float3* arr;
};