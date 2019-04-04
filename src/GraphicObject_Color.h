// GraphicObject_Color
// Andre Berthiaume, July 2016

#ifndef _GraphicObject_Color
#define _GraphicObject_Color

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderColorLight.h"
#include "Texture.h"
#include "GameTimer.h"

class GraphicObject_Color : public GraphicObject_Base
{
friend class ShaderColor;

public:
	GraphicObject_Color(const GraphicObject_Color&) = delete;				 // Copy constructor
	GraphicObject_Color(GraphicObject_Color&&) = default;                    // Move constructor
	GraphicObject_Color& operator=(const GraphicObject_Color&) & = default;  // Copy assignment operator
	GraphicObject_Color& operator=(GraphicObject_Color&&) & = default;       // Move assignment operator
	~GraphicObject_Color();		  											 // Destructor

	GraphicObject_Color() = delete;

	void SetTexture(Texture * tex);
	void SetTexture(Texture * tex, int meshnum);
	void SetWorld(const Matrix& m);
	void SetSpotlightPos(const Vect & pos);
	void ShaderSendCamMatrices(const Matrix& view, const Matrix& proj);
	void ShaderSendLightParameters(const Vect & eyepos);
	void SetShaderToContext(ID3D11DeviceContext* devcon);

	virtual void Render() override;

	GraphicObject_Color(ShaderColorLight * shader, Texture ** tx, Model* mod);

private:
	ShaderColorLight*				pShader;
	Texture **						myTextures;
	Matrix							World;
	Vect							spotLightPos;

	GameTimer mTimer;
};

#endif _GraphicObject_Color
