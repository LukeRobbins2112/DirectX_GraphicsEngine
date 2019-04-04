#include "GraphicObject_MeshTex.h"
#include "Model.h"
#include "ShaderTextureLight.h"
#include <assert.h>
#include "d3dUtil.h"

GraphicObject_MeshTex::GraphicObject_MeshTex(ShaderTextureLight * shader, Texture ** tx,  Model* mod)
{
	SetModel(mod );
	pShader = shader;

	World = Matrix(IDENTITY);

	this->numMeshes = mod->GetMeshCount();

	int n = mod->GetMeshCount();
	myTextures = new Texture * [n];
	for (int i = 0; i < n; i++)
		myTextures[i] = tx[i];

	spotLightPos = Vect(0, 0, -4);

	pShader->SetDirectionalLightParameters(Vect(-1, -1, 1).getNorm(), .2 * Vect(1, 1, 1), .2 * Vect(1, 1, 1), Vect(1, 1, 1));

	pShader->SetPointLightParameters(Vect(0, 10, 0), 100, .3 * Vect(0, 1, 0), .1 * Vect(1, 1, 1), .2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));

	mTimer.Reset();

	SINGLE_TEXTURE = false;
	
}

GraphicObject_MeshTex::GraphicObject_MeshTex(ShaderTextureLight * shader, Texture * tx, Model* mod)
{
	SetModel(mod);
	pShader = shader;

	World = Matrix(IDENTITY);

	this->singleTex = tx;
	SINGLE_TEXTURE = true;

	spotLightPos = Vect(0, 0, -4);

	pShader->SetDirectionalLightParameters(Vect(-1, -1, 1).getNorm(), .2 * Vect(1, 1, 1), .2 * Vect(1, 1, 1), Vect(1, 1, 1));

	pShader->SetPointLightParameters(Vect(0, 10, 0), 100, .3 * Vect(0, 1, 0), .1 * Vect(1, 1, 1), 2 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));

	mTimer.Reset();

}

GraphicObject_MeshTex::~GraphicObject_MeshTex()
{
	/*for (int i = 0; i < this->numMeshes; i++) {
		delete this->myTextures[i];
	}*/
	//delete[] myTextures;
}

void GraphicObject_MeshTex::SetTexture(Texture * tex)
{
	for (int i = 0; i < this->pModel->GetMeshCount(); i++)
		myTextures[i] = tex;
}

void GraphicObject_MeshTex::SetTexture(Texture * tex, int meshnum)
{
	assert(pModel->ValidMeshNum(meshnum));
	myTextures[meshnum] = tex;
}

void GraphicObject_MeshTex::SetWorld(const Matrix& m) 
{ 
	World = m;
}

void GraphicObject_MeshTex::SetSpotlightPos(const Vect & pos) {
	spotLightPos = pos;
}

void GraphicObject_MeshTex::SetSpotLightParameters(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp)
{
	this->pShader->SetSpotLightParameters(pos, r, att, dir, spotExp, amb, dif, sp);
}

void GraphicObject_MeshTex::SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb, const Vect& dif, const Vect& sp)
{
	pShader->SetPointLightParameters(pos, r, att, amb, dif, sp);
}

void GraphicObject_MeshTex::ShaderSendLightParameters(const Vect & eyepos) {
	this->pShader->SendLightParameters(eyepos);
}

void GraphicObject_MeshTex::ShaderSendCamMatrices(const Matrix& view, const Matrix& proj) {
	this->pShader->SendCamMatrices(view, proj);
}

void GraphicObject_MeshTex::SetShaderToContext(ID3D11DeviceContext* devcon) {
	this->pShader->SetToContext(devcon);
}

void GraphicObject_MeshTex::Render()
{
	mTimer.Tick();

	pShader->SetSpotLightParameters(spotLightPos, 4000, .5 * Vect(1, 0, 0),
		-spotLightPos.getNorm(), 50,
		.6 * Vect(1, 1, 1), 3 * Vect(1, 1, 1), 1 * Vect(1, 1, 1, 150));


	pModel->BindVertexIndexBuffers(pShader->GetContext());

	if (SINGLE_TEXTURE) {
		pShader->SetTextureResourceAndSampler(singleTex);
		pShader->SendWorldAndMaterial(World, Colors::White, Colors::White, Vect(1, 1, 1, 100));
		pModel->Render(pShader->GetContext());
	}
	else {
		for (int i = 0; i < pModel->GetMeshCount(); i++)
		{
			pShader->SetTextureResourceAndSampler(myTextures[i]);
			pShader->SendWorldAndMaterial(World, Colors::White, Colors::White, Vect(1, 1, 1, 100));
			pModel->RenderMesh(pShader->GetContext(), i);
		}
	}
	
}