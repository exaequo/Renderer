#pragma once
#include "Mesh.h"
class OBJMesh :
	public Mesh
{
public:
	OBJMesh(const std::string &fileName);
	~OBJMesh();
	OBJMesh(const OBJMesh&) = delete;

	void loadFromFile(const std::string &fileName);

	virtual void draw(Rasterizer& rast, const VertexProcesor& vp) const;
	virtual void makeNormals();

	virtual Material* getMaterial() { return materials[0]; }
	void setMaterial(Material* mat) { materials[0] = mat; }
private:
	std::vector<Material*> materials;
	std::vector<float3> positions;
	std::vector<float3> normals;
	std::vector<float3> textureCoord;
	std::vector<SimpleTriangle> triangles;
};

