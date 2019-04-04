#include "ModelTools.h"
//#include "Enum.h"
//#include <math.h>
#include "Matrix.h"
#include <assert.h>
#include "Model.h"
#include "d3dUtil.h"


/// Creates the unit box centered at the origin
void ModelTools::CreateUnitBox(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = 8;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	pVerts[0].set(-0.5f, -0.5f, -0.5f, Colors::Black);
	pVerts[1].set(-0.5f, +0.5f, -0.5f, Colors::Lime);
	pVerts[2].set(+0.5f, +0.5f, -0.5f, Colors::Yellow);
	pVerts[3].set(+0.5f, -0.5f, -0.5f, Colors::Red);
	pVerts[4].set(-0.5f, -0.5f, +0.5f, Colors::Blue);
	pVerts[5].set(-0.5f, +0.5f, +0.5f, Colors::Cyan);
	pVerts[6].set(+0.5f, +0.5f, +0.5f, Colors::White);
	pVerts[7].set(+0.5f, -0.5f, +0.5f, Colors::Magenta);

	/*
	pVerts[0].set(-0.5f, -0.5f, -0.5f, 0, 0, 1.0f, 0.5f, 0.5f, );
	pVerts[1].set(-0.5f, +0.5f, -0.5f, 0, 0, 1.0f, 0.5f, 0.5f, );
	pVerts[2].set(+0.5f, +0.5f, -0.5f, 0, 0, 1.0f, 0.5f, 0.5f, );
	pVerts[3].set(+0.5f, -0.5f, -0.5f, 0, 0, 1.0f, 0.5f, 0.5f, );
	pVerts[4].set(-0.5f, -0.5f, +0.5f, 0, 0, 1.0f, 0.5f, 0.5f, );
	pVerts[5].set(-0.5f, +0.5f, +0.5f, 0, 0, 1.0f, 0.5f, 0.5f, );
	pVerts[6].set(+0.5f, +0.5f, +0.5f, 0, 0, 1.0f, 0.5f, 0.5f, );
	pVerts[7].set(+0.5f, -0.5f, +0.5f, 0, 0, 1.0f, 0.5f, 0.5f, );
	*/

	// back face
	pTriList[0].set(0, 1, 2);
	pTriList[1].set(0, 2, 3);

	// front face
	pTriList[2].set(4, 6, 5);
	pTriList[3].set(4, 7, 6);

	// left face
	pTriList[4].set(4, 5, 1);
	pTriList[5].set(4, 1, 0);

	// right face
	pTriList[6].set(3, 2, 6);
	pTriList[7].set(3, 6, 7);

	// top face
	pTriList[8].set(1, 5, 6);
	pTriList[9].set(1, 6, 2);

	// bottom face
	pTriList[10].set(4, 0, 3);
	pTriList[11].set(4, 3, 7);
}

