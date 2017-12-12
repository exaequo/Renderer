#include "stdafx.h"
#include "ToonShader.h"


ToonShader::ToonShader()
{
}


ToonShader::~ToonShader()
{
}

Vertex ToonShader::tr(const Vertex & v, const VertexProcesor & vp) const
{
	return vp.tr(v);
}

float3 ToonShader::lt(const Vertex & v, const Material & mat, const VertexProcesor & vp) const
{
	float3 color = vp.lt(v,mat);

	float intensity = color.magnitude();
	float newIntensity = 0;

	if (intensity >= .25f && intensity < .5f) { newIntensity = 0.25f; }
	if (intensity >= .5f && intensity < .75f) { newIntensity = 0.5f; }
	if (intensity >= .75f && intensity < 1.f) { newIntensity = 0.75f; }
	if (intensity > 1.f) { newIntensity = 1; }

	color = color / intensity * newIntensity;

	return color;
}

