#pragma once
#include "Buffer.h"
#include <string>
class TgaBuffer :
	public Buffer
{
public:
	TgaBuffer(int width, int height, float depth) : Buffer(width, height, depth) {};
	~TgaBuffer();

	bool save(const std::string name) const;

};