void ModelTools::CreateUnitBoxRepTexture(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri)
{
	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];



	// Setting up faces
	// Forward
	int vind = 0;
	int tind = 0;
	pVerts[vind].set(0.5f, 0.5f, 0.5f, 1, 0, 0, 0, 1);      //front top right
	pVerts[vind + 1].set(-0.5f, 0.5f, 0.5f, 0, 0, 0, 0, 1);  //front top left
	pVerts[vind + 2].set(-0.5f, -0.5f, 0.5f, 0, 1, 0, 0, 1);  //front bottom left
	pVerts[vind + 3].set(0.5f, -0.5f, 0.5f, 1, 1, 0, 0, 1);	  //front bottom right
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Back
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 0, 0, 0, 0, -1);         //back top right -- top left of face
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 1, 0, 0, 0, -1);	 //back top left -- top right of face
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 1, 1, 0, 0, -1);	//back bottom left -- bottom right of face
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 0, 1, 0, 0, -1);	//back bottom right -- bottom left of face
	pTriList[tind].set(vind + 2, vind + 1, vind);
	pTriList[tind + 1].set(vind + 3, vind + 2, vind);

	// Left
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 1, 0, 0);		  //back top right -- top right of image
	pVerts[vind + 1].set(0.5f, 0.5f, 0.5f, 0, 0, 1, 0, 0);	  //front top right - top left of image
	pVerts[vind + 2].set(0.5f, -0.5f, 0.5f, 0, 1, 1, 0, 0);	  //front bottom right - bottom left of image
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 1, 0, 0);  //back bottom right -- bottom right of image
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Right
	vind += 4;
	tind += 2;
	pVerts[vind].set(-0.5f, 0.5f, 0.5f, 1, 0, -1, 0, 0);		//front top left -- top right of face (1, 0)
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, -1, 0, 0);	//back top left -- top left of face (0, 0)
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, -1, 0, 0);	//back bottom left -- bottom left of face (0, 1)
	pVerts[vind + 3].set(-0.5f, -0.5f, 0.5f, 1, 1, -1, 0, 0);	//fron bottom left -- bottom right of face  (1, 1)
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Top
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, 0.5f, -0.5f, 1, 0, 0, 1, 0);			//back top right -- top right of face (1, 0)
	pVerts[vind + 1].set(-0.5f, 0.5f, -0.5f, 0, 0, 0, 1, 0);	//back top left -- top left of face (0, 0)
	pVerts[vind + 2].set(-0.5f, 0.5f, 0.5f, 0, 1, 0, 1, 0);		//front top left -- bottom left of face (0, 1)
	pVerts[vind + 3].set(0.5f, 0.5f, 0.5f, 1, 1, 0, 1, 0);		//front top right -- bottom right of face (1, 1)
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);

	// Bottom
	vind += 4;
	tind += 2;
	pVerts[vind].set(0.5f, -0.5f, 0.5f, 1, 0, 0, -1, 0);		//front bottom right -- top right of face (0, 1)
	pVerts[vind + 1].set(-0.5f, -0.5f, 0.5f, 0, 0, 0, -1, 0);	//front bottom left	-- top left of face (0, 0)
	pVerts[vind + 2].set(-0.5f, -0.5f, -0.5f, 0, 1, 0, -1, 0);	//back bottom left  -- bottom left of face (1, 0)
	pVerts[vind + 3].set(0.5f, -0.5f, -0.5f, 1, 1, 0, -1, 0);	//back bottom right -- bottom right of face (1, 1)
	pTriList[tind].set(vind, vind + 1, vind + 2);
	pTriList[tind + 1].set(vind, vind + 2, vind + 3);
}


