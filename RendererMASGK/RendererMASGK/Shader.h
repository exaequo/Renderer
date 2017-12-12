#pragma once
class Shader
{
public:
	Shader();
	~Shader();
	virtual class Vertex tr(const class Vertex & v, const VertexProcesor& vp) const = 0;

	virtual float3 lt(const class Vertex& v, const Material& mat, const VertexProcesor& vp) const = 0;
};

