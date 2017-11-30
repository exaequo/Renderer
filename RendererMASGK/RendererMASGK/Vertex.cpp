#include "stdafx.h"
#include "Vertex.h"


Vertex::~Vertex()
{
}

const float3 & Vertex::getPosition() const
{
	return position;
}

const float3 & Vertex::getTexCoord() const
{
	return texCoord;
}

const float3 & Vertex::getNormal() const
{
	return normal;
}
