#pragma once
class Vertex
{
public:
	Vertex(const float3& position) : position{ position } {}
	Vertex(const float3& position, const float3& normal) : position{ position }, normal{ normal } {}
	Vertex(const float3& position, const float3& normal, const float3& texCoord) : position{ position }, normal{ normal }, texCoord{ texCoord } {}
	Vertex(const float3& position, const float3& normal, const float3& texCoord, const float3& tangent, const float3& bitangent) : position{ position }, normal{ normal }, texCoord{ texCoord }, tangent{ tangent }, bitangent{ bitangent } {}
	~Vertex();

	const float3& getPosition() const;
	const float3& getTexCoord() const;
	const float3& getNormal() const;

private:
	float3 position;
	float3 normal;
	float3 texCoord;
	float3 tangent;
	float3 bitangent;
	friend VertexProcesor;
};

typedef Vertex Fragment;

