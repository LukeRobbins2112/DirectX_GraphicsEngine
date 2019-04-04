#include "GraphicObject_Terrain.h"
#include "Model.h"
#include "ShaderColor.h"
#include <assert.h>

GraphicObject_Terrain::GraphicObject_Terrain(ShaderColorMultLights * shader, Texture * tex, TerrainModel * terrain)
{
	SetTerrain(terrain);

	pShader = shader;

	World = terrain->GetWorldMat();

	this->myTex = tex;

	//int n = mod->GetMeshCount();
	/*myTextures = new Texture *[n];
	for (int i = 0; i < n; i++)
		myTextures[i] = tx[i];*/

	spotLightPositions[0] = Vect(10, 10, 10);
	spotLightPositions[1] = Vect(20, 10, -5);
	spotLightPositions[2] = Vect(0, 0, 0);

	pShader->SetDirectionalLightParameters(Vect(-1, -1, 1).getNorm(), .1 * Vect(1, 1, 1), .01 * Vect(1, 1, 1), Vect(1, 1, 1));

	pShader->SetPointLightParameters(Vect(0, 10, 0), 100, .3 * Vect(0, 1, 0), .1 * Vect(1, 1, 1), 0.2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));

	

}

GraphicObject_Terrain::~GraphicObject_Terrain()
{

}

void GraphicObject_Terrain::SetTerrain(TerrainModel * terrain) {
	this->pTerrain = terrain;
}

void GraphicObject_Terrain::SetTexture(Texture * tex)
{
	/*for (int i = 0; i < this->pModel->GetMeshCount(); i++)
		myTextures[i] = tex;*/

	this->myTex = tex;
}

//void GraphicObject_MultLights::SetTexture(Texture * tex, int meshnum)
//{
//	assert(pModel->ValidMeshNum(meshnum));
//	myTextures[meshnum] = tex;
//}

void GraphicObject_Terrain::SetWorld(const Matrix& m)
{
	World = m;
}

void GraphicObject_Terrain::SetSpotlightPos(const Vect & pos, int index) {
	spotLightPositions[index] = pos;
}

void GraphicObject_Terrain::ShaderSendLightParameters(const Vect & eyepos) {
	this->pShader->SendLightParameters(eyepos);
}


void GraphicObject_Terrain::ShaderSendCamMatrices(const Matrix& view, const Matrix& proj) {
	this->pShader->SendCamMatrices(view, proj);
}

void GraphicObject_Terrain::SetShaderToContext(ID3D11DeviceContext* devcon) {
	this->pShader->SetToContext(devcon);

	pShader->SetDirectionalLightParameters(Vect(-1, -1, 1).getNorm(), .1 * Vect(1, 1, 1), .1 * Vect(1, 1, 1), Vect(1, 1, 1));

	pShader->SetPointLightParameters(Vect(0, 10, 0), 100, .3 * Vect(0, 1, 0), .1 * Vect(1, 1, 1), 0.2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));
}

void GraphicObject_Terrain::Render()
{
	//mTimer.Tick();

	//pShader->SetSpotLightParameters(0, spotLightPos, 1000, .5 * Vect(1, 0, 0),
	//	Vect(0, -1, 0), 50,
	//	.6 * Vect(1, 1, 1), .6 * Vect(1, 1, 1), 1 * Vect(1, 1, 1, 150));

	pShader->SetSpotLightParameters(0, spotLightPositions[0], 1000, .5 * Vect(1, 0, 0),
		Vect(0, -1, 0), 50,
		.6 * Vect(1, 1, 1), .6 * Vect(1, 1, 1), 1 * Vect(1, 1, 1, 150));

	pShader->SetTextureResourceAndSampler(myTex);
	pShader->SendWorldAndMaterial(World*Matrix(TRANS, 0, /*cosf(mTimer.TotalTime())*/ 0, 0), Colors::White, Colors::White, Vect(1, 1, 1, 100));
	pTerrain->Render(pShader->GetContext());
}