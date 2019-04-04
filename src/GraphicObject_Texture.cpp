#include "GraphicObject_Texture.h"
#include "Model.h"
#include "ShaderColor.h"
#include <assert.h>

GraphicObject_Texture::GraphicObject_Texture(ShaderTexture * shader, Texture * tex, Model* mod)
{
	SetModel(mod);
	pShaderTex = shader;

	myTex = tex;

	World = Matrix(IDENTITY);
}

GraphicObject_Texture::~GraphicObject_Texture()
{

}

void GraphicObject_Texture::SetTexture(Texture * tex)
{
	this->myTex = tex;
}

void GraphicObject_Texture::SetWorld(const Matrix& m)
{
	World = m;
}

void GraphicObject_Texture::Render()
{
	pShaderTex->SendWorld(World);
	pShaderTex->SetTextureResourceAndSampler(this->myTex);
	pModel->Render(pShaderTex->GetContext());
}