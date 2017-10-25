#pragma once

struct float3 {
	union {
		struct { float r, g, b; };
		struct { float x, y, z; };
	};

	float3& operator+(const float3&);
	float3& operator*(float);
	float3& operator*(const float3&);
};