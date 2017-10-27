// RendererMASGK.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

int main()
{
	
	TgaBuffer buff{ 512, 512 , 1.f};
	buff.ClearColor(0x00f0f0f0); //argb
	buff.ClearDepth();

	Rasterizer rast{ buff };
	rast.Triangle({ -1.f, 0.f, 0.f }, { 0.f, .75f, 0.f }, { .75f, -1.f, 0.f },
					{ 1, 1, 0 }, { 0, 1, 1 }, { 0, 0, 1 });

	rast.Triangle({ .75f, -1.f, 1.f }, { -1.f, .75f, -1.f }, {1.f, 1.f, 1.f},
					{ 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 });
	rast.Triangle({ -1.f, 0.f, 0.f }, { .75f, -1.f, 0.f }, { -1.f, -1.f, 0.f },
					{ .2f, 0, 0 }, { 0, .1f, 0 }, { 0, 0, .1f });
	buff.save("test.tga");


	//std::cin.get();
    return 0;
}

