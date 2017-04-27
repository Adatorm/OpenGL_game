#include "MyLib.h"
namespace gnr{
//start of gnr namespace


MyLib::MyLib()
{
}


MyLib::~MyLib()
{

}


void MyLib::crossProduct(GLfloat v1[3], GLfloat v2[3], GLfloat vr[3]){
	vr[0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);//i
	vr[1] = (v1[2] * v2[0]) - (v1[0] * v2[2]);//j
	vr[2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);//k
}

void MyLib::normalizeCalculation(GLfloat polygon[][3], GLfloat *normal, GLint *face){
	GLfloat v1[3],v2[3],v3[3];//three vector to calculate normal

	int a1, a2, a3;//polygon points to calculate the normal
	a1 = face[0];
	a2 = face[1];
	a3 = face[2];

	v1[0] = polygon[a1][0];
	v1[1] = polygon[a1][1];
	v1[2] = polygon[a1][2];

	v2[0] = polygon[a2][0];
	v2[1] = polygon[a2][1];
	v1[2] = polygon[a2][2];


	v3[0] = polygon[a3][0];
	v3[1] = polygon[a3][1];
	v3[2] = polygon[a3][2];

	GLfloat a[3], b[3];//create two new vector with three points
	a[0] = v1[0] - v2[0];
	a[1] = v1[1] - v2[1];
	a[2] = v1[2] - v2[2];

	b[0] = v1[0] - v3[0];
	b[1] = v1[1] - v3[1];
	b[2] = v1[2] - v3[2];

	//cros product
	crossProduct(a, b, normal);

	GLfloat magnitude = normal[0] * normal[0] + normal[1] * normal[1] + normal[2] * normal[2];
	magnitude = sqrt(magnitude);
	if (magnitude==0)
	{ 
		std::cerr << "division by zero in normal calculation" << std::endl;
	}
	else
	{
		normal[0] = normal[0] / magnitude;
		normal[1] = normal[1] / magnitude;
		normal[2] = normal[2] / magnitude;
	}
	
}

void MyLib::normalizeCalculation3d(GLfloat polygon[][3], GLfloat normal[][3], GLint face[][4] , GLint faceSize){
	for (int i = 0; i < faceSize; ++i)
	{
		normalizeCalculation(polygon, normal[i],face[i]);
	}
}


//end of ml namespace
}