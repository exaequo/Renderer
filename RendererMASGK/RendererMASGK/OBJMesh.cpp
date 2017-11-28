#include "stdafx.h"
#include "OBJMesh.h"
#include <fstream>


OBJMesh::OBJMesh(const std::string & fileName)
{
	loadFromFile(fileName);
}

OBJMesh::~OBJMesh()
{
}

void OBJMesh::loadFromFile(const std::string & fileName)
{
	using namespace std;

	string token;
	string stringValue;
	ifstream objFile(fileName + ".obj");
	ifstream mtlFile(fileName + ".mtl");

	float3 vectorValue;
	char delimeter = ' ';
	vector<string> objFileTokens;
	vector<string> mtlFileTokens;

	if (mtlFile.is_open())
	{
		while (mtlFile >> token)
		{
			mtlFileTokens.push_back(token);
		}

		mtlFile.close();
	}
	else
	{
		cout << "Unable to open file: " << fileName << ".mtl" << endl;
		throw std::exception("mtl file open excepttion");
	}

	if (objFile.is_open())
	{
		while (objFile >> token)
		{
			objFileTokens.push_back(token);
		}

		objFile.close();
	}
	else
	{
		cout << "Unable to open file: " << fileName << ".obj" << endl;
		throw std::exception("obj file open excepttion");
	}

	//LOADING MATERIALS
	Material* currentMat{};
	size_t count = mtlFileTokens.size();
	int i = 0;
	while (i < count)
	{
		if (mtlFileTokens[i] == "newmtl")
		{
			materials.push_back(Material {});
			currentMat = &materials[materials.size() - 1];
			currentMat->Name() = mtlFileTokens[i + 1];
			i += 2;
			continue;
		}

		if (mtlFileTokens[i] == "Ns")
		{
			currentMat->Ns() = stof(mtlFileTokens[i + 1]);
			i += 2;
			continue;
		}
		if (mtlFileTokens[i] == "Ni")
		{
			currentMat->Ni() = stof(mtlFileTokens[i + 1]);
			i += 2;
			continue;
		}
		if (mtlFileTokens[i] == "d")
		{
			currentMat->D() = stof(mtlFileTokens[i + 1]);
			i += 2;
			continue;
		}
		if (mtlFileTokens[i] == "Tr")
		{
			currentMat->Tr() = stof(mtlFileTokens[i + 1]);
			i += 2;
			continue;
		}
		if (mtlFileTokens[i] == "Tf")
		{
			currentMat->Tf() = { stof(mtlFileTokens[i + 1]), stof(mtlFileTokens[i + 2]), stof(mtlFileTokens[i + 3]) };
			i += 4;
			continue;
		}
		if (mtlFileTokens[i] == "illum")
		{
			currentMat->Illum() = stof(mtlFileTokens[i + 1]);
			i += 2;
			continue;
		}
		if (mtlFileTokens[i] == "Ka")
		{
			currentMat->ColorAmbient() = { stof(mtlFileTokens[i + 1]), stof(mtlFileTokens[i + 2]), stof(mtlFileTokens[i + 3]) };
			i += 4;
			continue;
		}
		if (mtlFileTokens[i] == "Kd")
		{
			currentMat->ColorDiffuse() = { stof(mtlFileTokens[i + 1]), stof(mtlFileTokens[i + 2]), stof(mtlFileTokens[i + 3]) };
			i += 4;
			continue;
		}
		if (mtlFileTokens[i] == "Ks")
		{
			currentMat->ColorSpecular() = { stof(mtlFileTokens[i + 1]), stof(mtlFileTokens[i + 2]), stof(mtlFileTokens[i + 3]) };
			i += 4;
			continue;
		}
		if (mtlFileTokens[i] == "Ke")
		{
			currentMat->ColorEmissive() = { stof(mtlFileTokens[i + 1]), stof(mtlFileTokens[i + 2]), stof(mtlFileTokens[i + 3]) };
			i += 4;
			continue;
		}

		++i;
	}
	//LOADING TRIANGLES
	count = objFileTokens.size();
	i = 0;

	while (i < count)
	{
		if (objFileTokens[i] == "v")
		{
			positions.push_back({ stof(objFileTokens[i + 1]), stof(objFileTokens[i + 2]), stof(objFileTokens[i + 3]) });
			i += 4;
			continue;
		}
	
	
		if (objFileTokens[i] == "vn")
		{
			normals.push_back({ stof(objFileTokens[i + 1]), stof(objFileTokens[i + 2]), stof(objFileTokens[i + 3]) });
			i += 4;
			continue;
		}

		if (objFileTokens[i] == "vt")
		{
			textureCoord.push_back({ stof(objFileTokens[i + 1]), stof(objFileTokens[i + 2]), stof(objFileTokens[i + 3]) });
			i += 4;
			continue;
		}

		if (objFileTokens[i] == "usemtl")
		{
			for (Material &mat : materials)
			{
				if (mat.Name() == objFileTokens[i + 1])
				{
					currentMat = &mat;
				}
			}
		}

		if (objFileTokens[i] == "f")
		{
			std::vector<Vertex> triangleVertices{};

			for (int j = 1; j < 4; ++j)
			{
				std::vector<std::string> values = divideLine(objFileTokens[i + j], '/');
				triangleVertices.push_back(Vertex{
					{positions.at(stoi(values[0]) - 1)},	//position
					{normals.at(stoi(values[2]) - 1)},		//normals
					{textureCoord.at(stoi(values[1]) - 1)}  //tex coord
				});

				//std::cout << values.size() << ", ";
			}

			triangles.push_back(SimpleTriangle{
				triangleVertices[0], 
				triangleVertices[1],
				triangleVertices[2],
				*currentMat
			});

			i += 4;
			continue;
		}

		++i;
	}
}

void OBJMesh::draw(Rasterizer & rast, const VertexProcesor & vp) const
{
	for (auto tr : triangles)
	{
		tr.draw(rast, vp);
	}
}

void OBJMesh::makeNormals()
{
}
