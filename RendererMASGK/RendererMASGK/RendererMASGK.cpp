// RendererMASGK.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

int main()
{
	int width = 1280;
	int height = 720;

	TgaBuffer buffer{ width, height, 10000.f };
	buffer.ClearColor(0x00ffffff);
	buffer.ClearDepth();

	Rasterizer rasterizer(buffer);

	VertexProcesor vp{ 60, static_cast<float>(width) / height, 0.3f, 1000.f,
			{0,0,10}, {0,0,0}, {0,1,0} };
	
	vp.multByTranslation({ -5,0,-10.f });
	//vp.multByScale({ .5f, .5f, .5f });
	//vp.multByRotation(45.f, { 1, 0, 0 });

	/*SimpleTriangle obj{ { -0.5f, -0.5f, 0.f },{ 0.f, 0.5f, 0.f },{ 0.5f, -0.5f, 0.f } };
	obj.getMaterial().ColorDiffuse() = float3{ 0,1,0 };
	obj.draw(rasterizer, vp);*/

	OBJMesh objM{ "sphere" };
	objM.draw(rasterizer, vp);

	//vp.multByRotation(-45.f, { 1, 0, 0 });
	

	buffer.loadTexture("test1.tga", "test");
	objM.getMaterial().MainTextureID() = "test";

	vp.multByTranslation({ 10,0,0 });
	objM.draw(rasterizer, vp);

	buffer.save("test.tga");

	//std::cin.get();
    return 0;
}