void ModelTools::CreateUnitBoxSixFaceTexture(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri) {

	nverts = 24;
	pVerts = new StandardVertex[nverts];
	ntri = 12;
	pTriList = new TriangleByIndex[ntri];

	int vertIndex = 0;
	int triIndex = 0;

	//front face -- top left tri -- top right front, top left front, bottom left front
	//front face -- bottom right tri -- bottom right front, top right front, bottom left front
	pVerts[vertIndex].set(+0.5f, +0.5f, +0.5f, 0.25f, 0.625f, 0, 0, 1);		//top right front
	pVerts[vertIndex + 1].set(-0.5f, +0.5f, +0.5f, 0.25f, 0.375f, 0, 0, 1);	//top left front
	pVerts[vertIndex + 2].set(-0.5f, -0.5f, +0.5f, 0.0f, 0.375f, 0, 0, 1);	//bottom left front
	pVerts[vertIndex + 3].set(+0.5f, -0.5f, +0.5f, 0.0f, 0.625f, 0, 0, 1);		//bottom right front
	pTriList[triIndex].set(vertIndex, vertIndex + 1, vertIndex + 2);
	pTriList[triIndex + 1].set(vertIndex, vertIndex + 2, vertIndex + 3);

	vertIndex += 4;
	triIndex += 2;

	//
	//back
	//

	//back face -- top left tri -- back top right, back top left, back bottom left
	//back face -- bottom right tri -- back bottom right, back top right, back bottom left
	pVerts[vertIndex].set(+0.5f, +0.5f, -0.5f, 0.5f, 0.625f, 0, 0, -1);		//back top right
	pVerts[vertIndex + 1].set(-0.5f, +0.5f, -0.5f, 0.5f, 0.375f, 0, 0, -1);		//back top left
	pVerts[vertIndex + 2].set(-0.5f, -0.5f, -0.5f, 0.75f, 0.375f, 0, 0, -1);		//back bottom left
	pVerts[vertIndex + 3].set(+0.5f, -0.5f, -0.5f, 0.75f, 0.625f, 0, 0, -1);		//back bottom right
	pTriList[triIndex].set(vertIndex + 2, vertIndex + 1, vertIndex);
	pTriList[triIndex + 1].set(vertIndex + 3, vertIndex + 2, vertIndex);

	vertIndex += 4;
	triIndex += 2;

	//
	//right face
	//

	//right face -- top left tri -- top right, top left, bottom left
	//right face -- bottom right tri -- bottom right, top right, bottom left
	pVerts[vertIndex].set(+0.5f, +0.5f, -0.5f, 0.25f, 0.375f, 1, 0, 0);		//back top right
	pVerts[vertIndex + 1].set(+0.5f, +0.5f, +0.5f, 0.5f, 0.375f, 1, 0, 0);		//front top right
	pVerts[vertIndex + 2].set(+0.5f, -0.5f, +0.5f, 0.5f, 0.125f, 1, 0, 0);		//front bottom right
	pVerts[vertIndex + 3].set(+0.5f, -0.5f, -0.5f, 0.25f, 0.125f, 1, 0, 0);		//back bottom right
	pTriList[triIndex].set(vertIndex, vertIndex + 1, vertIndex + 2);
	pTriList[triIndex + 1].set(vertIndex, vertIndex + 2, vertIndex + 3);

	vertIndex += 4;
	triIndex += 2;

	//
	//left face
	//

	//left face -- top left tri -- top right, top left, bottom left
	//left face -- bottom right tri -- bottom right, top right, bottom left
	pVerts[vertIndex].set(-0.5f, +0.5f, +0.5f, 0.5f, 0.625f, -1, 0, 0);		//front top left
	pVerts[vertIndex + 1].set(-0.5f, +0.5f, -0.5f, 0.25f, 0.625f, -1, 0, 0);		//back top left
	pVerts[vertIndex + 2].set(-0.5f, -0.5f, -0.5f, 0.25f, 0.875f, -1, 0, 0);		//back bottom left
	pVerts[vertIndex + 3].set(-0.5f, -0.5f, +0.5f, 0.5f, 0.875f, -1, 0, 0);		//front bottom left
	pTriList[triIndex].set(vertIndex, vertIndex + 1, vertIndex + 2);
	pTriList[triIndex + 1].set(vertIndex, vertIndex + 2, vertIndex + 3);

	vertIndex += 4;
	triIndex += 2;

	//
	//top face
	//

	//top face -- back left tri -- top right, top left, bottom left
	//top face -- front right tri -- bottom right, top right, bottom left
	pVerts[vertIndex].set(+0.5f, +0.5f, -0.5f, 0.5f, 0.625f, 0, 1, 0);		//back top right
	pVerts[vertIndex + 1].set(-0.5f, +0.5f, -0.5f, 0.5f, 0.375f, 0, 1, 0);		//back top left
	pVerts[vertIndex + 2].set(-0.5f, +0.5f, +0.5f, 0.25f, 0.375f, 0, 1, 0);		//front top left
	pVerts[vertIndex + 3].set(+0.5f, +0.5f, +0.5f, 0.25f, 0.625f, 0, 1, 0);		//front top right
	pTriList[triIndex].set(vertIndex, vertIndex + 1, vertIndex + 2);
	pTriList[triIndex + 1].set(vertIndex, vertIndex + 2, vertIndex + 3);

	vertIndex += 4;
	triIndex += 2;

	//
	//bottom face
	//

	//bottom face -- back left tri -- top right, top left, bottom left
	//bottom face -- front right tri -- bottom right, top right, bottom left
	pVerts[vertIndex].set(+0.5f, -0.5f, -0.5f, 0.75f, 0.625f, 0, -1, 0);		//back bottom right
	pVerts[vertIndex + 1].set(-0.5f, -0.5f, -0.5f, 0.75f, 0.375f, 0, -1, 0);		//back bottom left
	pVerts[vertIndex + 2].set(-0.5f, -0.5f, +0.5f, 1.0f, 0.375f, 0, -1, 0);		//front bottom left
	pVerts[vertIndex + 3].set(+0.5f, -0.5f, +0.5f, 1.0f, 0.625f, 0, -1, 0);		//front bottom right
	pTriList[triIndex].set(vertIndex, vertIndex + 3, vertIndex + 2);		//back bottom right, front bottom right, front bottom left
	pTriList[triIndex + 1].set(vertIndex, vertIndex + 2, vertIndex + 1);	//back bottom right, front bottom left, back bottom left

	vertIndex += 4;
	triIndex += 2;
}



