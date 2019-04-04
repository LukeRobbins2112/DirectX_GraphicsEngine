

#ifndef _GraphicObject_MultLights
#define _GraphicObject_MultLights

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderColorMultLights.h"
#include "Texture.h"
#include "GameTimer.h"

class GraphicObject_MultLights : public GraphicObject_Base
{
	friend class ShaderColorMultLights;

public:
	GraphicObject_MultLights(const GraphicObject_MultLights&) = delete;				 // Copy constructor
	GraphicObject_MultLights(GraphicObject_MultLights&&) = default;                    // Move constructor
	GraphicObject_MultLights& operator=(const GraphicObject_MultLights&) & = default;  // Copy assignment operator
	GraphicObject_MultLights& operator=(GraphicObject_MultLights&&) & = default;       // Move assignment operator
	~GraphicObject_MultLights();		  											 // Destructor

	GraphicObject_MultLights() = delete;

	void SetTexture(Texture * tex);
	//void SetTexture(Texture * tex, int meshnum);
	void SetWorld(const Matrix& m);
	Matrix GetWorld();
	Vect GetSpotLightPos(int index);
	void SetSpotlightPos(const Vect & pos, int index);
	void SetSpotLightParameters(int index, const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb, const Vect& dif, const Vect& sp);
	void ShaderSendCamMatrices(const Matrix& view, const Matrix& proj);
	void ShaderSendLightParameters(const Vect & eyepos);
	void SetShaderToContext(ID3D11DeviceContext* devcon);

	virtual void Render() override;

	GraphicObject_MultLights(ShaderColorMultLights * shader, Texture * tx, Model* mod);

private:
	ShaderColorMultLights*				pShader;
	Texture *						myTexture;
	Matrix							World;
	Vect                         spotLightPositions [3] ;


	GameTimer mTimer;
};

#endif _GraphicObject_MultLights
