#pragma once
class Light
{
public:
	Light():position{{0,0,0}}, color{{0,0,0}}{}
	Light(float3 position, float3 color) : position{position}, color{color}{}
	~Light();

	float3& Color() { return color; }
	virtual float3 getLightInPoint(const float3& normal, const float3& eye) = 0;
protected:
	float3 position;
	float3 color;
};

