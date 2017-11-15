#include "stdafx.h"
#include "VertexProcesor.h"
#include <cmath>

float3 VertexProcesor::tr(const float3 & v)
{
	float4x4 obj2view = mul(world2view, obj2world);
	float4 res = mul(obj2view, float4{ v, 1 });
	res = mul(view2proj, res);

	//rendering chaining[View To Projection]x[World To View]x[Model to World]
	/*float4x4 world2proj = mul(mul(view2proj, world2view), obj2world);
	float4 res = mul(world2proj, { v, 1 });*/

	//std::cout << "v: " << res << "\n";
	return (float3)res;
}

void VertexProcesor::setPerspective(float fovy, float aspect, float near, float far)
{
	fovy *= PI / 360.f;
	float f = cosf(fovy) / sinf(fovy);
	view2proj[0] = float4{ f / aspect,	0, 0, 0 };
	view2proj[1] = float4{ 0, f, 0, 0 };
	view2proj[2] = float4{ 0, 0, (far+near) / (near-far), -1.f };
	view2proj[3] = float4{ 0, 0, 2*far*near / (near-far), 0 };
}

void VertexProcesor::setLookat(const float3 & eye, const float3 & center, const float3 & up)
{
	float3 f = center - eye;
	f.normalize();
	float3 upV = up.getNormalized();
	float3 s = crossProduct(f, upV);
	float3 u = crossProduct(s, f);

	world2view[0] = float4{ s[0], u[0], -f[0], 0 };
	world2view[1] = float4{ s[1], u[1], -f[1], 0 };
	world2view[2] = float4{ s[2], u[2], -f[2], 0 };
	world2view[3] = float4{ eye*(-1), 1 };
}

void VertexProcesor::multByTranslation(const float3 & v)
{
	float4x4 m{
		float4{1, 0, 0, 0},
		float4{0, 1, 0, 0},
		float4{0, 0, 1, 0},
		float4{v[0], v[1], v[2], 1}
	};
	obj2world = mul(m, obj2world);
}

void VertexProcesor::multByScale(const float3 & v)
{
	float4x4 m{
		float4{ v[0], 0, 0, 0 },
		float4{ 0, v[1], 0, 0 },
		float4{ 0,  0,v[2], 0 },
		float4{ 0,	0, 0,	1 }
	};
	obj2world = mul(m, obj2world);
}

void VertexProcesor::multByRotation(const float a, const float3 & vec)
{
	float	s = sinf(a * PI / 180.f),
			c = cosf(a * PI / 180.f);
	auto v = vec.getNormalized();
	float4x4 m{
		float4{ v.x*v.x*(1-c) + c,	 v.y*v.x*(1 - c) + v.z*s, v.x*v.z*(1 - c) - v.y*s, 0 },
		float4{ v.x*v.y*(1-c)-v.z*s, v.y*v.y*(1 - c) + c,	  v.y*v.z*(1 - c) + v.x*s, 0 },
		float4{ v.x*v.z*(1-c)+v.y*s, v.y*v.z*(1 - c) - v.x*s, v.z*v.z*(1-c)+c,		   0 },
		float4{ 0, 0, 0, 1 }
	};
	obj2world = mul(m, obj2world);
}


VertexProcesor::VertexProcesor(float fovy, float aspect, float near, float far, 
	const float3 & eye, const float3 & center, const float3 & up)
{
	obj2world = float4x4{
		float4{1,0,0,0},
		float4{0,1,0,0},
		float4{0,0,1,0},
		float4{0,0,0,1}
	};
	setPerspective(fovy, aspect, near, far);
	setLookat(eye, center, up);
}

VertexProcesor::~VertexProcesor()
{
	
}
