#ifndef _TerrainModel
#define _TerrainModel

#include "Matrix.h"
#include <tuple>
#include <d3d11.h>
#include "DirectXTex.h"

class Model;
struct ID3D11DeviceContext;
struct ID3D11Device;

class TerrainModel : public Align16
{

private:
	Model* pModTerrain;
	Matrix WorldMat;

	int TexelIndex(int side, int i, int j) const;
	static float normalizeX(float rawValue, int side);
	static float normalizeY(float rawValue);
	static float normalizeZ(float rawValue, int side);

	static void UpdateNorm(Vect & v1, Vect & v2);


public:
	TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV);

	Matrix GetWorldMat() { return WorldMat; }

	void Render(ID3D11DeviceContext* context);

	~TerrainModel();

};



#endif _TerrainModel