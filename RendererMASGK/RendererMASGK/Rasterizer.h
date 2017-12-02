#pragma once
#include "stdafx.h"

class Rasterizer
{
public:
	
	Rasterizer(Buffer& buff) : buffer{ buff } {}
	~Rasterizer();
	void Triangle(
		const float3& p1,	const float3& p2,	const float3& p3,
		const float3& tc1,	const float3& tc2,	const float3& tc3,
		const float3& n1,	const float3& n2,	const float3& n3,
		const float3& c1,	const float3& c2,	const float3& c3,
		class Material* mat
	);

	//void Triangle(const class Vertex & v1 , const class Vertex& v2, const class Vertex& v3 , const class Material& mat);
protected:
	Buffer &buffer;

};