void ModelTools::CreateUnitPyramid(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri) {

	nverts = 5;
	pVerts = new StandardVertex[nverts];
	ntri = 6;
	pTriList = new TriangleByIndex[ntri];


	pVerts[0].set(-0.5f, -0.5f, +0.5f, Colors::Black);		//Front left
	pVerts[1].set(-0.5f, -0.5f, -0.5f, Colors::Lime);		//Back Left
	pVerts[2].set(+0.5f, -0.5f, +0.5f, Colors::Yellow);		//Front right
	pVerts[3].set(+0.5f, -0.5f, -0.5f, Colors::Red);		//Back right
	pVerts[4].set(0.0f, +0.5f, +0.0f, Colors::Black);		//top

															// front face
	pTriList[0].set(2, 4, 0);

	// back face
	pTriList[1].set(3, 1, 4);

	// right face
	pTriList[2].set(3, 4, 2);

	// left face
	pTriList[3].set(0, 4, 1);

	// bottom face
	pTriList[4].set(3, 2, 0);
	pTriList[5].set(3, 0, 1);
}

void ModelTools::CreateUnitPyramidRepTexture(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri) {

	nverts = 18;
	pVerts = new StandardVertex[nverts];
	ntri = 6;
	pTriList = new TriangleByIndex[ntri];

	// Setting up faces
	// Forward
	int vertIndex = 0;
	int triIndex = 0;

	//front face -- front right, top, front left

	pVerts[vertIndex].set(+0.5f, -0.5f, +0.5f, 1, 1);		//(u,v) = (1, 1) for bottom right of tri
	pVerts[vertIndex + 1].set(+0.0f, +0.5f, +0.0f, 0.5, 0);		//(u,v) = (0.5, 0) for top center of tri
	pVerts[vertIndex + 2].set(-0.5f, -0.5f, +0.5f, 0, 1);		//(u,v) = (0, 1) for bottom left of tri
	pTriList[triIndex].set(vertIndex, vertIndex + 1, vertIndex + 2);

	UpdateNorm(pVerts[vertIndex].normal, Vect(0.0f, 0.5f, 1.0f));
	UpdateNorm(pVerts[vertIndex + 1].normal, Vect(0.0f, 0.5f, 1.0f));
	UpdateNorm(pVerts[vertIndex + 2].normal, Vect(0.0f, 0.5f, 1.0f));

	vertIndex += 3;
	triIndex++;

	//back face -- back right, back left, top (3, 1, 4)

	pVerts[vertIndex].set(+0.5f, -0.5f, -0.5f, 0, 1);		//(u, v) = (1, 1) for bottom right of tri
	pVerts[vertIndex + 1].set(-0.5f, -0.5f, -0.5f, 1, 1);	//(u, v) = (0, 1) for bottom left of tri
	pVerts[vertIndex + 2].set(+0.0f, +0.5f, +0.0f, 0.5, 0);		//(u,v) = (0.5, 0) for top center of tri
	pTriList[triIndex].set(vertIndex, vertIndex + 1, vertIndex + 2);

	UpdateNorm(pVerts[vertIndex].normal, Vect(0.0f, +0.5f, -1.0f));
	UpdateNorm(pVerts[vertIndex + 1].normal, Vect(0.0f, +0.5f, -1.0f));
	UpdateNorm(pVerts[vertIndex + 2].normal, Vect(0.0f, +0.5f, -1.0f));

	vertIndex += 3;
	triIndex++;

	//right face -- back right, top, front right(3, 4, 2)

	pVerts[vertIndex].set(+0.5f, -0.5f, -0.5f, 1, 1);				//(u, v) = (1, 1) for bottom right of tri
	pVerts[vertIndex + 1].set(+0.0f, +0.5f, +0.0f, 0.5, 0);				//(u,v) = (0.5, 0) for top center of tri
	pVerts[vertIndex + 2].set(+0.5f, -0.5f, +0.5f, 0, 1);					//(u, v) = (0, 1) for bottom left of tri
	pTriList[triIndex].set(vertIndex, vertIndex + 1, vertIndex + 2);

	UpdateNorm(pVerts[vertIndex].normal, Vect(+1.0, +0.5f, 0.0f));
	UpdateNorm(pVerts[vertIndex + 1].normal, Vect(+1.0, +0.5f, 0.0f));
	UpdateNorm(pVerts[vertIndex + 2].normal, Vect(+1.0, +0.5f, 0.0f));

	vertIndex += 3;
	triIndex++;

	//left face -- front left, top, back left (0, 4, 1)

	pVerts[vertIndex].set(-0.5f, -0.5f, +0.5f, 1, 1);				//(u, v) = (1, 1) for bottom right of tri
	pVerts[vertIndex + 1].set(+0.0f, +0.5f, +0.0f, 0.5, 0);				//(u,v) = (0.5, 0) for top center of tri
	pVerts[vertIndex + 2].set(-0.5f, -0.5f, -0.5f, 0, 1);					//(u, v) = (0, 1) for bottom left of tri
	pTriList[triIndex].set(vertIndex, vertIndex + 1, vertIndex + 2);

	UpdateNorm(pVerts[vertIndex].normal, Vect(-1.0, +0.5f, 0.0f));
	UpdateNorm(pVerts[vertIndex + 1].normal, Vect(-1.0, +0.5f, 0.0f));
	UpdateNorm(pVerts[vertIndex + 2].normal, Vect(-1.0, +0.5f, 0.0f));

	vertIndex += 3;
	triIndex++;


	//bottom tri #1 -- back right, front right, front left (3, 2, 0)

	pVerts[vertIndex].set(+0.5f, -0.5f, -0.5f, 1, 1);				//(u, v) = (1, 1) for bottom right of tri
	pVerts[vertIndex + 1].set(+0.5f, -0.5f, +0.5f, 1, 0);				//(u,v) = (0.5, 0) for top center of tri
	pVerts[vertIndex + 2].set(-0.5f, -0.5f, +0.5f, 0, 0);					//(u, v) = (0, 1) for bottom left of tri
	pTriList[triIndex].set(vertIndex, vertIndex + 1, vertIndex + 2);

	UpdateNorm(pVerts[vertIndex].normal, Vect(0.0f, -1.0f, 0.0f));
	UpdateNorm(pVerts[vertIndex + 1].normal, Vect(0.0f, -1.0f, 0.0f));
	UpdateNorm(pVerts[vertIndex + 2].normal, Vect(0.0f, -1.0f, 0.0f));

	vertIndex += 3;
	triIndex++;

	//bottom tri #2 -- back right, front left, back left (3, 0, 1)

	pVerts[vertIndex].set(+0.5f, -0.5f, -0.5f, 1, 1);				//(u, v) = (1, 1) for bottom right of tri
	pVerts[vertIndex + 1].set(-0.5f, -0.5f, +0.5f, 0, 0);				//(u,v) = (0.5, 0) for top center of tri
	pVerts[vertIndex + 2].set(-0.5f, -0.5f, -0.5f, 0, 1);					//(u, v) = (0, 1) for bottom left of tri
	pTriList[triIndex].set(vertIndex, vertIndex + 1, vertIndex + 2);

	UpdateNorm(pVerts[vertIndex].normal, Vect(0.0f, -1.0f, 0.0f));
	UpdateNorm(pVerts[vertIndex + 1].normal, Vect(0.0f, -1.0f, 0.0f));
	UpdateNorm(pVerts[vertIndex + 2].normal, Vect(0.0f, -1.0f, 0.0f));

	vertIndex += 3;
	triIndex++;




}

