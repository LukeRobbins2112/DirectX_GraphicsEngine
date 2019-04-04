// ModelTools
// Support tools to compute bounding volumes on models
// Ported/adapted from Keenan's FBX Converter code

#ifndef _ModelTools
#define _ModelTools

#include "Vect.h"
#include <d3d11.h>
#include "d3dUtil.h"
#include <math.h>


struct StandardVertex;
struct TriangleByIndex;

class ModelTools
{

public:
	static void CreateUnitBox(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri);
	static void CreateUnitBoxRepTexture(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri);
	static void CreateUnitBoxSixFaceTexture(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri);

	static void CreateUnitPyramid(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri);
	static void CreateUnitPyramidRepTexture(StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri);

	//static void CreateUnitSphere(int vslice, int hslice, StandardVertex *&pVerts, int& nverts, TriangleByIndex *&pTriList, int& ntri);

	//private method for getting average of normal
	static void UpdateNorm(Vect & currentNorm, Vect & addNorm);
	static void UpdateNorm(Vect & currentNorm, Vect addNorm);


	
};

static const double PI = 3.1415926;


#endif _ModelTools