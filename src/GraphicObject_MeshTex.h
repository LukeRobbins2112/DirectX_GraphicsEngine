// GraphicObject_Color
// Andre Berthiaume, July 2016

#ifndef _GraphicObject_Color
#define _GraphicObject_Color

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderTextureLight.h"
#include "Texture.h"
#include "GameTimer.h"

class GraphicObject_MeshTex : public GraphicObject_Base
{
friend class ShaderColor;

public:
	GraphicObject_MeshTex(const GraphicObject_MeshTex&) = delete;				 // Copy constructor
	GraphicObject_MeshTex(GraphicObject_MeshTex&&) = default;                    // Move constructor
	GraphicObject_MeshTex& operator=(const GraphicObject_MeshTex&) & = default;  // Copy assignment operator
	GraphicObject_MeshTex& operator=(GraphicObject_MeshTex&&) & = default;       // Move assignment operator
	~GraphicObject_MeshTex();		  											 // Destructor

	GraphicObject_MeshTex() = delete;

	void SetTexture(Texture * tex);
	void SetTexture(Texture * tex, int meshnum);
	void SetWorld(const Matrix& m);
	void SetSpotlightPos(const Vect & pos);
	void SetSpotLightParameters(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb, const Vect& dif, const Vect& sp);
	void ShaderSendCamMatrices(const Matrix& view, const Matrix& proj);
	void ShaderSendLightParameters(const Vect & eyepos);
	void SetShaderToContext(ID3D11DeviceContext* devcon);

	virtual void Render() override;

	GraphicObject_MeshTex(ShaderTextureLight * shader, Texture ** tx, Model* mod);
	GraphicObject_MeshTex(ShaderTextureLight * shader, Texture * onetex, Model* mod);

private:
	ShaderTextureLight*				pShader;
	Texture **						myTextures;
	Texture *						singleTex;
	Matrix							World;
	Vect							spotLightPos;

	int numMeshes;

	bool SINGLE_TEXTURE;

	GameTimer mTimer;
};

#endif _GraphicObject_Color
