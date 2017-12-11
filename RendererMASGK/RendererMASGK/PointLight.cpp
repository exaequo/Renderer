#include "stdafx.h"
#include "PointLight.h"



PointLight::PointLight(const VertexProcesor * vp, const float3 & pos, const float3 & color, const float3 & ambient)
	:Light(vp,pos,color,ambient)
{

}

PointLight::~PointLight()
{
}
