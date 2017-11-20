// RendererMASGK.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

int main()
{
	//VertexProcesor vp{ 120, 1.f, 0.f, 10.f,
	//	{0,0,10}, {0,0,-1}, {0,1,0} };
	//TgaBuffer buff{ 512, 512 , 10000.f };
	//buff.ClearColor(0x00f0f0f0); //argb
	//buff.ClearDepth();

	//Rasterizer rast{ buff };

	//

	//rast.Triangle(vp.tr({ -1.f, 0.f, -1.f }), vp.tr({ 0.f, 0.75f, -1.f }), vp.tr({ 0.75f, -1.f, -1.f }),
	//{ 1, 0, 0 }, { 1, 0, 0 }, { 1, 0, 0 });
	//
	//vp.multByTranslation({ 0.5f,0.5f,0.f });
	//std::cout << "o2w Tr.\n" << vp.obj2world << "\n";

	//vp.multByScale({ 1.1f, 1.1f, 1.f });
	//rast.Triangle(vp.tr({ -1.f, 0.f, -50.f }), vp.tr({ 0.f, 0.75f, -50.f }), vp.tr({ 0.75f, -1.f, -50.f }),
	//{ 0, 1, 0 }, { 0, 1, 0 }, { 0, 1, 0 });

	//buff.save("test.tga");
	int width = 1280;
	int height = 720;

	TgaBuffer buffer{ width, height, 10000.f };
	buffer.ClearColor(0x00FFFFFF);
	buffer.ClearDepth();

	Rasterizer rasterizer(buffer);

	VertexProcesor vp{ 60, static_cast<float>(width) / height, 0.3f, 100.f,
			{0,0,4}, {0,0,0}, {0,1,0} };

	vp.multByScale({ 2.f, 2.f, 1.f });
	vp.multByRotation(15.f, { 0,0,1 });
	vp.multByTranslation({ 0.f, -0.5f, 0.f });


	rasterizer.Triangle(vp.tr({ -0.5f, -0.5f, 0.f }), vp.tr({ 0.f, 0.5f, 0.f }), vp.tr({ 0.5f, -0.5f, 0.f }),
		{ 1,0,0 }, { 0,1,0 }, { 0,0,1 });

	vp.multByTranslation({ -1.f, 0.75f, -2.f });
	vp.multByRotation(30.f, { 0,0,1 });
	rasterizer.Triangle(vp.tr({ -0.5f, -0.5f, 0.f }), vp.tr({ 0.f, 0.5f, 0.f }), vp.tr({ 0.5f, -0.5f, 0.f }),
	{ 1,0,0 }, { 1,0,0 }, { 1,0,0 });

	buffer.save("tst1.tga");

	std::cin.get();
    return 0;
}

