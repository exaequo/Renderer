#pragma once
#include "Mesh.h"
class SimpleTriangle :
	public Mesh
{
public:
	SimpleTriangle(const float3& p1, const float3& p2, const float3& p3);
	SimpleTriangle(const Vertex& v1, const Vertex& v2, const Vertex& v3, const Material& material);

	~SimpleTriangle();

	virtual void draw(Rasterizer& rast, const VertexProcesor& vp) const;
	virtual void makeNormals();
};

