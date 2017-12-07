#pragma once

class Material
{
public:
	Material();
	Material(const float3& color);	

	const float3& getColorAmbient() const { return colorAmbient; }
	float3& ColorAmbient() { return colorAmbient; }
	
	const float3& getColorDiffuse() const { return colorDiffuse; }
	float3& ColorDiffuse() { return colorDiffuse; }
	
	const float3& getColorSpecular() const { return colorSpecular; }
	float3& ColorSpecular() { return colorSpecular; }
	
	const float3& getColorEmissive() const { return colorEmissive; }
	float3& ColorEmissive() { return colorEmissive; }
	
	std::string& Name() { return name; }

	float& Ns() { return m_Ns; }
	const float& getNs() const { return m_Ns; }

	float& Ni() { return m_Ni; }
	float& D() { return m_d; }
	float& Tr() { return m_Tr; }
	float& Illum() { return illum; }
	float3& Tf() { return m_Tf; }
	float& N() { return m_n; }

	int ID() { return materialID; }
	class Texture* getTexture() { return tex; }
	const class Texture* getTexture() const { return tex; }
	void setTexture(Texture * t) { tex = t; }
	class Texture* getNormal() { return normal; }
	const class Texture* getNormal() const { return normal; }
	void setNormal(Texture * t) { normal = t; }

private:
	std::string name;
	float3 colorAmbient;
	float3 colorDiffuse;
	float3 colorSpecular;
	float3 colorEmissive;
	float m_Ns;					
	float m_Ni;
	float m_d;
	float m_Tr;
	float3 m_Tf;
	float illum;
	
	float m_n;

	//std::string textureID;
	Texture* tex;
	Texture* normal;

	int materialID;
	static int currentMaterialID;
};