//void ModelTools::CreateUnitSphere(int vslice, int hslice, StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri) {
//
//	
//	//nverts = vslice * hslice + 2;
//	//pVerts = new StandardVertex[nverts];
//	//ntri = (hslice - 1) * vslice * 2;
//	//pTriList = new TriangleByIndex[ntri];
//
//	//// Setting up faces
//	//// Forward
//	//int vertIndex = 0;
//
//	//int maxRadius = 1;
//	//int radius = 0;
//
//	//float hSliceAngle = 2 * PI / hslice;
//	//float vSliceDist = maxRadius / vslice;
//	//float longitudeAngle = PI / (vslice + 2);
//
//	////top vertex
//	//pVerts[vertIndex++].set(0, maxRadius, 0);
//
//	////calculate vertices
//	//for (int i = 1; i < hslice; i++) {
//
//	//	radius = maxRadius * cos(longitudeAngle * i);
//
//	//	radius = maxRadius;
//
//	//	for (int j = 0; j < vslice; j++) {
//
//	//		float xVal = cosf(hSliceAngle * j) * radius;
//	//		float yVal = i * vSliceDist;
//	//		float zVal = sinf(hSliceAngle * j) * radius;
//
//	//		pVerts[vertIndex++].set(xVal, yVal, zVal);
//	//	}
//	//}
//
//	////bottom vertex
//	//pVerts[nverts - 1].set(0, -maxRadius, 0);
//
//
//
//	////calculate triangles
//	//int triIndex = 0;
//
//	////bottom triangles
//	//vertIndex = 2;														
//	//for (int i = 1; i < vslice; i++) {							
//	//	pTriList[triIndex++].set(vertIndex, vertIndex - 1, 0);
//	//	vertIndex++;
//	//}
//
//	////body triangles
//	//for (int i = 1; i < (hslice - 1); i++) {
//
//	//	for (int j = 0; j < vslice; j++) {
//	//		
//	//		vertIndex = (i * vslice) + j;
//
//	//		pTriList[triIndex++].set(vertIndex, vertIndex + 1, vertIndex + 1 + vslice);
//	//		pTriList[triIndex++].set(vertIndex, vertIndex + 1 + vslice, vertIndex + vslice);
//	//		
//	//		//vertIndex++;
//	//	}
//	//}
//
//	////top triangles
//	//for (int i = 0; i < vslice; i++) {
//	//	pTriList[triIndex++].set(vertIndex, vertIndex + 1, nverts - 1);
//	//	vertIndex++;
//	//}
//
//
//
//
//	//
//
//
// 
//}




