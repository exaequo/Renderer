#pragma once
#include <iostream>

#ifndef PI
#define PI (3.14159265358979323846)
#endif

struct float3 {
	union {
		struct { float r, g, b; };
		struct { float x, y, z; };
	};
	unsigned int ColorRGB() const;

	float Dot(const float3& other);
	float3 Cross(const float3& other);
	float magnitude() const;
	float3& normalize();
	float3 getNormalized() const;

	float3& operator+(const float3&);
	float3& operator-(const float3&);
	float3& operator*(const float);
	float3& operator*(const float3&);
	float& operator[](const int n);
	const float& operator[](const int n) const;
	
	friend float3 operator-(const float3& lhs, const float3 & rhs);
	friend float3 operator*(const float3& lhs, const float rhs);
	friend std::ostream& operator<< (std::ostream& stream, const float3&);
};
struct float4 {
	union {
		struct { float r, g, b, a; };
		struct { float x, y, z, w; };
	};
	float4() {};
	float4(float x, float y, float z, float w) : x{ x }, y{ y }, z{ z }, w{ w } {};
	float4(const float3& v, float w) : x{ v.x }, y{ v.y }, z{ v.z }, w{ w } {};
	unsigned int ColorARGB() const;

	float4& operator+(const float4&);
	float4& operator*(const float);
	float4& operator*(const float4&);
	float& operator[](const int n);
	const float& operator[](const int n) const;

	explicit operator float3() const { return float3{ x,y,z }; }

	friend float4 operator*(const float4& lhs, const float rhs);
	friend std::ostream& operator<< (std::ostream& stream, const float4&);
};

struct float4x4 {
	float4 arr[4];
	float4& operator[](const int n);
	const float4& operator[](const int n) const;

	friend std::ostream& operator<< (std::ostream& stream, const float4x4&);
};

int Min(int v1, int v2, int v3);
int Max(int v1, int v2, int v3);

float3 crossProduct(const float3& lhs, const float3& rhs);
float dotProduct(const float3& lhs, const float3& rhs);

float3 operator*(const float3& lhs, const float rhs);
float4 operator*(const float4& lhs, const float rhs);

float4x4 mul(const float4x4& l, const float4x4& r);
float4 mul(const float4x4& l, const float4& r);