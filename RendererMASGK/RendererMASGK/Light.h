#pragma once
class Light
{
public:
	Light(const class VertexProcesor* vp, const float3& position, const float3& color, const float3& ambient);
	Light() : Light(nullptr, { 0,0,0 }, { 0,0,0 }, { 0,0,0 }) {};
	~Light();

	float3& Position() { return position; }
	float3& Color() { return color; }
	virtual float3 getLightInPoint(const float3& normal, const float3& eye, const Material& mat) = 0;
protected:
	float3 position;
	float3 color;
	float3 ambient;
};

