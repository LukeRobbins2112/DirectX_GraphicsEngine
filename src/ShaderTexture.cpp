#include "ShaderTexture.h"
#include "d3dUtil.h"
#include <d3d11.h>
#include <assert.h>

ShaderTexture::ShaderTexture(ID3D11Device* device) : ShaderBase(device, L"../Assets/Shaders/Texture.hlsl")
{
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT , D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	UINT numElements = ARRAYSIZE(layout);
	this->CreateInputLayout(layout, numElements);

	HRESULT hr;

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

	// World buffer
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Data_World);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
	bd.MiscFlags = 0;
	bd.StructureByteStride = 0;
	hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBuffWorld);
	assert(SUCCEEDED(hr));

	//// Texture buffer
	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = sizeof(Data_Texture);
	//bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	//bd.CPUAccessFlags = 0;
	//bd.MiscFlags = 0;
	//bd.StructureByteStride = 0;
	//hr = this->GetDevice()->CreateBuffer(&bd, nullptr, &mpBuffTexture);
	//assert(SUCCEEDED(hr));
}

ShaderTexture::~ShaderTexture() {
	ReleaseAndDeleteCOMobject(mpBufferCamMatrices);
	ReleaseAndDeleteCOMobject(mpBuffWorld);
	//ReleaseAndDeleteCOMobject(mpBuffTexture);
}

void ShaderTexture::SetToContext(ID3D11DeviceContext* devcon) {

	ShaderBase::SetContext(devcon);
	ShaderBase::SetToContext_VS_PS_InputLayout();

	devcon->VSSetConstantBuffers(0, 1, &mpBufferCamMatrices);
	devcon->VSSetConstantBuffers(1, 1, &mpBuffWorld);
	//devcon->VSSetConstantBuffers(0, 1, &mpBuffTexture);
}



void ShaderTexture::SendCamMatrices(const Matrix& view, const Matrix& proj) {
	CamMatrices	mCamMatrices;
	mCamMatrices.View = view;
	mCamMatrices.Projection = proj;

	this->GetContext()->UpdateSubresource(mpBufferCamMatrices, 0, nullptr, &mCamMatrices, 0, 0);
}

void ShaderTexture::ShaderTexture::SendWorld(const Matrix& world) {

	Data_World wld;
	wld.World = world;

	this->GetContext()->UpdateSubresource(mpBuffWorld, 0, nullptr, &wld, 0, 0);
}

void ShaderTexture::SetTextureResourceAndSampler(Texture * tex) {
	tex->SetToContext(this->GetContext(), 0, 0);
}
