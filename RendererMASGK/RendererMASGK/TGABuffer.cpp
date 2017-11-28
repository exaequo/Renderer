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

bool TgaBuffer::loadTexture(const std::string & name)
{
	return false;
}


