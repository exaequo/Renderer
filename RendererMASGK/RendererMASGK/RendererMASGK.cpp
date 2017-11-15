// RendererMASGK.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

int main()
{
	VertexProcesor vp{ 45.f, 2.f, 0.f, 10000.f,
		{0,0,0}, {0,0,1}, {0,1,0} };
	TgaBuffer buff{ 512, 512 , 1000.f };
	buff.ClearColor(0x00f0f0f0); //argb
	buff.ClearDepth();

	Rasterizer rast{ buff };
	/*rast.Triangle({ -1.f, 0.f, 0.f }, { 0.f, .75f, 0.f }, { .75f, -1.f, 0.f },
					{ 1, 1, 0 }, { 0, 1, 1 }, { 0, 0, 1 });

	rast.Triangle({ .75f, -1.f, 1.f }, { -1.f, .75f, -1.f }, {1.f, 1.f, 1.f},
					{ 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 });
	rast.Triangle({ -1.f, 0.f, 0.f }, { .75f, -1.f, 0.f }, { -1.f, -1.f, 0.f },
					{ .2f, 0, 0 }, { 0, .1f, 0 }, { 0, 0, .1f });*/
	/*rast.Triangle({ -0.9f, -2.41f, 3.f }, { 0.f, 1.81f, 3.f }, { 1.20f, 0.f, 3.f },
	{ 1, 1, 0 }, { 0, 1, 1 }, { 0, 0, 1 });*/

	float3 f3 = { -1.f, 0.f, 4.f };

	rast.Triangle(vp.tr({ 0.75f, -1.f, 4.f }), vp.tr({ 0.f, 0.75f, 4.f }), vp.tr({ -1.f, 0.f, 4.f }),
	{ 1, 1, 0 }, { 0, 1, 1 }, { 0, 0, 1 });
	
	buff.save("test.tga");

	std::cout << vp.obj2world <<"\n";
	std::cout << vp.world2view << "\n";
	std::cout << vp.view2proj << "\n";

	std::cout << mul(vp.view2proj, vp.world2view) << "\n";
	//float4x4 m{
	//	float4{ 1, 0, 0, 1.5f },
	//	float4{ 0, 1, 0, 1 },
	//	float4{ 0, 0, 1, 1.5f },
	//	float4{ 0, 0, 0, 1 }
	//};
	//float4x4 n{
	//	float4{ 1, 0, 0, 0 },
	//	float4{ 0, -1, 0, 0 },
	//	float4{ 0, 0, -1, 0 },
	//	float4{ 0, 0, 0, 1 }
	//};
	//float4x4 o{
	//	float4{ 0, 0, 1, 0 },
	//	float4{ 0, 1, 0, 0 },
	//	float4{ -1, 0, 0, 0 },
	//	float4{ 0, 0, 0, 1 }
	//};
	//
	//auto mult = mul(mul(m, n), o);
	//float4 v{ 0,1,0,1 };
	//std::cout << mult <<"\n\n";

	//std::cout << mul(mult, v);

	std::cin.get();
    return 0;
}

