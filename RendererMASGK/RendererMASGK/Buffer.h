#pragma once
class Buffer
{
public:
	Buffer();
	~Buffer();
	unsigned int color;
	float depth;
	float w, h, minx, maxx, miny, maxy, len;

	void SetSize();
	void ClearColor();
	void ClearDepth();
};


