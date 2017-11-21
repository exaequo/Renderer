#pragma once
#include "Mesh.h"
class SimpleTriangle :
	public Mesh
{
public:
	SimpleTriangle(const float3& p1, const float3& p2, const float3& p3);
		
	~SimpleTriangle();

	virtual void draw(Rasterizer& rast, const VertexProcesor& vp) const;
	virtual void makeNormals();
};

