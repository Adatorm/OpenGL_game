#include "Prisim.h"

namespace gnr{
	Prisim::Prisim()
	{

	}
	Prisim::Prisim(GLfloat x, GLfloat y, GLfloat z, GLfloat lengthh, GLfloat widthh, GLfloat heightt) :Cube(x, y, z){
		length = lengthh;
		width = widthh;
		height = heightt;
		calculateVertex();
	}

	void Prisim::calculateVertex(){
		v[0][0] = v[1][0] = v[2][0] = v[3][0] = x + width / 2.0f;//+x
		v[3][1] = v[2][1] = v[5][1] = v[4][1] = y + height / 2.0f;//+y
		v[2][2] = v[1][2] = v[6][2] = v[5][2] = z + length / 2.0f;//+z
		v[4][0] = v[5][0] = v[6][0] = v[7][0] = x - width / 2.0f;//-x
		v[1][1] = v[0][1] = v[7][1] = v[6][1] = y - height / 2.0f;//-y
		v[0][2] = v[7][2] = v[4][2] = v[3][2] = z - length / 2.0f;//-z

	}

	void Prisim::draw(){
		int i;

		gnr::MyLib::normalizeCalculation3d(v, n, faces, 6);
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

	void Prisim::draw(GLint texture){
		int i;

		gnr::MyLib::normalizeCalculation3d(v, n, faces, 6);

		for (i = 0; i < 6; i++) {
			glBindTexture(GL_TEXTURE_2D, texture);
			glBegin(GL_QUADS);
			glNormal3fv(&n[i][0]);
			glTexCoord2f(0.0f, 0.0f); glVertex3fv(&v[faces[i][0]][0]);
			glTexCoord2f(1.0f, 0.0f); glVertex3fv(&v[faces[i][1]][0]);
			glTexCoord2f(1.0f, 1.0f); glVertex3fv(&v[faces[i][2]][0]);
			glTexCoord2f(0.0f, 1.0f); glVertex3fv(&v[faces[i][3]][0]);
			glEnd();
		}
	}

	void Prisim::draw2(GLint texture,int step,bool wholeTexture){
		int i;
		mPolygon p(4);
		Vector3d nr;
		
		for (i = 0; i < 6; i++) {
			
			for (int t = 0; t < 4; t++)
			{
				p[t].x = v[faces[i][t]][0];
				p[t].y = v[faces[i][t]][1];
				p[t].z = v[faces[i][t]][2];
			}
			Plane::drawPlaneMultiple(p, nr, step, texture, wholeTexture);
		}
	}
	Prisim::~Prisim()
	{
	}

}//namespace gnr