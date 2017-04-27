#pragma once
#ifndef PRISIM_H
#define PRISIM_H
#include "Cube.h"
#include "GL/glut.h"
#include "Vertex.h"
#include "Plane.h"
namespace gnr{
class Prisim : public Cube
{
public:
	Prisim();
	Prisim(GLfloat x, GLfloat y, GLfloat z, GLfloat lengthh, GLfloat widthh,GLfloat heightt);
	~Prisim();
	GLfloat length;
	GLfloat width;
	GLfloat height;

	void draw();
	void draw(GLint texture);
	void draw2(GLint texture, int step, bool wholeTexture);
	void calculateVertex();
};
}
#endif