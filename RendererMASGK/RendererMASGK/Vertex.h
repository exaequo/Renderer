#pragma once
class Vertex
{
public:
	Vertex(const float3& position, const float3& normal) : position{ position }, normal{ normal } {}
	~Vertex();

	float3 getPosition() const;
	float3 getNormal() const;
private:
	float3 position;
	float3 normal;
};

typedef Vertex Fragment;

