
#include "Cube.h"

namespace gnr{
GLint Cube::faces[6][4]= {  /* Vertex indices for the 6 faces of a cube. */
	{ 6, 1, 2, 5 }, { 1, 0, 3, 2 }, { 0, 7, 4, 3 },
	{ 7, 6, 5, 4 }, {5, 2, 3, 4 }, { 1, 6, 7, 0 } };

Cube::Cube() :Shape(),size(1)
{
	calculateVertex();
}

Cube::Cube(GLfloat x, GLfloat y, GLfloat z, GLfloat size) : Shape(x, y, z), size(size)
{
	calculateVertex();
}


Cube::~Cube()
{

}

void Cube::calculateVertex(){
	v[0][0] = v[1][0] = v[2][0] = v[3][0] = x+size/2.0f;//+x
	v[3][1] = v[2][1] = v[5][1] = v[4][1] = y+size/2.0f;//+y
	v[2][2] = v[1][2] = v[6][2] = v[5][2] = z+size/2.0f;//+z
	v[4][0] = v[5][0] = v[6][0] = v[7][0] = x - size / 2.0f;//-x
	v[1][1] = v[0][1] = v[7][1] = v[6][1] = y - size / 2.0f;//-y
	v[0][2] = v[7][2] = v[4][2] = v[3][2] = z - size / 2.0f;//-z
}

void Cube::draw(){
	int i;

	gnr::MyLib::normalizeCalculation3d(v,n,faces,6);
	for (i = 0; i < 6; i++) {
		glBegin(GL_QUADS);
		glNormal3fv(&n[i][0]);
		glVertex3fv(&v[faces[i][0]][0]);
		glVertex3fv(&v[faces[i][1]][0]);
		glVertex3fv(&v[faces[i][2]][0]);
		glVertex3fv(&v[faces[i][3]][0]);
		glEnd();
	}
}

void Cube::printVertex(){

	for (int i = 0; i < 8; ++i)
	{
		std::cout << i << "->" << " x:" << v[i][0] << " y:" << v[i][1] << " z:" << v[i][2] << std::endl;
	}
}

}