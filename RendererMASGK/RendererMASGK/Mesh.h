#pragma once
#include <vector>
#include "Material.h"
class Mesh
{
public:
	Mesh() {}

	~Mesh();

	virtual void draw(Rasterizer& rast, const VertexProcesor& vp) const = 0;
	virtual void makeNormals() = 0;
	Material& getMaterial() { return material; }

protected:
	std::vector<Vertex> vertices;
	std::vector<int3> indices;
	Material material;
};

