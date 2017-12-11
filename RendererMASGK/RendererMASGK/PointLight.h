#pragma once
#include "Light.h"
class PointLight :
	public Light
{
public:
	PointLight(const class VertexProcesor * vp, const float3& pos, const float3& color, const float3& ambient);
	~PointLight();

	virtual const float3& getDir() const { return { 0,0,0 }; }
	virtual const float3& getPos() const { return position; }
	virtual const LightType getType() const { return LightType::Point; }
};

