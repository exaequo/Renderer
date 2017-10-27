#include "stdafx.h"
#include "vfunctions.h"
#include <algorithm>

unsigned int float3::ColorRGB() const
{
	return ((unsigned char)(r * 255)) * 65536 + (unsigned char)(g * 255) * 256 + (unsigned char)(b * 255);
}

float float3::Dot(const float3 & other)
{
	return dotProduct(*this, other);
}

float3 float3::Cross(const float3 & other)
{
	return crossProduct(*this, other);
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

float & float3::operator[](const int n)
{
	if (n < 0 || n > 2) { throw std::exception("out of float3 range"); }

	switch (n)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	}
	throw std::exception("baderr");
}

int Min(int v1, int v2, int v3)
{
	return std::min(v1, std::min(v2, v3));
}

int Max(int v1, int v2, int v3)
{
	return std::max(v1, std::max(v2, v3));
}

float3 crossProduct(const float3 & l, const float3 & r)
{
	return float3{
		l.y * r.z - l.z * r.y,
		-(l.x * r.z - l.z * r.x),
		l.x * r.y - l.y * r.x
	};
}

float dotProduct(const float3 & lhs, const float3 & rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

float3 operator*(const float3 & lhs, const float rhs)
{
	float3 res{ lhs.x, lhs.y, lhs.z };
	res.x *= rhs;
	res.y *= rhs;
	res.z *= rhs;
	return res; 
}

std::ostream & operator<<(std::ostream & stream, const float3 &val)
{
	stream << "[" << val.x << "," << val.y << "," << val.z << "]";
	return stream;
}

unsigned int float4::ColorARGB() const
{
	return ((unsigned char)(a * 255) * 16777216 + (unsigned char)(r * 255) * 65536 + (unsigned char)(g * 255) * 256 + (unsigned char)(b * 255));
}

float4 operator*(const float4 & lhs, const float rhs)
{
	float4 res{ lhs };
	res.x *= rhs;
	res.y *= rhs;
	res.z *= rhs;
	res.w *= rhs;
	return res;
}

float4 & float4::operator+(const float4 &other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	this->w += other.w;

	return *this;
}

float4 & float4::operator*(const float val)
{
	this->x *= val;
	this->y *= val;
	this->z *= val;
	this->w *= val;

	return *this;
}

float4 & float4::operator*(const float4 &other)
{
	this->x *= other.x;
	this->y *= other.y;
	this->z *= other.z;
	this->w *= other.w;

	return *this;
}

float & float4::operator[](const int n)
{
	if (n < 0 || n > 3) { throw std::exception("out of float4 range"); }
	
	switch (n)
	{
	case 0:
		return x;
	case 1:
		return y;
	case 2:
		return z;
	case 3:
		return w;
	}

	throw std::exception("baderr");
}
