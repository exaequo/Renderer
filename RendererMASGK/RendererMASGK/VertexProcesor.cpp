#include "stdafx.h"
#include "VertexProcesor.h"
#include <cmath>
#include <algorithm>

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
float3 VertexProcesor::lt(const Vertex & v, const Material& mat) const
{
	float3 col{};// = mat.getColorDiffuse();
	float3 n{ v.getNormal() };
	float3 tex{ 1,1,1 };

	if (mat.getTexture())
	{
		tex = mat.getTexture()->getColor(v.getTexCoord());
	}

	if (mat.getNormal())
	{
		n *= mat.getNormal()->getColor(v.getTexCoord());
	}
	n.normalize();

	for (auto * light : Data::Instance().getLights())
	{
		float3 res{};
		float3 spec{};
		float intensity = std::max(dotProduct(n, -1.f * light->getDir()), 0.f);

		if (intensity > 0.f)
		{
			float3 eye = v.getPosition().getNormalized();
			float3 h = (eye - light->getDir()).normalize();

			float intSpec = std::max(dotProduct(h, n), 0.f);
			spec = mat.getColorSpecular() * pow(intSpec, mat.getNs());
			spec *= light->Specular();
		}
		float3 diff = tex * mat.getColorDiffuse();

		res = intensity * light->Color() * diff + spec;

		res.normalizeColor();

		col += res;
	}

	/*if (mat.getTexture())
	{
		col *= mat.getTexture()->getColor(v.getTexCoord());
	}*/
	col += Data::Instance().getAmbientLight() * mat.getColorAmbient() * tex;

	col.normalizeColor();
	return col;
}


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

float3 VertexProcesor::transformNormal(const float3 & norm) const
{
	float4 n{ norm, 0.f };

	n = mul(normal, n);

	float3 res{ n.x, n.y, n.z };

	return res.getNormalized();
}



void VertexProcesor::calculateMatrices()
{
	obj2view = mul(world2view, obj2world);
	obj2proj = mul(view2proj, obj2view);
	//normal = float4x4::identity();
	normal = obj2view.inverse().transpose();// .inverse();//.inverse().transpose();
}
