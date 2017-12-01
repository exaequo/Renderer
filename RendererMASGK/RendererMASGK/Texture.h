#pragma once
class Texture
{
public:
	Texture();
	Texture(int width, int height, std::string name);
	Texture(const Texture& other);
	~Texture();
	float3& operator[](unsigned int);
	const float3& operator[](unsigned int) const;
	float3 getColor(const float3& coord) const;

private:
	int width;
	int height;
	int size;
	std::vector<float3> vec;
	std::string name;
	//float3* arr;
};