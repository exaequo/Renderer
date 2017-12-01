#include "stdafx.h"
#include "ObjectHolder.h"

ObjectHolder::~ObjectHolder()
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

ObjectHolder & ObjectHolder::Instance()
{
	static ObjectHolder instance;
	return instance;
}

Texture * ObjectHolder::getTexture(const std::string & name)
{
	if (textures.find(name) == textures.end())
	{
		return nullptr;
	}
	return (textures[name]);
}
