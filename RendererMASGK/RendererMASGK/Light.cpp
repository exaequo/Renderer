#include "stdafx.h"
#include "Light.h"



//Light::Light(const float3 & position, const float3 & color) : position{ position }, color{ color }
//{
//
//}
//
//Light::Light() : Light({0,0,0}, {0,0,0})
//{
//}

Light::Light(const VertexProcesor * vp, const float3 & position, const float3 & color, const float3 & ambient) : position{ position }, color{ color }, ambient{ ambient }, specular{{1,1,1}}
{
	Data::Instance().lights.push_back(this);
	if (vp)
	{
		this->position = //mul(vp->world2view, this->position);
			vp->tr(this->position);
	}
}

Light::~Light()
{
}
