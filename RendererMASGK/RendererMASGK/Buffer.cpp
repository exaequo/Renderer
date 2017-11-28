#include "stdafx.h"
#include "Buffer.h"
#include <exception>

Buffer::Buffer(int bufferWidth, int bufferHeight, float bufferDepth) : width{ bufferWidth }, height{ bufferHeight }, len{width * height}, depth{bufferDepth}
{
	colorBuffer = new unsigned int[len];
	depthBuffer = new float[len];
}

Buffer::~Buffer()
{
	delete[] colorBuffer;
	delete[] depthBuffer;
}

void Buffer::ClearColor(unsigned int color)
{
	clearColor = color;
	for (unsigned int i = 0; i < len; ++i)
	{
		colorBuffer[i] = color;
	}
}

void Buffer::ClearDepth()
{
	for (unsigned int i = 0; i < len; ++i)
	{
		depthBuffer[i] = depth;
	}
}

void Buffer::SetColor(unsigned int pos, unsigned int color)
{
	if (pos >= len)throw std::exception{"out of buffer length"};
	
	colorBuffer[pos] = color;
}

void Buffer::SetDepth(unsigned int pos, float newDepth)
{
	if (pos >= len)throw std::exception{ "out of buffer length" };

	depthBuffer[pos] = newDepth;
}

float Buffer::GetDepth(unsigned int pos)
{
	if (pos >= len)throw std::exception{ "out of buffer length" };

	return depthBuffer[pos];
}
