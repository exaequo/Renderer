#include "stdafx.h"
#include "vfunctions.h"

float3 & float3::operator+(const float3 & other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	
	return *this;
}

float3 & float3::operator*(float value)
{
	this->x *= value;
	this->y *= value;
	this->z *= value;

	return *this;
}

float3 & float3::operator*(const float3 & other)
{
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;

	return *this;
}