//typedef struct {
//	float x;
//	float y;
//	float z;
//}  Point;
//
//float DEGS_TO_RAD = 3.14159f / 180.0f;
//int numVertices = 0;    // Tallies the number of vertex points added.
//
//						//------------------------
//						//-- Prints a sphere as a "standard sphere" triangular mesh with the specified
//						//-- number of latitude (nLatitude) and longitude (nLongitude) lines and
//						//-- writes results to the specified output file (fout).
//
//void printStandardSphere(Point pt, float radius, int nLatitude, int nLongitude, FILE *fout)
//{
//	int p, s, i, j;
//	float x, y, z, out;
//	int nPitch = nLongitude + 1;
//
//	float pitchInc = (180. / (float)nPitch) * DEGS_TO_RAD;
//	float rotInc = (360. / (float)nLatitude) * DEGS_TO_RAD;
//
//	//## PRINT VERTICES:
//
//	fprintf(fout, "v %g %g %g\n", pt.x, pt.y + radius, pt.z);    // Top vertex.
//	fprintf(fout, "v %g %g %g\n", pt.x, pt.y - radius, pt.z);    // Bottom vertex.
//	numVertices = numVertices + 2;
//
//	int fVert = numVertices;    // Record the first vertex index for intermediate vertices.
//	for (p = 1; p<nPitch; p++)     // Generate all "intermediate vertices":
//	{
//		out = radius * sin((float)p * pitchInc);
//		if (out < 0) out = -out;    // abs() command won't work with all compilers
//		y = radius * cos(p * pitchInc);
//		printf("OUT = %g\n", out);    // bottom vertex
//		printf("nPitch = %d\n", nPitch);    // bottom vertex
//		for (s = 0; s<nLatitude; s++)
//		{
//			x = out * cos(s * rotInc);
//			z = out * sin(s * rotInc);
//
//			fprintf(fout, "v %g %g %g\n", x + pt.x, y + pt.y, z + pt.z);
//			numVertices++;
//		}
//	}
//
//	//## PRINT SQUARE FACES BETWEEN INTERMEDIATE POINTS:
//
//	for (p = 1; p<nPitch - 1; p++) {
//		for (s = 0; s<nLatitude; s++) {
//			i = p*nLatitude + s;
//			j = (s == nLatitude - 1) ? i - nLatitude : i;
//			fprintf(fout, "f %d %d %d %d\n",
//				(i + 1 - nLatitude) + fVert, (j + 2 - nLatitude) + fVert, (j + 2) + fVert, (i + 1) + fVert);
//		}
//	}
//
//	//## PRINT TRIANGLE FACES CONNECTING TO TOP AND BOTTOM VERTEX:
//
//	int offLastVerts = fVert + (nLatitude * (nLongitude - 1));
//	for (s = 0; s<nLatitude; s++)
//	{
//		j = (s == nLatitude - 1) ? -1 : s;
//		fprintf(fout, "f %d %d %d\n", fVert - 1, (j + 2) + fVert, (s + 1) + fVert);
//		fprintf(fout, "f %d %d %d\n", fVert, (s + 1) + offLastVerts, (j + 2) + offLastVerts);
//	}
//}






void ModelTools::UpdateNorm(Vect & currentNorm, Vect & addNorm) {

	if (currentNorm.magSqr() == 0)
		currentNorm.set(addNorm);
	else
		currentNorm.set((currentNorm.X() + addNorm.X()) / 2, (currentNorm.Y() + addNorm.Y()) / 2, (currentNorm.Z() + addNorm.Z()) / 2);

}


void ModelTools::UpdateNorm(Vect & currentNorm, Vect addNorm) {

	if (currentNorm.magSqr() == 0)
		currentNorm.set(addNorm);
	else
		currentNorm.set((currentNorm.X() + addNorm.X()) / 2, (currentNorm.Y() + addNorm.Y()) / 2, (currentNorm.Z() + addNorm.Z()) / 2);

}