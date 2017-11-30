#pragma once
#include "Buffer.h"
#include <string>
#include <map>

class TgaBuffer :
	public Buffer
{
public:
	TgaBuffer(int width, int height, float depth) : Buffer(width, height, depth) {};
	~TgaBuffer();

	bool save(const std::string name) const;
	static bool loadTexture(const std::string& filename, const std::string& textureName);
	
	
	//static void changeMaterialToTextureConnection(const int materialID, const std::string& texID);
//private:
	
	//static std::map<int, std::string> materialsToTextureNames;
};

