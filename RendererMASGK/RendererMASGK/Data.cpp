#include "stdafx.h"
#include "Data.h"

Data::~Data()
{
	for (auto obj : textures)
	{
		delete obj.second;
	}

	for (auto obj : materials)
	{
		delete obj;
	}
}

Data & Data::Instance()
{
	static Data instance;
	return instance;
}

Texture * Data::getTexture(const std::string & name)
{
	if (textures.find(name) == textures.end())
	{
		return nullptr;
	}
	return (textures[name]);
}
