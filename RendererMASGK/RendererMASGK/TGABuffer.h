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
	bool loadTexture(const std::string& filename, const std::string& textureName);

private:
	std::map<std::string, class Texture> textures;
};

