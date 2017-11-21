#include "stdafx.h"
#include "SimpleTriangle.h"




SimpleTriangle::SimpleTriangle(const float3 & p1, const float3 & p2, const float3 & p3)
{
	vertices.push_back(Vertex{ p1,{ 0,0,0 } });
	vertices.push_back(Vertex{ p2,{ 0,0,0 } });
	vertices.push_back(Vertex{ p3,{ 0,0,0 } });

	indices = { { 0,1,2 } };
}

SimpleTriangle::~SimpleTriangle()
{
}

void SimpleTriangle::draw(Rasterizer & rasterizer, const VertexProcesor & vp) const
{
	rasterizer.Triangle(vp.tr(vertices[0].getPosition()), vp.tr(vertices[1].getPosition()), vp.tr(vertices[2].getPosition()),
	material.color, material.color, material.color);
}

void SimpleTriangle::makeNormals()
{
}
