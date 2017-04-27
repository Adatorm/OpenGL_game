#pragma
#ifndef CUBE
#define CUBE

#include "Shape.h"
#include "MyLib.h"
namespace gnr{

class Cube: public Shape 
{
public:

	//default x,y,z (0,0,0) default size=1
	Cube();//default constructor

	//x,y,z coorinate, size-> length of edges of cube(default 1)
	Cube(GLfloat x, GLfloat y, GLfloat z, GLfloat size = 1);//coordinate constructor
	
	virtual void draw();

	void calculateVertex();

	virtual ~Cube();

	GLfloat size;

	//0->5 == +x,+y,+z,-x,-y,-z
	static GLint faces[6][4];//faces

	GLfloat n[6][3];//normal

	GLfloat v[8][3];//vertex

	void printVertex();

};

}
#endif