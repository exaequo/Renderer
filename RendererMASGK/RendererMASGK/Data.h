#pragma once
class Data
{
public:
	Data() {}
	~Data();
	Data(const Data&) = delete;
	Data & operator=(const Data&) = delete;

	static Data& Instance();
	
	class Texture * getTexture(const std::string& name);
	const std::vector<class Light*> & getLights() const { return lights; }
	float3& AmbientLight() { return ambientLight; }
	const float3& getAmbientLight() const { return ambientLight; }

	//int materialsSize() const { return materials.size(); }
	//int texturesSize() const { return textures.size(); }

private:
	std::vector<class Material *> materials;
	std::map<std::string, class Texture *> textures;
	std::vector<class Light*> lights;
	
	float3 ambientLight;

	friend class Texture;
	friend class Material;
	friend class Light;
};

