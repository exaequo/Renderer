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
		vp,
		vp.tr(vertices[0].getPosition()), vp.tr(vertices[1].getPosition()), vp.tr(vertices[2].getPosition()),
		vertices[0].getTexCoord(), vertices[1].getTexCoord(), vertices[2].getTexCoord(),
		vertices[0].getNormal(), vertices[1].getNormal(), vertices[2].getNormal(),
		//material->getColorDiffuse(), material->getColorDiffuse(), material->getColorDiffuse(),
		material
		//material, material->getTexture()
	);
}

void SimpleTriangle::drawInverse(Rasterizer & rasterizer, const VertexProcesor & vp) const
{
	/*Vertex v1 = vp.tr(vertices[0]);
	Vertex v2 = vp.tr(vertices[1]);
	Vertex v3 = vp.tr(vertices[2]);
	*/
	Vertex
		v1 = vertices[0],
		v2 = vertices[1],
		v3 = vertices[2];
	float3
		n1 = vp.transformNormal(v1.getNormal()),
		n2 = vp.transformNormal(v2.getNormal()),
		n3 = vp.transformNormal(v3.getNormal());
	//float3
	//	n1 = v1.getNormal(),
	//	n2 = v2.getNormal(),
	//	n3 = v3.getNormal();

	rasterizer.Triangle(
		vp,
		v3.getPosition(), v2.getPosition(), v1.getPosition(),
		v3.getTexCoord(), v2.getTexCoord(), v1.getTexCoord(),
		n3,n2,n1,
		//v3.getNormal(), v2.getNormal(), v1.getNormal(),
		//material->getColorDiffuse(), material->getColorDiffuse(), material->getColorDiffuse(),
		//{1,0,0},{0,1,0},{0,0,1},
		material
	);
}

void SimpleTriangle::makeNormals()
{
}
