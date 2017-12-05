#include "stdafx.h"
#include "DirectionalLight.h"
#include <algorithm>

DirectionalLight::DirectionalLight(const VertexProcesor * vp, const float3 & dir, const float3 & color, const float3 & ambient) : 
	Light{ vp,{ 0,0,0 }, color, ambient }, dir{ dir }
{
	if (vp) {
		//this->dir = vp->tr(dir);
		this->dir = (float3)mul(mul(vp->world2view, vp->view2proj), { this->dir,0 });
		this->dir.normalize();//
	}
}

DirectionalLight::~DirectionalLight()
{
}

const float3 & DirectionalLight::getDir() const
{
	return dir;
}

//float3 DirectionalLight::getLightInPoint(const float3 & normal, const float3 & pos, const Material& mat)
//{
//	float3 res{};
//	float3 spec{};
//	float intensity = std::max(dotProduct(normal, -1.f * dir), 0.f);
//
//	if (intensity > 0.f)
//	{
//		float3 eye = (-1.f * pos).normalize();
//		float3 h = (eye - dir).normalize();
//
//		float intSpec = std::max(dotProduct(h, normal), 0.f);
//		spec = mat.getColorSpecular() * pow(intSpec, mat.getNs());
//	}
//	res = intensity * color * mat.getColorDiffuse() + spec;
//	
//	res.normalizeColor();
//	std::cout << "i: "<< intensity <<", s: " << spec << "\n";
//	return res;
//}
