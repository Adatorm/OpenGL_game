#pragma
#ifndef SHAPE_H
#define SHAPE_H
#include <GL/glut.h>
#define POLYGON_UNIT 0.5
namespace gnr{

class Shape
{
public:

	//default shape coordinate-> 0,0,0
	Shape() :x(0), y(0), z(0)
	{

	}
	Shape(GLfloat x, GLfloat y, GLfloat z) :x(x), y(y), z(z)
	{

	}

	void rotate(){
		checkAngler();
		glRotatef(angler,xr, yr, zr );
	}

	//check rotation
	void checkAngler(){
		if (angler < -360.0)
			angler += 360.0;
		if (angler > 360.0)
			angler -= 360.0;
	}

	virtual void draw() = 0;//draw function

	virtual ~Shape(){}//destructor

	GLfloat x;//x coordinate
	GLfloat y;//y coordinate
	GLfloat z;//z coordinate 

	GLfloat xr=0;//x rotate
	GLfloat yr=0;//y rotate
	GLfloat zr=0;//z rotate
	GLfloat angler = 0;//z rotate
};

}
#endif