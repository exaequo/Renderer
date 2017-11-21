#include "stdafx.h"
#include "Vertex.h"


Vertex::~Vertex()
{
}

float3 Vertex::getPosition() const
{
	return position;
}

float3 Vertex::getNormal() const
{
	return normal;
}
