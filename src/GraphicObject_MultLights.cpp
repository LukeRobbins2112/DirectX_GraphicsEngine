#include "GraphicObject_MultLights.h"
#include "Model.h"
#include "ShaderColorMultLights.h"
#include <assert.h>
#include "d3dUtil.h"

GraphicObject_MultLights::GraphicObject_MultLights(ShaderColorMultLights * shader, Texture * tx, Model* mod)
{
	SetModel(mod);
	pShader = shader;

	World = Matrix(IDENTITY);

	//int n = mod->GetMeshCount();
	myTexture = tx;
	/*for (int i = 0; i < n; i++)
		myTextures[i] = tx[i];*/

	spotLightPositions[0] = Vect(10, 6, 10);
	spotLightPositions[1] = Vect(20, 6, -5);
	spotLightPositions[3] = Vect(0, 0, 0);

	pShader->SetDirectionalLightParameters(Vect(-1, -1, 1).getNorm(), .01 * Vect(1, 1, 1), .01 * Vect(1, 1, 1), Vect(1, 1, 1));

	pShader->SetPointLightParameters(Vect(0, 10, 0), 100, .3 * Vect(0, 1, 0), .1 * Vect(1, 1, 1), 0.2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));


	mTimer.Reset();

}

GraphicObject_MultLights::~GraphicObject_MultLights()
{
	//delete[] myTextures;
}

void GraphicObject_MultLights::SetTexture(Texture * tex)
{
	/*for (int i = 0; i < this->pModel->GetMeshCount(); i++)
		myTextures[i] = tex;*/

	myTexture = tex;
}

//void GraphicObject_MultLights::SetTexture(Texture * tex, int meshnum)
//{
//	assert(pModel->ValidMeshNum(meshnum));
//	myTextures[meshnum] = tex;
//}

void GraphicObject_MultLights::SetWorld(const Matrix& m)
{
	World = m;
}

Matrix GraphicObject_MultLights::GetWorld()
{
	return this->World;
}

Vect GraphicObject_MultLights::GetSpotLightPos(int index)
{
	return this->spotLightPositions[index];
}

void GraphicObject_MultLights::SetSpotlightPos(const Vect & pos, int index) {
	spotLightPositions[index] = pos;
}

void GraphicObject_MultLights::SetSpotLightParameters(int index, const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp)
{
	this->pShader->SetSpotLightParameters(index, pos, r, att, dir, spotExp, amb, dif, sp);
}

void GraphicObject_MultLights::SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb, const Vect& dif, const Vect& sp)
{
	pShader->SetPointLightParameters(pos, r, att, amb, dif, sp);
}

void GraphicObject_MultLights::ShaderSendLightParameters(const Vect & eyepos) {
	this->pShader->SendLightParameters(eyepos);
}

void GraphicObject_MultLights::ShaderSendCamMatrices(const Matrix& view, const Matrix& proj) {
	this->pShader->SendCamMatrices(view, proj);
}

void GraphicObject_MultLights::SetShaderToContext(ID3D11DeviceContext* devcon) {
	this->pShader->SetToContext(devcon);

	pShader->SetDirectionalLightParameters(Vect(-1, -1, 1).getNorm(), .1 * Vect(1, 1, 1), .1 * Vect(1, 1, 1), Vect(1, 1, 1));

	pShader->SetPointLightParameters(Vect(0, 10, 0), 100, .3 * Vect(0, 1, 0), .1 * Vect(1, 1, 1), 0.2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));
}

void GraphicObject_MultLights::Render()
{
	mTimer.Tick();

	/*pModel->BindVertexIndexBuffers(pShader->GetContext());

	for (int i = 0; i < pModel->GetMeshCount(); i++)
	{
		pShader->SetTextureResourceAndSampler(myTextures[i]);
		pShader->SendWorldAndMaterial(World, Colors::White, Colors::White, Vect(1, 1, 1, 100));
		pModel->RenderMesh(pShader->GetContext(), i);
	}*/

	pShader->SetTextureResourceAndSampler(myTexture);
	pShader->SendWorldAndMaterial(World, Colors::White, Colors::White, Vect(1, 1, 1, 100));
	pModel->Render(pShader->GetContext());
}