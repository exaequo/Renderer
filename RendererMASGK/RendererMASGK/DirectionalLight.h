#pragma once
#include "Light.h"
class DirectionalLight :
	public Light
{
public:
	DirectionalLight(const float3& dir, const float3& color) :Light{ {0,0,0}, color }, dir{ dir } {}
	~DirectionalLight();

private:
	float3 dir;
};

