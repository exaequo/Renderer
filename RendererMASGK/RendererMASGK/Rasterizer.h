#pragma once
#include "stdafx.h"
class Rasterizer
{
public:
	
	Rasterizer(Buffer& buff);
	~Rasterizer();
	void Triangle(const float3& p1, const float3& p2, const float3& p3,
				  const float3& c1, const float3& c2, const float3& c3);

};

