#pragma once
class Texture
{
public:
	Texture();
	Texture(int width, int height);
	Texture(const Texture& other);
	~Texture();
	float3& operator[](unsigned int);
	const float3& operator[](unsigned int) const;

private:
	int width;
	int height;
	int size;
	std::vector<float3> vec;
	//float3* arr;
};