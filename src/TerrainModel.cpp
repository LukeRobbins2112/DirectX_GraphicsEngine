#include "TerrainModel.h"
#include "Model.h"
#include "d3dUtil.h"
#include "DirectXTex.h"
#include <assert.h>


TerrainModel::TerrainModel(ID3D11Device* dev, LPCWSTR heightmapFile, float len, float maxheight, float ytrans, int RepeatU, int RepeatV)
{
	DirectX::ScratchImage scrtTex;
	HRESULT hr = LoadFromTGAFile(heightmapFile, nullptr, scrtTex);
	assert(SUCCEEDED(hr));

	const DirectX::Image* hgtmap = scrtTex.GetImage(0, 0, 0);
	assert(hgtmap->height == hgtmap->width);

	const size_t side = hgtmap->height;	// the image should be square
	//size_t pixel_width = 4;			// 4 bytes RGBA per pixel - never referenced

	size_t numVertices = side * side;
	int numTriangles = (side - 1) * (side - 1) * 2;

	StandardVertex * vertices = new StandardVertex[numVertices];
	TriangleByIndex* pTriList = new TriangleByIndex[numTriangles];

	//for 2x2 map, the top right corner grey is the third texel, 
	//so it seems to go down each column: top left, bottom left, top right, bottom right
	//confirmed by 4x4 - all 0x0 until the 6th pixel, which is grey and 0xaf. First column going down, then second col...


	/*

	00--04--08--12      (-1.0, -1.0)--(-0.33, -1.0)--(+0.33, -1.0)--(+1.0, -1.0)
	|   |   |   |		       |               |           |            |
	v   v   v   v		       v               v           v            v
	01--05--09--13		(-1.0, -0.33)--(-0.33, -0.33)--(0.33, -0.33)--(1.0, -0.33)
	|   |   |   |		       |               |           |            |
	v   v   v   v		       v               v           v            v
	02--06--10--14		(-1.0, 0.33)--(-0.33, 0.33)--(0.33, 0.33)--(1.0, 0.33)
	|   |   |   |		       |               |           |            |
	v   v   v   v		       v               v           v            v
	03--07--11--15		(-1.0, 1.0)   (-0.33, 1.0)   (-0.33, 1.0)   (1.0, 1.0)

	***/

	//calculating and normalizing vertices coordinates

	int pos = 0;
	for (float i = 0; i < side; i++) {
		for (float j = 0; j < side; j++) {

			float xValue = normalizeX(i, side);		//took these out for easier debugging
			float zValue = normalizeZ(j, side);
			float rawY = (float)hgtmap->pixels[TexelIndex(side, (int)j, (int)i)];
			float yValue = normalizeY(rawY);

			vertices[pos++].set(xValue * len, yValue * maxheight, zValue * len, (i / (side - 1)) * (float)RepeatU, (j / (side - 1)) * (float)RepeatV);


			//vertices[side * (side - 1)].set(1, 1, 2);
			//vertices[3].set(2, 3, 2);

			//vertices[pos++].set(xValue, yValue, zValue, RepeatU, RepeatV);
		}
	}



	//second pass at triangle winding
	int triIndex = 0;
	int vertIndex = 0;
	for (unsigned int i = 0; i < (side - 1); i++) {

		for (unsigned int j = 0; j < (side - 1); j++) {
			vertIndex = (i * side) + j;
			pTriList[triIndex++].set(vertIndex, vertIndex + 1, vertIndex + side);
			pTriList[triIndex++].set(vertIndex + 1, vertIndex + side + 1, vertIndex + side);
		}
	}


	////
	//LIGHTING NORMALS
	// 

	//Calculate vertex normals

	triIndex = 0;
	vertIndex = 0;
	for (unsigned int i = 0; i < (side - 1); i++) {
		for (unsigned int j = 0; j < (side - 1); j++) {
			vertIndex = (i * side) + j;

			//SET VERTEX NORMAL FOR TOP LEFT FACE OF TRIANGLE
			Vect topLeftNorm = (vertices[vertIndex + 1].Pos - vertices[vertIndex].Pos).cross(vertices[vertIndex + side].Pos - vertices[vertIndex].Pos);

			UpdateNorm(vertices[vertIndex].normal, topLeftNorm);
			UpdateNorm(vertices[vertIndex + 1].normal, topLeftNorm);
			UpdateNorm(vertices[vertIndex + side].normal, topLeftNorm);


			//SET VERTEX NORMAL FOR TOP LEFT FACE OF TRIANGLE
			Vect bottomRightNorm = (vertices[vertIndex + side + 1].Pos - vertices[vertIndex + 1].Pos).cross(vertices[vertIndex + side].Pos - vertices[vertIndex + 1].Pos);

			UpdateNorm(vertices[vertIndex + 1].normal, bottomRightNorm);
			UpdateNorm(vertices[vertIndex + side + 1].normal, bottomRightNorm);
			UpdateNorm(vertices[vertIndex + side].normal, bottomRightNorm);

		}
	}

	pModTerrain = new Model(dev, vertices, numVertices, pTriList, numTriangles);
	WorldMat = Matrix(TRANS, 0, ytrans * maxheight, 0);

}

void TerrainModel::UpdateNorm(Vect & currentNorm, Vect & addNorm) {

	if (currentNorm.magSqr() == 0)
		currentNorm.set(addNorm);
	else
		currentNorm.set((currentNorm.X() + addNorm.X()) / 2, (currentNorm.Y() + addNorm.Y()) / 2, (currentNorm.Z() + addNorm.Z()) / 2);

}

void TerrainModel::Render(ID3D11DeviceContext* context)
{
	pModTerrain->Render(context);
}

int TerrainModel::TexelIndex(int side, int i, int j) const {

	return (i * side + j);		//4 is for the red channel, every 4 bytes: (R, G, B, A), (R, G, B, A)...
}

float TerrainModel::normalizeZ(float rawValue, int side) {

	float normVal = rawValue / (side - 1) * 2;		//calculates value in -1 to 1 range

	return (-1) + normVal;
}

float TerrainModel::normalizeX(float rawValue, int side) {

	float normVal = rawValue / (side - 1) * 2;		//calculates value in -1 to 1 range

	return (-1) + normVal;
}

float TerrainModel::normalizeY(float rawValue) {
	return (-1) + (rawValue / 255 * 2);
}

TerrainModel::~TerrainModel() {
	delete pModTerrain;
}