#pragma once

struct float3 {
	union {
		struct { float r, g, b; };
		struct { float x, y, z; };
	};
	unsigned int ColorARGB() const;

	float3& operator+(const float3&);
	float3& operator*(const float);
	float3& operator*(const float3&);
	float& operator[](int n);
	
	friend float3 operator*(const float3& lhs, const float rhs);
};

int Min(int v1, int v2, int v3);
int Max(int v1, int v2, int v3);

float3 operator*(const float3& lhs, const float rhs);