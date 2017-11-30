#include "stdafx.h"
#include "SimpleTriangle.h"




SimpleTriangle::SimpleTriangle(const float3 & p1, const float3 & p2, const float3 & p3)
{
	vertices.push_back(Vertex{ p1,{ 0,0,0 } });
	vertices.push_back(Vertex{ p2,{ 0,0,0 } });
	vertices.push_back(Vertex{ p3,{ 0,0,0 } });

	indices = { { 0,1,2 } };
}

SimpleTriangle::SimpleTriangle(const Vertex & v1, const Vertex & v2, const Vertex & v3, Material * material) 
{
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);

	this->material = material;
}

SimpleTriangle::~SimpleTriangle()
{
}

void SimpleTriangle::draw(Rasterizer & rasterizer, const VertexProcesor & vp) const
{
	//std::cout << "T: "<< material.getTextureID() << "\n";
	//std::cout << material->getColorDiffuse()<<"\n";
	rasterizer.Triangle(
		vp.tr(vertices[2].getPosition()), vp.tr(vertices[1].getPosition()), vp.tr(vertices[0].getPosition()),
		vertices[2].getTexCoord(), vertices[1].getTexCoord(), vertices[0].getTexCoord(),
		vertices[2].getNormal(), vertices[1].getNormal(), vertices[0].getNormal(),
		material, material->getTexture()
	);
}

void SimpleTriangle::makeNormals()
{
}
