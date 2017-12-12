#pragma once
#include "Shader.h"
class ToonShader :
	public Shader
{
public:
	ToonShader();
	~ToonShader();

	virtual class Vertex tr(const class Vertex & v, const VertexProcesor& vp) const;

	virtual float3 lt(const class Vertex& v, const Material& mat, const VertexProcesor& vp) const;
};

