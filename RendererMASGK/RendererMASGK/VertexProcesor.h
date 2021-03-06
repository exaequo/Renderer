#pragma once
class VertexProcesor
{
public:
	float4x4 obj2world;
	float4x4 world2view;
	float4x4 view2proj;
	float4x4 obj2view;
	float4x4 obj2proj;
	float4x4 normal;

	float3 tr(const float3& v) const;
	class Vertex tr(const class Vertex & v) const;
	//class Vertex lt(const class Vertex & f) const;
	float3 lt(const class Vertex& v, const Material& mat) const;

	class Vertex shaderTr(const class Vertex & v, class Shader* shader) const;
	float3 shaderLt(const class Vertex& v, const Material& mat, class Shader* shader) const;

	void setPerspective(float fovy, float aspect, float near, float far);
	void setLookat(const float3& eye, const float3& center, const float3& up);
	void multByTranslation(const float3& v);
	void multByScale(const float3& v);
	void multByRotation(const float a, const float3& v);

	void clearTransformations();

	float3 transformNormal(const float3& norm) const;

	VertexProcesor(float fovy, float aspect, float near, float far, 
		const float3& eye, const float3& center, const float3& up);
	~VertexProcesor();

	void calculateMatrices();

	friend class Shader;
};

