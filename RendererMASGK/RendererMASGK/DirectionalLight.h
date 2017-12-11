#pragma once
#include "Light.h"
class DirectionalLight :
	public Light
{
public:
	DirectionalLight(const class VertexProcesor * vp, const float3& dir, const float3& color, const float3& ambient);
	~DirectionalLight();

	float3& Dir() { return dir; }

	virtual const float3& getDir() const;
	virtual const float3& getPos() const { return { 0,0,0 }; }
	virtual const LightType getType() const { return LightType::Directional; }
	//virtual float3 getLightInPoint(const float3& normal, const float3& eye, const Material& mat);
private:
	float3 dir;
};

