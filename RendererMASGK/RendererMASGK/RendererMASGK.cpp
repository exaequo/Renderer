// RendererMASGK.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <chrono>
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
	
	Data::Instance().AmbientLight() = { 0.25f, 0.25f, 0.25f };

	DirectionalLight light{  DirectionalLight(&vp,{ 0.2f, -1, -0.2f },{ 1, 1.f, 1 },{ .1f, .1f, .1f }) };
	light.Specular() = { 1, 1.f, 0.f };
	DirectionalLight light2{  DirectionalLight(&vp,{ -0.2f, 1, -0.05f },{ .5f, .75f, .5f },{ .1f, .1f, .1f }) };

	
	//light2->Specular() = { 0.2f, 1, .5f };
	//DirectionalLight *light{ new DirectionalLight(&vp,{ 0, 0, -1.f },{ 1, 1, 1 },{ .1f, .1f, .1f }) };

	//vp.multByTranslation({ -5,0, -10.f });
	//vp.multByRotation(90.f, { 0,1,0 });
	ToonShader shader{};

	OBJMesh torus{ "torus" };
	OBJMesh sphereT{ "sphereTEX" };
	OBJMesh wall{ "brickWall" };
	OBJMesh text{ "text" };
	OBJMesh rope{ "rope" };
	OBJMesh cube{ "cube" };
	cube.setMaterial(wall.getMaterial());
	
	auto startClock = std::chrono::steady_clock::now();
	vp.multByTranslation({ -5.5f,-10,-5 });
	PointLight light3{ PointLight{ &vp,{ 0,0,0 },{ 0.2f, 0.2f, 1 },{ .1f, .1f, .1f } } };
	vp.clearTransformations();


	vp.multByTranslation({ -7.5f,0,-7.5f });
	sphereT.draw(rasterizer, vp);
	
	vp.multByTranslation({ 10.5f,2,2.5f });
	vp.multByRotation(-45, { 0,1,0 });
	vp.multByRotation(-5, { 1,0,0 });
	vp.multByScale({ 0.5f, 0.5f, 0.5f });
	//text.getMaterial()->setShader(&shader);
	text.draw(rasterizer, vp);
	//vp.multByRotation(-90, { 0,1,0 });
	
	vp.clearTransformations();
	vp.multByRotation(15, { 1,0,0 });
	vp.multByTranslation({ 0.f,-3,-5 });
	vp.multByScale({ 0.5f, 0.5f, 0.5f });
	
	
	torus.draw(rasterizer, vp);
	vp.multByTranslation({12.f,0,0 });
	torus.getMaterial()->setShader(&shader);
	torus.draw(rasterizer, vp);

	vp.clearTransformations();
	//vp.multByScale({2, 2, 2 });
	//vp.multByRotation(45.f, { 0,1,0 });
	vp.multByTranslation({ 0,-10,-20 });
	wall.draw(rasterizer, vp);

	/*vp.multByTranslation({ 5.f,-5,-5 });
	vp.multByRotation(20.f, { 1,0,0 });
	
	vp.multByTranslation({ -5.f,-5, 0});
	vp.multByScale({ 4,4,4 });
	*/
	
	vp.clearTransformations();
	vp.multByTranslation({ 8.f,-6,-10 });
	vp.multByScale({ 0.5f, 0.5f, 0.5f });
	vp.multByRotation(-45.f, { 1,1,1 });
	
	rope.draw(rasterizer, vp);

	vp.clearTransformations();
	vp.multByTranslation({ -2.f,-7,-10 });
	vp.multByRotation(-45.f, { 1,1,1 });
//	vp.multByScale({ 0.5f, 0.5f, 0.5f });

	cube.draw(rasterizer, vp);

	buffer.save("test.tga");

	std::cout << "Time: " << std::chrono::duration <double>(std::chrono::steady_clock::now() - startClock).count() << "s\n";
	std::cin.get();
    return 0;
}

