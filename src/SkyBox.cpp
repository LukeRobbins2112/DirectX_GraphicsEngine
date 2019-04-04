#include "SkyBox.h"
#include "Model.h"
#include "d3dUtil.h"

SkyBox::SkyBox(ID3D11Device* dev, float len, float ytrans)
{

	int nverts = 24;
	StandardVertex* pVerts = new StandardVertex[nverts];

	int ntri = 12;
	TriangleByIndex* pTriList = new TriangleByIndex[ntri];

	int vertIndex = 0;
	int triIndex = 0;

	//front face

	pVerts[vertIndex + 0].set(-0.5f * len, +0.5001f * len, +0.5f * len, 0.75, 0.333333);		//top left
	pVerts[vertIndex + 1].set(+0.5f * len, +0.5001f * len, +0.5f * len, 1.0, 0.333333);					//top right
	pVerts[vertIndex + 2].set(+0.5f * len, -0.5001f * len, +0.5f * len, 1.0, 0.666667);				//bottom right
	pVerts[vertIndex + 3].set(-0.5f * len, -0.5001f * len, +0.5f * len, 0.75, 0.666667);				//bottom left

																										//FRONT FACES BACKWARDS -- WIND CLOCKWISE
	pTriList[triIndex + 0].set(vertIndex + 0, vertIndex + 1, vertIndex + 2);		//top right	
	pTriList[triIndex + 1].set(vertIndex + 0, vertIndex + 2, vertIndex + 3);		//bottom left

	vertIndex += 4;
	triIndex += 2;

	//back face





	pVerts[vertIndex + 0].set(-0.5f * len, +0.5001f * len, -0.5f * len, 0.5, 0.333333);		//top left
	pVerts[vertIndex + 1].set(+0.5f * len, +0.5001f * len, -0.5f * len, 0.25, 0.333333);					//top right
	pVerts[vertIndex + 2].set(+0.5f * len, -0.5001f * len, -0.5f * len, 0.25, 0.666667);				//bottom right
	pVerts[vertIndex + 3].set(-0.5f * len, -0.5001f * len, -0.5f * len, 0.5, 0.666667);				//bottom left

																									//BACK FACES FRONT -- WIND COUNTER-CLOCKWISE
	pTriList[triIndex + 0].set(vertIndex + 0, vertIndex + 2, vertIndex + 1);		//Top right	
	pTriList[triIndex + 1].set(vertIndex + 0, vertIndex + 3, vertIndex + 2);		//bottom left 

	vertIndex += 4;
	triIndex += 2;

	//right face


	pVerts[vertIndex + 0].set(+0.5f * len, +0.5001f * len, +0.5f * len, 0, 0.3333);		//top left
	pVerts[vertIndex + 1].set(+0.5f * len, +0.5001f * len, -0.5f * len, 0.25, 0.33333);					//top right
	pVerts[vertIndex + 2].set(+0.5f * len, -0.5001f * len, -0.5f * len, 0.25, 0.666667);				//bottom right
	pVerts[vertIndex + 3].set(+0.5f * len, -0.5001f * len, +0.5f * len, 0, 0.666667);				//bottom left

																									//RIGHT FACES LEFT -- WIND CLOCKWISE
	pTriList[triIndex + 0].set(vertIndex + 0, vertIndex + 1, vertIndex + 2);		//Top right	
	pTriList[triIndex + 1].set(vertIndex + 0, vertIndex + 2, vertIndex + 3);		//bottom left 

	vertIndex += 4;
	triIndex += 2;

	//left face

	pVerts[vertIndex + 0].set(-0.5f * len, +0.5001f * len, -0.5f * len, 0.5, 0.33333);		//top left
	pVerts[vertIndex + 1].set(-0.5f * len, +0.5001f * len, +0.5f * len, 0.75, 0.33333);					//top right
	pVerts[vertIndex + 2].set(-0.5f * len, -0.5001f * len, +0.5f * len, 0.75, 0.666667);				//bottom right
	pVerts[vertIndex + 3].set(-0.5f * len, -0.5001f * len, -0.5f * len, 0.5, 0.666667);				//bottom left

																									//LEFT FACES RIGHT -- WIND CLOCKWISE
	pTriList[triIndex + 0].set(vertIndex + 0, vertIndex + 1, vertIndex + 2);		//Top right	
	pTriList[triIndex + 1].set(vertIndex + 0, vertIndex + 2, vertIndex + 3);		//bottom left 

	vertIndex += 4;
	triIndex += 2;

	//top face

	pVerts[vertIndex + 0].set(-0.501f * len, +0.495f * len, -0.501f * len, 0.5, 0.3334);		//back left
	pVerts[vertIndex + 1].set(+0.501f * len, +0.495f * len, -0.501f * len, 0.25, 0.3334);					//back right
	pVerts[vertIndex + 2].set(+0.501f * len, +0.495f * len, +0.501f * len, 0.25, 0);				//front right
	pVerts[vertIndex + 3].set(-0.501f * len, +0.495f * len, +0.501f * len, 0.5, 0);				//front left

																								//TOP FACES DOWN -- WIND CLOCKWISE
	pTriList[triIndex + 0].set(vertIndex + 0, vertIndex + 1, vertIndex + 2);		//Top right	
	pTriList[triIndex + 1].set(vertIndex + 0, vertIndex + 2, vertIndex + 3);		//bottom left 

	vertIndex += 4;
	triIndex += 2;

	pTriList[0].set(0, 1, 2);
	pTriList[1].set(0, 2, 3);

	//bottom face

	pVerts[vertIndex + 0].set(-0.501f * len, -0.495f * len, -0.501f * len, 0.5, 0.666665);		//back left
	pVerts[vertIndex + 1].set(+0.501f * len, -0.495f * len, -0.501f * len, 0.25, 0.666665);					//back right
	pVerts[vertIndex + 2].set(+0.501f * len, -0.495f * len, +0.501f * len, 0.25, 1.0);				//front right
	pVerts[vertIndex + 3].set(-0.501f * len, -0.495f * len, +0.501f * len, 0.5, 1.0);				//front left

																									//LEFT FACES RIGHT -- WIND CLOCKWISE
	pTriList[triIndex + 0].set(vertIndex + 0, vertIndex + 2, vertIndex + 1);		//Top right	
	pTriList[triIndex + 1].set(vertIndex + 0, vertIndex + 3, vertIndex + 2);		//bottom left 

	skyBox = new Model(dev, pVerts, nverts, pTriList, ntri);

	worldMatrix = Matrix(TRANS, 0, ytrans, 0);
}

SkyBox::~SkyBox()
{
	delete skyBox;
}

void SkyBox::Render(ID3D11DeviceContext* context)
{
	skyBox->Render(context);
}