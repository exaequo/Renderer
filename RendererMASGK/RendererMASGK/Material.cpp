#include "stdafx.h"
#include "Material.h"

int Material::currentMaterialID = 0;

Material::Material() : Material({ 1,1,1 }) {}

Material::Material(const float3 & color) :colorDiffuse{ color } 
{
	materialID = currentMaterialID++;
	ObjectHolder::Instance().materials.push_back(this);
}


