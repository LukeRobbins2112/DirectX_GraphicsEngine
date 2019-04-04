#include "GraphicObject_Sky.h"
#include "Model.h"
#include "ShaderColor.h"
#include <assert.h>

GraphicObject_Sky::GraphicObject_Sky(ShaderTexture * shader, Texture * tex, SkyBox * box)
{
	SetSkybox(box);
	pShaderTex = shader;

	myTex = tex;

	World = box->GetWorldMat();
	
}

GraphicObject_Sky::~GraphicObject_Sky()
{

}

void GraphicObject_Sky::SetSkybox(SkyBox * box) {
	this->skyBox = box;
}

void GraphicObject_Sky::SetTexture(Texture * tex)
{
	this->myTex = tex;
}

void GraphicObject_Sky::SetWorld(const Matrix& m)
{
	World = m;
}

void GraphicObject_Sky::ShaderSendCamMatrices(const Matrix& view, const Matrix& proj) {
	this->pShaderTex->SendCamMatrices(view, proj);
}

void GraphicObject_Sky::SetShaderToContext(ID3D11DeviceContext* devcon) {
	this->pShaderTex->SetToContext(devcon);
}

void GraphicObject_Sky::Render()
{
	pShaderTex->SendWorld(World);
	pShaderTex->SetTextureResourceAndSampler(this->myTex);
	skyBox->Render(pShaderTex->GetContext());
}