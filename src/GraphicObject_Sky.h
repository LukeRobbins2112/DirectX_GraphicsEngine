

#ifndef _GraphicObject_Sky
#define _GraphicObject_Sky

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderTexture.h"
#include "SkyBox.h"

class GraphicObject_Sky : public GraphicObject_Base
{
	friend class ShaderTexture;

public:
	GraphicObject_Sky(const GraphicObject_Sky&) = delete;				 // Copy constructor
	GraphicObject_Sky(GraphicObject_Sky&&) = default;                    // Move constructor
	GraphicObject_Sky& operator=(const GraphicObject_Sky&) & = default;  // Copy assignment operator
	GraphicObject_Sky& operator=(GraphicObject_Sky&&) & = default;       // Move assignment operator
	~GraphicObject_Sky();		  											 // Destructor

	GraphicObject_Sky() = delete;

	
	void SetSkybox(SkyBox * box);
	void SetTexture(Texture * tex);
	void SetWorld(const Matrix& m);
	void ShaderSendCamMatrices(const Matrix& view, const Matrix& proj);
	void SetShaderToContext(ID3D11DeviceContext* devcon);

	virtual void Render() override;

	GraphicObject_Sky(ShaderTexture * shader, Texture * tex, SkyBox * box);

private:
	ShaderTexture*					pShaderTex;
	Texture *						myTex;
	Matrix							World;
	SkyBox *						skyBox;

};

#endif _GraphicObject_Sky
