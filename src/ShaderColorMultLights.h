// ShaderColorMultLights
#ifndef _ShaderColorMultLights
#define _ShaderColorMultLights

#include "ShaderBase.h"
#include "Matrix.h"
#include "Texture.h"

struct ID3D11Buffer;
struct ID3D11Device;

class ShaderColorMultLights : public ShaderBase
{

public:
	ShaderColorMultLights(const ShaderColorMultLights&) = delete;				 // Copy constructor
	ShaderColorMultLights(ShaderColorMultLights&&) = default;                    // Move constructor
	ShaderColorMultLights& operator=(const ShaderColorMultLights&) & = default;  // Copy assignment operator
	ShaderColorMultLights& operator=(ShaderColorMultLights&&) & = default;       // Move assignment operator
	~ShaderColorMultLights();		  							         // Destructor

	ShaderColorMultLights(ID3D11Device* device);

	virtual void SetToContext(ID3D11DeviceContext* devcon) override;

	void SetDirectionalLightParameters(const Vect& dir, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetSpotLightParameters(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));

	//multiple lights version, with array index
	void SetSpotLightParameters(int index, const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));	//multiple light version

	void SetFogParams(float fogStart, float fogRange, Vect fogColor); //Add params);

	//Texture
	void SetTextureResourceAndSampler(Texture * tex);

	void SendCamMatrices(const Matrix& view, const Matrix& proj);
	void SendLightParameters(const Vect& eyepos);
	void SendFogParameters();
	void SendWorldAndMaterial(const Matrix& world, const Vect& amb = Vect(.5f, .5f, .5f), const Vect& dif = Vect(.5f, .5f, .5f), const Vect& sp = Vect(.5f, .5f, .5f));

private:
	struct Material
	{
		Vect Ambient;
		Vect Diffuse;
		Vect Specular;
	};

	struct PhongADS
	{
		Vect Ambient;
		Vect Diffuse;
		Vect Specular;
	};



	const int NUM_LIGHTS = 3;

	struct DirectionalLight
	{
		PhongADS Light;
		Vect Direction;
	};

	DirectionalLight DirLightData;

	struct PointLight
	{
		PhongADS Light;
		Vect Position;
		Vect Attenuation;
		float Range;
	};

	PointLight PointLightData;

	struct SpotLight
	{
		PhongADS Light;
		Vect Position;
		Vect Attenuation;
		Vect Direction;
		float SpotExp;
		float Range;
	};

	SpotLight SpotLightData[3];





	struct CamMatrices
	{
		Matrix View;
		Matrix Projection;
	};

	ID3D11Buffer*  mpBufferCamMatrices;

	struct Data_WorldAndMaterial
	{
		Matrix World;
		Matrix WorlInv;
		Material Mat;
	};

	ID3D11Buffer*	mpBuffWordAndMaterial;

	struct Data_LightParams
	{
		DirectionalLight DirLight;
		PointLight PntLight;
		SpotLight SptLight[3];
		Vect EyePosWorld;
	};

	ID3D11Buffer*  mpBufferLightParams;

	struct FogData {
		float FogStart;
		float FogRange;
		Vect FogColor;
	};

	FogData FData;

	ID3D11Buffer*  mpBufferFogParams;
};

#endif _ShaderColorMultLights

