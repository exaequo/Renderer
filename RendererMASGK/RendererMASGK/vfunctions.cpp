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

float float3::magnitude() const
{
	return sqrtf(x*x + y*y + z*z);
}

float3& float3::normalize()
{
	float mag = magnitude();
	for (int i = 0; i < 3; ++i)
	{
		(*this)[i] /= mag;
	}
	return (*this);
}

float3 float3::getNormalized() const
{
	float3 f{ (*this) };
	float mag = magnitude();

	for (int i = 0; i < 3; ++i)
	{
		f[i] /= mag;
	}

	return f;
}

float3 & float3::operator+(const float3 & other)
{
	this->x += other.x;
	this->y += other.y;
	this->z += other.z;
	
	return *this;
}

float3 & float3::operator-(const float3 &other)
{
	this->x -= other.x;
	this->y -= other.y;
	this->z -= other.z;

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

	return *((&x) + n);
}

const float & float3::operator[](const int n) const
{
	if (n < 0 || n > 2) { throw std::exception("out of float3 range"); }

	return *((&x) + n);
}

std::ostream & operator<<(std::ostream & stream, const float4x4 &obj)
{
	for (int i = 0; i < 4; ++i) { stream << "|" << obj[i] << "|\n"; }
	return stream;
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

float3 operator-(const float3 & lhs, const float3 & rhs)
{
	return float3{
		lhs.x - rhs.x,
		lhs.y - rhs.y,
		lhs.z - rhs.z
	};
}

float3 operator*(const float lhs, const float3 & rhs)
{
	return float3{ rhs.x * lhs, rhs.y * lhs, rhs.z * lhs };
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

float4x4 mul(const float4x4 & l, const float4x4 & r)
{
	float4x4 result{};

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			result[i][j] = 0;
			for (int iter = 0; iter < 4; ++iter)
			{
				result[i][j] += l[i][iter] * r[iter][j];
			}
		}
	}

	return result;
}

float4 mul(const float4x4 & l, const float4 & r)
{
	float4 result{};
	for (int i = 0; i < 4; ++i)
	{
		result[i] = 0.f;
		for (int j = 0; j < 4; ++j)
		{
			result[i] += l[i][j] * r[j];
		}
	}
	return result;
}

std::ostream & operator<<(std::ostream & stream, const float4 &val)
{
	stream << "[" << val.x << "," << val.y << "," << val.z << "," << val.w <<"]";
	return stream;
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
	
	return *((&x) + n);
}

const float & float4::operator[](const int n) const
{
	if (n < 0 || n > 3) { throw std::exception("out of float4 range"); }

	return *((&x) + n);
}

float4x4::float4x4()
{
	for (int i = 0; i < 4; ++i) { arr[i] = float4{}; }
}

float4x4::float4x4(const float4 &f1, const float4 &f2, const float4 &f3, const float4 &f4)
{
	arr[0] = f1;
	arr[1] = f2;
	arr[2] = f3;
	arr[3] = f4;
}

float4x4::float4x4(float v)
{
	for (int i = 0; i < 4; ++i) { arr[i] = float4{ v,v,v,v }; }
}

float4 & float4x4::operator[](const int n)
{
	if (n > 3 || n < 0) { throw new std::exception{ "***float4x4: n too big\n" }; }
	return arr[n];
}

const float4 & float4x4::operator[](const int n) const
{
	if (n > 3 || n < 0) { throw new std::exception{ "***float4x4: n too big\n" }; }
	return arr[n];
}
