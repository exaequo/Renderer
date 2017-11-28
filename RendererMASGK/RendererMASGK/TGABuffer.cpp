#include "stdafx.h"
#include "TGABuffer.h"
#include <fstream>
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

TgaBuffer::~TgaBuffer()
{
}

bool TgaBuffer::save(const std::string filename) const
{
	unsigned short header[9] =
	{
		0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0100, 0x0100, 0x0820
	};
	FILE *f;
	fopen_s(&f, filename.c_str(), "wb+");
	
	if (!f) return false;

	header[6] = width;
	header[7] = height;

	fwrite(header, 2, 9, f);
	fwrite(colorBuffer, 4, width * height, f);

	fclose(f);

	return true;
}

bool TgaBuffer::loadTexture(const std::string& filename, const std::string& textureName)
{
	unsigned short header[9] =
	{
		0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000,
		0x0100, 0x0100, 0x0820
	};
	FILE *f;
	fopen_s(&f, filename.c_str(), "rb+");
	if (!f) return false;

	fread(header, sizeof(unsigned short), 9, f);

	int width = header[6];
	int height = header[7];
	int len = width * height;
	unsigned int * texBuffer = new unsigned int[ len ];
	
	fread(texBuffer, sizeof(unsigned int), len, f);
	
	Texture txt{ width, height };
	for (int i = 0; i < len; ++i)
	{
		txt[i] = createColor(texBuffer[i]);
	}
	
	//textures[textureName] = txt;

	fclose(f);
	
}


