#include "stdafx.h"
#include "vfunctions.h"
#include <algorithm>

unsigned int float3::ColorARGB() const
{
	return ((unsigned char)(r * 255)) * 65536 + (unsigned char)(g * 255) * 256 + (unsigned char)(b * 255);
}

float3 & float3::operator+(const float3 & other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	
	return *this;
}

float3 & float3::operator*(const float value)
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

float & float3::operator[](int n)
{
	n = (n < 0) ? 0 : n;
	n = (n > 2) ? 2 : n;

	switch (n)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	}
}

int Min(int v1, int v2, int v3)
{
	return std::min(v1, std::min(v2, v3));
}

int Max(int v1, int v2, int v3)
{
	return std::max(v1, std::max(v2, v3));
}

float3 operator*(const float3 & lhs, const float rhs)
{
	float3 res{ lhs.x, lhs.y, lhs.z };
	res.x *= rhs;
	res.y *= rhs;
	res.z *= rhs;
	return res; 
}
