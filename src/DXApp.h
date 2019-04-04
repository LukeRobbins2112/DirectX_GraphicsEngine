// DXApp
// Note: DX 11 SDK https://www.microsoft.com/en-us/download/details.aspx?id=6812
// Note on weird stuff with swap chain (1s and 2s) https://msdn.microsoft.com/en-us/library/windows/desktop/jj863687(v=vs.85).aspx

#ifndef _DXApp
#define _DXApp

#include <d3d11.h>
#include "d3dUtil.h"
#include "Align16.h"
#include "GameTimer.h"
#include <string>

// New includes for demo
#include "Vect.h"
#include "Matrix.h"
#include "Camera.h"
#include "ShaderColor.h"
#include "ShaderLightColor.h"
#include "ShaderTextureLight.h"
#include "ShaderColorMultLights.h"
#include "SkyBox.h"
#include "GraphicObject_Sky.h"
#include "GraphicObject_Terrain.h"
#include "GraphicObject_MultLights.h"
#include "GraphicObject_ColorLight.h"

class Model;
class Texture;
class FlatPlane;
class TerrainModel;
class GraphicObject_MeshTex;
class ShaderTexture;
class GraphicObject_Texture;

class DXApp : public Align16
{
private:	
	// Main window handle
	HWND      mhMainWnd;

	Vect BackgroundColor;

	// DX application elements
	ID3D11Device* md3dDevice;					// Connects to the graphics card
	ID3D11DeviceContext* md3dImmediateContext;	// Settings for the GPU to use
	IDXGISwapChain* mSwapChain;					// image buffers used for rendering
	ID3D11RenderTargetView* mRenderTargetView;	// Where to send rendring operations (typically: points to one of the swap buffers)
	ID3D11DepthStencilView* mpDepthStencilView; // Needed to force depth-buffer operations

	GameTimer mTimer;
	std::wstring mMainWndCaption;
	int mClientWidth;
	int mClientHeight;

	void InitDirect3D();
	void InitDemo();
	void UpdateScene();
	void DrawScene();
	void CalculateFrameStats();

	// Shader loading utility. SHould be moved elsewhere later...
	//HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	// Debug utility
	void ReportLiveDXObjects();

	// Demo specific additions
	Camera mCam;

	//Models
	Model* pModelAstronaut;
	Model * pPyramidModel;
	Model* pModelRobot;
	Model * pModelShip;
	SkyBox * skyBox;
	TerrainModel* pTerrain;

	Model * outpost;

	//World Matrices
	Matrix mWorld1;
	Matrix mWorld2;
	Matrix mWorld3;
	Matrix mWorld4;
	Matrix mWorld5;
	Matrix mWorld6;
	Matrix mWorld7;
	Matrix mWorld8;
	Matrix mWorld9;
	Matrix evilRobotWorlds[5];

	//Test

	Vect SatelliteSpotlightPos;

	//Shaders
	ShaderLightColor * pShaderLightColor;
	ShaderColorMultLights * pShaderMultLights;
	ShaderTexture*			pShaderTex;
	ShaderTextureLight *		pShaderTextureLight;
	

	//Textures
	Texture * textures[4];
	Texture * astronautTexture;
	Texture * shipTex;
	Texture * skyTex;
	Texture * mTexPlane;
	Texture * alienTex;
	Texture * evilAlienTex;

	//Graphic Objects

	GraphicObject_ColorLight * PyramidObject;
	GraphicObject_ColorLight * Satellite;
	GraphicObject_MultLights * Astronaut;		//Multiple lights
	GraphicObject_MultLights * Ship;
	GraphicObject_MultLights * Robot;		//Multiple lights
	GraphicObject_MultLights * EvilRobot;		//Multiple lights

	GraphicObject_Sky * SkyObj1;				//Skybox
	GraphicObject_Terrain * TerrainObj1;			//Terrain

	GraphicObject_MeshTex * meshExample;



	

	// gimmicky mouse control
	Vect MousePos;		
	float mTheta;
	float mPhi;
	float mRadius;
	
public:
	DXApp(HWND hwnd);
	virtual ~DXApp();
	
	void FrameTick();

	// overrides for handling mouse input.
	void OnMouseDown(WPARAM btnState, int xval, int yval);
	void OnMouseUp(WPARAM btnState, int xval, int yval);
	void OnMouseMove(WPARAM btnState, int xval, int yval);
	void OnMouseWheel(short delta);


};

#endif _DXApp