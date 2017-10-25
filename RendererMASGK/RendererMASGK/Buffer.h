#pragma once
class Buffer
{
public:
	Buffer(int width, int height, float depth);
	~Buffer();
	Buffer(Buffer&) = delete;
	unsigned int clearColor;
	float depth;
	int width, height, minx, maxx, miny, maxy, len;


	void SetSize(int width, int length);
	void ClearColor(unsigned int color);
	void ClearDepth();
	void SetColor(unsigned int pos, unsigned int color);
	void SetDepth(unsigned int pos, float depth);
	float GetDepth(unsigned int pos);

protected:
	unsigned int* colorBuffer;
	float* depthBuffer;
};


