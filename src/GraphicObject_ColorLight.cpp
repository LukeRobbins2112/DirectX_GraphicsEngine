#include "GraphicObject_ColorLight.h"
#include "Model.h"
#include "ShaderLightColor.h"
#include <assert.h>
#include "d3dUtil.h"

GraphicObject_ColorLight::GraphicObject_ColorLight(ShaderLightColor * shader, Model* mod)
{
	SetModel(mod);
	pShader = shader;

	pShader->SetDirectionalLightParameters(Vect(-1, -1, 1).getNorm(), 0.0 * Vect(1, 1, 1), 0.0 * Vect(1, 1, 1), Vect(1, 1, 1));

	pShader->SetPointLightParameters(Vect(0, 10, 0), 100, .1 * Vect(0, 1, 0), .1 * Vect(1, 1, 1), 0.1 * Vect(1, 1, 1), 1 * Vect(1, 1, 1));

	Color = Vect(1, 1, 1);
	World = Matrix(IDENTITY);
	spotLightPos = Vect(0, 0, -4);
}

GraphicObject_ColorLight::~GraphicObject_ColorLight()
{

}

void GraphicObject_ColorLight::SetColor(const Vect& col)
{
	Color = col;
}

void GraphicObject_ColorLight::SetWorld(const Matrix& m)
{
	World = m;
}

void GraphicObject_ColorLight::SetSpotLightParameters(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb, const Vect& dif, const Vect& sp)
{
	this->pShader->SetSpotLightParameters(pos, r, att, dir, spotExp, amb, dif, sp);
}

void GraphicObject_ColorLight::SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb, const Vect& dif, const Vect& sp)
{
	pShader->SetPointLightParameters(pos, r, att, amb, dif, sp);
}

void GraphicObject_ColorLight::SetSpotlightPos(const Vect & pos) {
	spotLightPos = pos;
}

void GraphicObject_ColorLight::SetEyePos(const Vect & pos) {
	eyePos = pos;
}

void GraphicObject_ColorLight::ShaderSendLightParameters(const Vect & eyepos) {
	this->pShader->SendLightParameters(eyepos);
}

void GraphicObject_ColorLight::ShaderSendCamMatrices(const Matrix& view, const Matrix& proj) {
	this->pShader->SendCamMatrices(view, proj);
}

void GraphicObject_ColorLight::SetShaderToContext(ID3D11DeviceContext* devcon) {
	this->pShader->SetToContext(devcon);
}

void GraphicObject_ColorLight::Render()
{

	pShader->SendWorldAndMaterial(World, Color, Color, Vect(1, 1, 1, 100));

	pShader->SendLightParameters(eyePos);
	pModel->Render(pShader->GetContext());
}