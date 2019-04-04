

#ifndef _GraphicObject_Terrain
#define _GraphicObject_Terrain

#include "GraphicObject_Base.h"
#include "Vect.h"
#include "ShaderTexture.h"
#include "ShaderColorMultLights.h"
#include "TerrainModel.h"
#include "d3dUtil.h"

class GraphicObject_Terrain : public GraphicObject_Base
{
	friend class ShaderColorMultLights;

public:
	GraphicObject_Terrain(const GraphicObject_Terrain&) = delete;				 // Copy constructor
	GraphicObject_Terrain(GraphicObject_Terrain&&) = default;                    // Move constructor
	GraphicObject_Terrain& operator=(const GraphicObject_Terrain&) & = default;  // Copy assignment operator
	GraphicObject_Terrain& operator=(GraphicObject_Terrain&&) & = default;       // Move assignment operator
	~GraphicObject_Terrain();		  											 // Destructor

	GraphicObject_Terrain() = delete;


	void SetTerrain(TerrainModel * box);
	void SetTexture(Texture * tex);
	//void SetTexture(Texture * tex, int meshnum);

	void SetSpotlightPos(const Vect & pos, int index);
	void ShaderSendLightParameters(const Vect & eyepos);

	void SetWorld(const Matrix& m);
	void ShaderSendCamMatrices(const Matrix& view, const Matrix& proj);
	void SetShaderToContext(ID3D11DeviceContext* devcon);


	virtual void Render() override;

	GraphicObject_Terrain(ShaderColorMultLights * shader, Texture * tex, TerrainModel * terrain);

private:
	ShaderColorMultLights*			pShader;
	Texture *						myTex;
	Matrix							World;
	TerrainModel *					pTerrain;
	Vect							spotLightPositions[3];

};

#endif _GraphicObject_Terrain
