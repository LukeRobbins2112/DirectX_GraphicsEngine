#include "ShaderColorMultLights.h"
#include "d3dUtil.h"
#include <d3d11.h>
#include <assert.h>

ShaderColorMultLights::ShaderColorMultLights(ID3D11Device* dev)
	: ShaderBase(dev, L"../Assets/Shaders/MultipleLights.hlsl")
{
	// Define the input layout
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT numElements = ARRAYSIZE(layout);
	this->CreateInputLayout(layout, numElements);

	//Fog Defaults to zero
	this->FData.FogColor = Vect(1, 1, 1, 1.000000000f);
	this->FData.FogRange = 0.0f;
	this->FData.FogStart = 999999999999.0f;

	HRESULT hr = S_OK;

	// View Projection buffer
	D3D11_BUFFER_DESC bd;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(CamMatrices);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBufferCamMatrices);
	assert(SUCCEEDED(hr));

	// light param
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Data_LightParams);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBufferLightParams);
	assert(SUCCEEDED(hr));

	// Color buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Data_WorldAndMaterial);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBuffWordAndMaterial);
	assert(SUCCEEDED(hr));

	// Fog buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(FogData);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBufferFogParams);
	assert(SUCCEEDED(hr));

	// Zeroing the light data
	ZeroMemory(&DirLightData, sizeof(DirLightData));
	ZeroMemory(&PointLightData, sizeof(PointLightData));
	ZeroMemory(&SpotLightData, sizeof(SpotLightData));
}

ShaderColorMultLights::~ShaderColorMultLights()
{
	ReleaseAndDeleteCOMobject(mpBuffWordAndMaterial);
	ReleaseAndDeleteCOMobject(mpBufferLightParams);
	ReleaseAndDeleteCOMobject(mpBufferCamMatrices);
	ReleaseAndDeleteCOMobject(mpBufferFogParams);
}

void ShaderColorMultLights::SendCamMatrices(const Matrix& view, const Matrix& proj)
{
	CamMatrices	mCamMatrices;
	mCamMatrices.View = view;
	mCamMatrices.Projection = proj;

	this->GetContext()->UpdateSubresource(mpBufferCamMatrices, 0, nullptr, &mCamMatrices, 0, 0);
}

void ShaderColorMultLights::SetDirectionalLightParameters(const Vect& dir, const Vect& amb, const Vect& dif, const Vect& sp)
{
	DirLightData.Light.Ambient = amb;
	DirLightData.Light.Diffuse = dif;
	DirLightData.Light.Specular = sp;
	DirLightData.Direction = dir;
}

void ShaderColorMultLights::SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb, const Vect& dif, const Vect& sp)
{
	PointLightData.Light.Ambient = amb;
	PointLightData.Light.Diffuse = dif;
	PointLightData.Light.Specular = sp;
	PointLightData.Position = pos;
	PointLightData.Attenuation = att;
	PointLightData.Range = r;
}

void ShaderColorMultLights::SetSpotLightParameters(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp)
{
	for (int i = 0; i < NUM_LIGHTS; i++) {
		SpotLightData[i].Light.Ambient = amb;
		SpotLightData[i].Light.Diffuse = dif;
		SpotLightData[i].Light.Specular = sp;
		SpotLightData[i].Position = pos;
		SpotLightData[i].Direction = dir;
		SpotLightData[i].Attenuation = att;
		SpotLightData[i].Range = r;
		SpotLightData[i].SpotExp = spotExp;
	}
}

void ShaderColorMultLights::SetSpotLightParameters(int index, const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp)
{
	SpotLightData[index].Light.Ambient = amb;
	SpotLightData[index].Light.Diffuse = dif;
	SpotLightData[index].Light.Specular = sp;
	SpotLightData[index].Position = pos;
	SpotLightData[index].Direction = dir;
	SpotLightData[index].Attenuation = att;
	SpotLightData[index].Range = r;
	SpotLightData[index].SpotExp = spotExp;
}

void ShaderColorMultLights::SetFogParams(float fogStart, float fogRange, Vect fogColor) {
	FData.FogStart = fogStart;
	FData.FogRange = fogRange;
	FData.FogColor = fogColor;
}

void ShaderColorMultLights::SendFogParameters() {

	FogData fd;
	fd.FogColor = FData.FogColor;
	fd.FogRange = FData.FogRange;
	fd.FogStart = FData.FogStart;

	this->GetContext()->UpdateSubresource(mpBufferFogParams, 0, nullptr, &fd, 0, 0);
}

void ShaderColorMultLights::SetTextureResourceAndSampler(Texture * tex) {
	tex->SetToContext(this->GetContext(), 0, 0);
}

void ShaderColorMultLights::SendLightParameters(const Vect& eyepos)
{
	Data_LightParams dl;
	dl.DirLight = DirLightData;
	dl.PntLight = PointLightData;

	for (int i = 0; i < NUM_LIGHTS; i++) {
		dl.SptLight[i] = SpotLightData[i];
	}

	dl.EyePosWorld = eyepos;

	this->GetContext()->UpdateSubresource(mpBufferLightParams, 0, nullptr, &dl, 0, 0);
}

void ShaderColorMultLights::SendWorldAndMaterial(const Matrix& world, const Vect& amb, const Vect& dif, const Vect& sp)
{
	Data_WorldAndMaterial wm;
	wm.World = world;
	wm.WorlInv = world.getInv();
	wm.Mat.Ambient = amb;
	wm.Mat.Diffuse = dif;
	wm.Mat.Specular = sp;

	this->GetContext()->UpdateSubresource(mpBuffWordAndMaterial, 0, nullptr, &wm, 0, 0);
}

void ShaderColorMultLights::SetToContext(ID3D11DeviceContext* devcon)
{
	ShaderBase::SetContext(devcon);
	ShaderBase::SetToContext_VS_PS_InputLayout();

	this->GetContext()->UpdateSubresource(mpBufferFogParams, 0, nullptr, &this->FData, 0, 0);


	devcon->VSSetConstantBuffers(0, 1, &mpBufferCamMatrices);
	devcon->VSSetConstantBuffers(1, 1, &mpBufferLightParams);
	devcon->VSSetConstantBuffers(2, 1, &mpBuffWordAndMaterial);
	devcon->VSSetConstantBuffers(3, 1, &mpBufferFogParams);

	devcon->PSSetConstantBuffers(0, 1, &mpBufferCamMatrices);
	devcon->PSSetConstantBuffers(1, 1, &mpBufferLightParams);
	devcon->PSSetConstantBuffers(2, 1, &mpBuffWordAndMaterial);
	devcon->PSSetConstantBuffers(3, 1, &mpBufferFogParams);
}