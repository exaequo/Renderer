#pragma once
class Vertex
{
public:
	Vertex(const float3& position) : position{ position } {}
	Vertex(const float3& position, const float3& normal) : position{ position }, normal{ normal } {}
	Vertex(const float3& position, const float3& normal, const float3& texCoord) : position{ position }, normal{ normal }, texCoord{ texCoord } {}
	~Vertex();

	float3 getPosition() const;
	float3 getNormal() const;
private:
	float3 position;
	float3 normal;
	float3 texCoord;
};

typedef Vertex Fragment;

