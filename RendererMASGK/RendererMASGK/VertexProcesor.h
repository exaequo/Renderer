#pragma once
class VertexProcesor
{
public:
	float4x4 obj2world;
	float4x4 world2view;
	float4x4 view2proj;

	float3 tr(const float3& v);
	void lt();

	void setPerspective(float fovy, float aspect, float near, float far);
	void setLookat(const float3& eye, const float3& center, const float3& up);
	void multByTranslation(const float3& v);
	void multByScale(const float3& v);
	void multByRotation(const float a, const float3& v);

	VertexProcesor(float fovy, float aspect, float near, float far, 
		const float3& eye, const float3& center, const float3& up);
	~VertexProcesor();
};

