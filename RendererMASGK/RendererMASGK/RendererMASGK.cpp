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

	VertexProcesor vp{ 60, static_cast<float>(width) / height, 0.3f, 1000.f,
			{0,0,10}, {0,0,0}, {0,1,0} };
	
	vp.multByTranslation({ -5,0,-10.f });
	//vp.multByScale({ .5f, .5f, .5f });
	//vp.multByRotation(45.f, { 1, 0, 0 });

	/*SimpleTriangle obj{ { -0.5f, -0.5f, 0.f },{ 0.f, 0.5f, 0.f },{ 0.5f, -0.5f, 0.f } };
	obj.getMaterial().ColorDiffuse() = float3{ 0,1,0 };
	obj.draw(rasterizer, vp);*/

	OBJMesh objM2{ "sphereTEX" };

	OBJMesh objM{ "sphere" };
	objM.draw(rasterizer, vp);

	//vp.multByRotation(-45.f, { 1, 0, 0 });
	
	std::string texName = "tst";
	if (!buffer.loadTexture("wall.tga", texName))
	{
		std::cout << "Couldn't load tex\n";
	}

	for (Material *mat : ObjectHolder::Instance().materials)
	{
		std::cout << "Mater: " << mat->ColorAmbient() << "\n";
	}
	ObjectHolder::Instance().materials[0]->setTexture(ObjectHolder::Instance().getTexture(texName));

	//auto *tex = TgaBuffer::getTexture(texName);
	
	vp.multByTranslation({ 10,0,0 });
	objM2.draw(rasterizer, vp);

	buffer.save("test.tga");

	std::cin.get();
    return 0;
}

