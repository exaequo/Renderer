#include "stdafx.h"
#include "Rasterizer.h"
#include <algorithm>

Rasterizer::~Rasterizer()
{
}

/** Draws a triangle with vertices of the specified colors*/
void Rasterizer::Triangle(const float3 & p1, const float3 & p2, const float3 & p3, const float3 & c1, const float3 & c2, const float3 & c3)
{

	//std::cout << " *DRAWING TRIANGLE*\n";
	//std::cout << "P1: " << p1 << "\n";
	//std::cout << "P2: " << p2 << "\n";
	//std::cout << "P3: " << p3 << "\n";
	//screen point positions
	int x1 = (p1.x + 1) * buffer.width *.5f,
		x2 = (p2.x + 1) * buffer.width *.5f,
		x3 = (p3.x + 1) * buffer.width *.5f;
	int y1 = (p1.y + 1) * buffer.height *.5f,
		y2 = (p2.y + 1) * buffer.height *.5f,
		y3 = (p3.y + 1) * buffer.height *.5f;
	
	//rectangle of the triangle calculations
	int minx = std::max(Min(x1, x2, x3), 0),
		maxx = std::min(Max(x1, x2, x3), buffer.width - 1),
		miny = std::max(Min(y1, y2, y3), 0),
		maxy = std::min(Max(y1, y2, y3), buffer.height - 1);
	//constants
	int 
		dx12 = x1 - x2,
		dx23 = x2 - x3,
		dx31 = x3 - x1,
		dy12 = y1 - y2,
		dy23 = y2 - y3,
		dy31 = y3 - y1;
	float db1 = 1.f / (-dy23 * dx31 + dx23 * dy31);
	float db2 = 1.f / (dy31 * dx23 - dx31 * dy23);
	
	//topleft calculations
	bool tl1 = false, tl2 = false, tl3 = false;

	if (dy12 < 0 || (dy12 == 0 && dx12 > 0)) { tl1 = true; }
	if (dy23 < 0 || (dy23 == 0 && dx23 > 0)) { tl2 = true; }
	if (dy31 < 0 || (dy31 == 0 && dx31 > 0)) { tl3 = true; }

	for (int y = miny; y < maxy; ++y)
	{
		for (int x = minx; x < maxx; ++x)
		{
			if (((tl1 && dx12*(y - y1) - dy12*(x - x1) >= 0) || (!tl1 && dx12*(y - y1) - dy12*(x - x1) > 0)) &&
				((tl2 && dx23*(y - y2) - dy23*(x - x2) >= 0) || (!tl2 && dx23*(y - y2) - dy23*(x - x2) > 0)) &&
				((tl3 && dx31*(y - y3) - dy31*(x - x3) >= 0) || (!tl3 && dx31*(y - y3) - dy31*(x - x3) > 0)))
			{
				//which position on buffer
				int n = y*buffer.width + x;
				//baricentric
				float
					d1 = (dy23 * (x - x3) - dx23 * (y - y3)) * db1,
					d2 = (dy31 * (x - x3) - dx31 * (y - y3)) * db2,
					d3 = 1 - d1 - d2;
				//checking depth
				float depth = (d1 * p1.z + d2 * p2.z + d3 * p3.z);

				if (depth >= 0 && depth < buffer.GetDepth(n))
				{
					//color calculations
					float3 color = c1 * d1 + c2 * d2 + c3 * d3;
					buffer.SetColor(n, color.ColorRGB());
					buffer.SetDepth(n, depth);
				}
			}
		}
	}
}

void Rasterizer::Triangle(const Vertex & v1, const Vertex & v2, const Vertex & v3, const Material & mat)
{
	Triangle(v1.getPosition(), v2.getPosition(), v3.getPosition(),
		mat.getColorDiffuse(), mat.getColorDiffuse(), mat.getColorDiffuse());
}

