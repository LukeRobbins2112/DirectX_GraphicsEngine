#include "GraphicObject_Color.h"
#include "Model.h"
#include "ShaderColorLight.h"
#include <assert.h>
#include "d3dUtil.h"

GraphicObject_Color::GraphicObject_Color(ShaderColorLight * shader, Texture ** tx,  Model* mod)
{
	SetModel(mod );
	pShader = shader;

	World = Matrix(IDENTITY);

	int n = mod->GetMeshCount();
	myTextures = new Texture * [n];
	for (int i = 0; i < n; i++)
		myTextures[i] = tx[i];

	spotLightPos = Vect(0, 0, -4);

	pShader->SetDirectionalLightParameters(Vect(-1, -1, 1).getNorm(), .7 * Vect(1, 1, 1), .5 * Vect(1, 1, 1), Vect(1, 1, 1));

	pShader->SetPointLightParameters(Vect(0, 10, 0), 100, .3 * Vect(0, 1, 0), .1 * Vect(1, 1, 1), 2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));

	mTimer.Reset();
	
}

GraphicObject_Color::~GraphicObject_Color()
{
	delete[] myTextures;
}

void GraphicObject_Color::SetTexture(Texture * tex)
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
		myTextures[i] = tex;
}

void GraphicObject_Color::SetTexture(Texture * tex, int meshnum)
{
	assert(pModel->ValidMeshNum(meshnum));
	myTextures[meshnum] = tex;
}

void GraphicObject_Color::SetWorld(const Matrix& m) 
{ 
	World = m;
}

void GraphicObject_Color::SetSpotlightPos(const Vect & pos) {
	spotLightPos = pos;
}

void GraphicObject_Color::ShaderSendLightParameters(const Vect & eyepos) {
	this->pShader->SendLightParameters(eyepos);
}

void GraphicObject_Color::ShaderSendCamMatrices(const Matrix& view, const Matrix& proj) {
	this->pShader->SendCamMatrices(view, proj);
}

void GraphicObject_Color::SetShaderToContext(ID3D11DeviceContext* devcon) {
	this->pShader->SetToContext(devcon);
}

void GraphicObject_Color::Render()
{
	mTimer.Tick();

	pShader->SetSpotLightParameters(spotLightPos, 4000, .5 * Vect(1, 0, 0),
		-spotLightPos.getNorm(), 50,
		.6 * Vect(1, 1, 1), 3 * Vect(1, 1, 1), 1 * Vect(1, 1, 1, 150));


	pModel->BindVertexIndexBuffers(pShader->GetContext());

	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SetTextureResourceAndSampler(myTextures[i]);
		pShader->SendWorldAndMaterial(World*Matrix(TRANS, 0, cosf(mTimer.TotalTime()), 0), Colors::White, Colors::White, Vect(1, 1, 1, 100));
		pModel->RenderMesh(pShader->GetContext(), i);
	}
}