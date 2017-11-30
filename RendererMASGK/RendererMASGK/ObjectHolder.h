#pragma once
class ObjectHolder
{
public:
	ObjectHolder() {}
	~ObjectHolder() {}
	ObjectHolder(const ObjectHolder&) = delete;
	ObjectHolder & operator=(const ObjectHolder&) = delete;

	static ObjectHolder& Instance();
	
	class Texture * getTexture(const std::string& name);

	//int materialsSize() const { return materials.size(); }
	//int texturesSize() const { return textures.size(); }

//private:
	std::vector<class Material *> materials;
	std::map<std::string, class Texture *> textures;

	friend class TgaBuffer;
	friend class Material;
};

