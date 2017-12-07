// RendererMASGK.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

int main()
{
	int width = 1280;
	int height = 720;

	TgaBuffer buffer{ width, height, 10000.f };
	buffer.ClearColor(0x00efefef);
	buffer.ClearDepth();

	Rasterizer rasterizer(buffer);
	VertexProcesor vp{ 30, static_cast<float>(width) / height, 0.3f, 10000.f,
			{0,0,20}, {0,0,0}, {0,1,0} };
	
	Data::Instance().AmbientLight() = { 0.15f, 0.15f, 0.15f };

	DirectionalLight *light{ new DirectionalLight(&vp,{ 0.1f, -1, -0.1f },{ 1, 1, 1 },{ .1f, .1f, .1f }) };
	//light->Specular() = { 1, .5f, .5f };
	/*DirectionalLight *light2{ new DirectionalLight(&vp,{ -0.2f, 1, -0.05f },{ .5f, .5f, .5f },{ .1f, .1f, .1f }) };
	light2->Specular() = { 0.2f, 1, .5f };*/
	//DirectionalLight *light{ new DirectionalLight(&vp,{ 0, 0, -1.f },{ 1, 1, 1 },{ .1f, .1f, .1f }) };

	//vp.multByTranslation({ -5,0, -10.f });
	//vp.multByRotation(90.f, { 0,1,0 });
	
	OBJMesh objM{ "torus" };
	OBJMesh objM2{ "sphereTEX" };

	
	objM2.draw(rasterizer, vp);
		
	vp.multByTranslation({ 5.f,-5,-5 });
	vp.multByRotation(20.f, { 1,0,0 });
	
	vp.multByTranslation({ -5.f,-5, 0});
	vp.multByScale({ 4,4,4 });

	objM.draw(rasterizer, vp);
	buffer.save("test.tga");

	std::cin.get();
    return 0;
}

