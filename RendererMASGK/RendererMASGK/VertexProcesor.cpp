#include "stdafx.h"
#include "VertexProcesor.h"
#include <cmath>

VertexProcesor::VertexProcesor(float fovy, float aspect, float near, float far,
	const float3 & eye, const float3 & center, const float3 & up)
{
	obj2world = float4x4{
		float4{ 1,0,0,0 },
		float4{ 0,1,0,0 },
		float4{ 0,0,1,0 },
		float4{ 0,0,0,1 }
	};
	setPerspective(fovy, aspect, near, far);
	setLookat(eye, center, up);
	calculateMatrices();
}

VertexProcesor::~VertexProcesor()
{

}

float3 VertexProcesor::tr(const float3 & v) const
{
	float4 result = mul(obj2proj, { v, 1 });

	return (float3)result / result.w;
}

Vertex VertexProcesor::tr(const Vertex & v) const
{
	Vertex res{ v };

	res.position = tr( v.position );
	//return Vertex();
	return res;
}
float3 VertexProcesor::lt(const Vertex & v) const
{
	return float3();
}
//
//Vertex VertexProcesor::lt(const Vertex & f) const
//{
//	Vertex res{ f };
//	
//
//
//	return res;
//}



void VertexProcesor::setPerspective(float fovy, float aspect, float near, float far)
{
	fovy *= (float)PI / 360.f;
	float f = cosf(fovy) / sinf(fovy);
	/*
	view2proj[0] = float4{ f / aspect,	0, 0, 0 };
	view2proj[1] = float4{ 0, f, 0, 0 };
	view2proj[2] = float4{ 0, 0, (far+near) / (near-far), -1.f };
	view2proj[3] = float4{ 0, 0, 2*far*near / (near-far), 0 };*/

	view2proj[0] = float4{ f / aspect,	0, 0, 0 };
	view2proj[1] = float4{ 0, f, 0, 0 };
	view2proj[2] = float4{ 0, 0, (far + near) / (near - far), 2 * far*near / (near - far) };
	view2proj[3] = float4{ 0, 0, -1.f, 0 };

	calculateMatrices();

	//std::cout << "view2proj:\n" << view2proj << "\n";
}

void VertexProcesor::setLookat(const float3 & eye, const float3 & center, const float3 & upVector)
{
	/*float3 f = center - eye;
	f.normalize();
	float3 upV = upVector.getNormalized();
	float3 s = crossProduct(f, upV);
	float3 u = crossProduct(s, f);

	world2view[0] = float4{ s[0], u[0], -f[0], 0 };
	world2view[1] = float4{ s[1], u[1], -f[1], 0 };
	world2view[2] = float4{ s[2], u[2], -f[2], 0 };
	world2view[3] = float4{ -1 * eye, 1 };*/

	float3 forward = eye - center;
	forward.normalize();

	float3 left = crossProduct(upVector, forward);
	left.normalize();

	float3 up = crossProduct(forward, left);

	world2view = {
		float4{ left.x,		left.y,		left.z,		-dotProduct(left, eye) },
		float4{ up.x,		up.y,		up.z,		-dotProduct(up, eye) },
		float4{ forward.x,	forward.y,	forward.z,	-dotProduct(forward, eye) },
		float4{ 0,			0,			0,			1 }
	};

	calculateMatrices();

	//std::cout << "world2view:\n" << world2view << "\n";
}

void VertexProcesor::multByTranslation(const float3 & v)
{
	float4x4 m{
		float4{1, 0, 0, v[0]},
		float4{0, 1, 0, v[1]},
		float4{0, 0, 1, v[2]},
		float4{0, 0, 0, 1}
	};
	/*float4x4 m{
		float4{ 1, 0, 0, 0 },
		float4{ 0, 1, 0, 0 },
		float4{ 0, 0, 1, 0 },
		float4{ v, 1 }
	};*/

	obj2world = mul(obj2world, m);
	calculateMatrices();
}

void VertexProcesor::multByScale(const float3 & v)
{
	float4x4 m{
		float4{ v[0], 0, 0, 0 },
		float4{ 0, v[1], 0, 0 },
		float4{ 0,  0,v[2], 0 },
		float4{ 0,	0, 0,	1 }
	};
	obj2world = mul(obj2world, m);
	calculateMatrices();
}

void VertexProcesor::multByRotation(const float a, const float3 & vec)
{
	float	s = sinf(a * (float)PI / 180.f),
			c = cosf(a * (float)PI / 180.f);
	auto v = vec.getNormalized();
	/*float4x4 m{
		float4{ v.x*v.x*(1-c) + c,	 v.y*v.x*(1 - c) + v.z*s, v.x*v.z*(1 - c) - v.y*s, 0 },
		float4{ v.x*v.y*(1-c)-v.z*s, v.y*v.y*(1 - c) + c,	  v.y*v.z*(1 - c) + v.x*s, 0 },
		float4{ v.x*v.z*(1-c)+v.y*s, v.y*v.z*(1 - c) - v.x*s, v.z*v.z*(1-c)+c,		   0 },
		float4{ 0, 0, 0, 1 }
	};*/

	float4x4 m{
		float4{ v.x*v.x*(1 - c) + c,	 v.x*v.y*(1 - c) - v.z*s, v.x*v.z*(1 - c) + v.y*s, 0 },
		float4{ v.x*v.y*(1 - c) + v.z*s, v.y*v.y*(1 - c) + c,	  v.y*v.z*(1 - c) - v.x*s, 0 },
		float4{ v.x*v.z*(1 - c) - v.y*s, v.y*v.z*(1 - c) + v.x*s, v.z*v.z*(1 - c) + c,	   0 },
		float4{ 0, 0, 0, 1 }
	};
	//std::cout << "m:\n" << m << "\n";

	obj2world = mul(obj2world, m);
	calculateMatrices();
}



void VertexProcesor::calculateMatrices()
{
	obj2view = mul(world2view, obj2world);
	obj2proj = mul(view2proj, obj2view);
	normal = obj2view.inverse().transpose();
}
