#pragma once
#include <iostream>
struct float3 {
	union {
		struct { float r, g, b; };
		struct { float x, y, z; };
	};
	unsigned int ColorRGB() const;

	float Dot(const float3& other);
	float3 Cross(const float3& other);

	float3& operator+(const float3&);
	float3& operator*(const float);
	float3& operator*(const float3&);
	float& operator[](const int n);
	
	friend float3 operator*(const float3& lhs, const float rhs);
	friend std::ostream& operator<< (std::ostream& stream, const float3&);
};
struct float4 {
	union {
		struct { float r, g, b, a; };
		struct { float x, y, z, w; };
	};
	unsigned int ColorARGB() const;

	float4& operator+(const float4&);
	float4& operator*(const float);
	float4& operator*(const float4&);
	float& operator[](const int n);

	friend float4 operator*(const float4& lhs, const float rhs);
};

struct float4x4 {
	float4 arr[4];

//TODO implement rest
};

int Min(int v1, int v2, int v3);
int Max(int v1, int v2, int v3);

float3 crossProduct(const float3& lhs, const float3& rhs);
float dotProduct(const float3& lhs, const float3& rhs);

float3 operator*(const float3& lhs, const float rhs);
float4 operator*(const float4& lhs, const float rhs);