#pragma
#ifndef PLANE_H
#define PLANE_H
#include <iostream>
#include "Shape.h"
#include "Vector3d.h"
#include "Vertex.h"
#include "MyLib.h"
namespace gnr{

class Plane : public Shape
{
public :
	Plane();
	void draw(GLint a);
	void draw();
	static void drawPlaneMultiple(mPolygon polygon, Vector3d &normal, int step, GLint texture, bool wholeTexture);// draw plane with given corner
	static void drawPlane2(mPolygon &vertexes, Vector3d &normal);// draw a plane
	void drawPlane(mPolygon &p, GLint texture);
	~Plane();
	Plane(GLfloat x, GLfloat y, GLfloat z, GLfloat length,GLfloat width,Vector3d &dir);
	Vector3d direction;// plane dir,normal
	GLfloat planelength;
	GLfloat planewidth;
};

}//namespace gnr
#endif