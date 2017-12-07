#include "stdafx.h"
#include "vfunctions.h"
#include <algorithm>
#include <sstream>

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

void float3::normalizeColor()
{
	for (int i = 0; i < 3; ++i)
	{
		if ((*this)[i] < 0.f) { (*this)[i] = 0.f; }
		if ((*this)[i] > 1.f) { (*this)[i] = 1.f; }
	}
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
	float3 r{*this};
	r.x += other.x;
	r.y += other.y;
	r.z += other.z;
	
	return r;
}

float3 & float3::operator-(const float3 &other)
{
	float3 r{*this};
	r.x -= other.x;
	r.y -= other.y;
	r.z -= other.z;

	return r;
}

float3 float3::operator-()
{
	return float3{ -x,-y,-z };
}

float3 & float3::operator*(const float value)
{
	float3 r{ *this };
	r.x *= value;
	r.y *= value;
	r.z *= value;
	return r;
}

float3 & float3::operator/(const float r)
{
	float3 res{ *this };
	for (int i = 0; i < 3; ++i) { res[i] /= r; }
	return res;
}

float3 & float3::operator*(const float3 & other) const
{
	float3 r{ *this };
	r.x *= other.x;
	r.y *= other.y;
	r.z *= other.z;

	return r;
}

float3 & float3::operator+=(const float3 &o)
{
	x += o.x;
	y += o.y;
	z += o.z;

	return *this;
}

float3 & float3::operator*=(const float3 &o)
{
	x *= o.x;
	y *= o.y;
	z *= o.z;

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

float3 max(const float3 & l, const float3 & r)
{
	if (l.magnitude() > r.magnitude())
	{
		return l;
	}
	else
	{
		return r;
	}
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

	/*for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			result[i][j] = 0;
			for (int iter = 0; iter < 4; ++iter)
			{
				result[i][j] += l[iter][i] * r[j][iter];
			}
		}
	}*/

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			result[i][j] = 0;
			for (int k = 0; k < 4; ++k)
			{
				result[i][j] += l[i][k] * r[k][j];
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

float3 createColor(const unsigned int c)
{
	return float3{ 
		(float)((c >> 16) % 256) / 256.f, 
		(float)((c >> 8) % 256) / 256.f,
		(float)(c % 256) / 256.f
	};
}

std::vector<std::string> divideLine(const std::string & str, const char divider)
{
	std::vector<std::string> result{};
	std::stringstream ss(str);
	std::string token;
	while (getline(ss, token, divider))
	{
		result.push_back(token);
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

float4x4 float4x4::inverse() const
{
	float4x4 m1 = { *this };
	float4x4 m2{ 
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}
	};
	
	for (int i = 0; i < 4; ++i)
	{
		/*if (m1[i][i] == 0)
		{
			throw std::exception("float4x4: DIVISION BY 0");
		}*/
		float div = 1.f / m1[i][i];

		for (int j = 0; j < 4; ++j)
		{
			m1[j][i] *= div;
			m2[j][i] *= div;
		}

		for (int j = 0; j < 4; ++j)
		{
			if (j != i)
			{
				float mul = m1[i][j];

				for (int k = 0; k < 4; ++k)
				{
					m1[k][j] -= mul * m1[k][i];
					m2[k][j] -= mul * m2[k][i];
				}
			}
		}
	}

	return m2;
}

float4x4 float4x4::transpose() const
{
	return {
		{ (*this)[0][0], (*this)[1][0], (*this)[2][0],  (*this)[3][0] },
		{ (*this)[0][1], (*this)[1][1], (*this)[2][1],  (*this)[3][1] },
		{ (*this)[0][2], (*this)[1][2], (*this)[2][2],  (*this)[3][2] },
		{ (*this)[0][3], (*this)[1][3], (*this)[2][3],  (*this)[3][3] },
	
	};
}

float4x4 float4x4::identity()
{
	return float4x4(
		{1,0,0,0},
		{0,1,0,0},
		{0,0,1,0},
		{0,0,0,1}	
	);
}

int & int3::operator[](const int n)
{
	if (n > 3 || n < 0) { throw new std::exception{ "***int3: n wrong\n" }; }
	return *(&a + n);
}

const int & int3::operator[](const int n) const
{
	if (n > 3 || n < 0) { throw new std::exception{ "***int3: n wrong\n" }; }
	return *(&a + n);
}
