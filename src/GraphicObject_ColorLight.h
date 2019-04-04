// GraphicObject_ColorLight
// Andre Berthiaume, July 2016

#ifndef _GraphicObject_ColorLight
#define _GraphicObject_ColorLight

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderLightColor.h"

class GraphicObject_ColorLight : public GraphicObject_Base
{
	friend class ShaderColor;

public:
	GraphicObject_ColorLight(const GraphicObject_ColorLight&) = delete;				 // Copy constructor
	GraphicObject_ColorLight(GraphicObject_ColorLight&&) = default;                    // Move constructor
	GraphicObject_ColorLight& operator=(const GraphicObject_ColorLight&) & = default;  // Copy assignment operator
	GraphicObject_ColorLight& operator=(GraphicObject_ColorLight&&) & = default;       // Move assignment operator
	~GraphicObject_ColorLight();		  											 // Destructor

	GraphicObject_ColorLight() = delete;

	void SetColor(const Vect& col);
	void SetWorld(const Matrix& m);
	void SetPointLightParameters(const Vect& pos, float r, const Vect& att, const Vect& amb, const Vect& dif, const Vect& sp);
	void SetSpotLightParameters(const Vect& pos, float r, const Vect& att, const Vect& dir, float spotExp, const Vect& amb = Vect(1, 1, 1), const Vect& dif = Vect(1, 1, 1), const Vect& sp = Vect(1, 1, 1));
	void SetSpotlightPos(const Vect & pos);
	void SetEyePos(const Vect & pos);
	void ShaderSendCamMatrices(const Matrix& view, const Matrix& proj);
	void ShaderSendLightParameters(const Vect & eyepos);
	void SetShaderToContext(ID3D11DeviceContext* devcon);

	virtual void Render() override;

	GraphicObject_ColorLight(ShaderLightColor * shader, Model* mod);

private:
	ShaderLightColor*				pShader;
	Vect							Color;
	Matrix							World;
	Vect							spotLightPos;
	Vect							eyePos;

};

#endif _GraphicObject_ColorLight
