#pragma
#ifndef MYLIB
#define MYLIB


#include <GL/glut.h>
#include <cmath>
#include<iostream>
#include<vector>
#include"Vertex.h"

namespace gnr{
//START OF gnr NAMESPACE

class MyLib
{
public:
	MyLib();
	~MyLib();

	/* v1 and v2 are parameters and vr is a return value as a result*/
	static void crossProduct(GLfloat v1[3],GLfloat v2[3],GLfloat vr[3]);

	static void normalizeCalculation(GLfloat polygon[][3],GLfloat *normal,GLint *face);

	static void normalizeCalculation3d(GLfloat polygon[][3], GLfloat normal[][3], GLint face[][4],GLint faceSize);


};

//END_OF ml NAMESPACE
}
#endif
