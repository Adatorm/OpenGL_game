#include "Render.h"
using namespace std;
namespace gnr{
	Render::Render()
	{
	}
	void Render::platform(){

	}

	void Render::DrawNet(GLfloat size, GLint LinesX, GLint LinesZ)
	{
		glBegin(GL_LINES);
		for (int xc = 0; xc < LinesX; xc++)
		{
			glVertex3f(-size / 2.0f + xc / (GLfloat)(LinesX - 1)*size,
				0.0f,
				size / 2.0f);
			glVertex3f(-size / 2.0f + xc / (GLfloat)(LinesX - 1)*size,
				0.0f,
				size / -2.0f);
		}
		for (int zc = 0; zc < LinesX; zc++)
		{
			glVertex3f(size / 2.0f,
				0.0,
				-size / 2.0f + zc / (GLfloat)(LinesZ - 1)*size);
			glVertex3f(size / -2.0f,
				0.0,
				-size / 2.0f + zc / (GLfloat)(LinesZ - 1)*size);
		}
		glEnd();
	}

	void Render::sky(GLfloat s,Vertex v){
		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_QUADS);
		glVertex3f(-s + v.x, 0.0f + v.y, -s + v.z);
		glVertex3f(s + v.x, 0.0f + v.y, -s + v.z);
		glVertex3f(s + v.x, s + v.y, -s + v.z);
		glVertex3f(-s + v.x, s + v.y, -s + v.z);
		glEnd();

		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_QUADS);
		glVertex3f(s + v.x, 0.0f + v.y, -s + v.z);
		glVertex3f(s + v.x, 0.0f + v.y, s + v.z);
		glVertex3f(s + v.x, s + v.y, s + v.z);
		glVertex3f(s + v.x, s + v.y, -s + v.z);
		glEnd();

		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_QUADS);
		glVertex3f(s + v.x, 0.0f + v.y, s + v.z);
		glVertex3f(-s + v.x, 0.0f + v.y, s + v.z);
		glVertex3f(-s + v.x, s + v.y, s + v.z);
		glVertex3f(s + v.x, s + v.y, s + v.z);
		glEnd();

		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_QUADS);
		glVertex3f(-s + v.x, 0.0f + v.y, s + v.z);
		glVertex3f(-s + v.x, 0.0f + v.y, -s + v.z);
		glVertex3f(-s + v.x, s + v.y, -s + v.z);
		glVertex3f(-s + v.x, s + v.y, s + v.z);
		glEnd();

		glColor3f(0.0f, 0.0f, 1.0f);
		glBegin(GL_QUADS);
		glVertex3f(-s + v.x, s + v.y, -s + v.z);
		glVertex3f(s + v.x, s + v.y, -s + v.z);
		glVertex3f(s + v.x, s + v.y, s + v.z);
		glVertex3f(-s + v.x, s + v.y, s + v.z);
		glEnd();

	}

	void Render::line(GLfloat width,Vector3d color,Vertex st,Vertex end){
		glLineWidth(width);
		glColor3f(color.x, color.y, color.z);
		glBegin(GL_LINES);
		glVertex3f(st.x, st.y, st.z);
		glVertex3f(end.x, end.y, end.z);
		glEnd();
	}

	void Render::groundLine(){
		Vector3d v(0.0f, 1.0f, 1.0f);
		for (int i = -256; i < 256; i+=2)
		{
			line(1.0f, v, Vertex((GLfloat)i, 0.0f, 256.0f), Vertex((GLfloat)i, 0.0f, -256.0f));
		}
		for (int i = -256; i < 256; i += 2)
		{
			line(1.0f, v, Vertex(-256.0f, 0.0f, (GLfloat)i), Vertex(256.0f, 0.0f, (GLfloat)i));
		}

	}
	void Render::pyramid(GLfloat x, GLfloat y, GLfloat z,GLfloat volume){
		glPushMatrix();
		glTranslatef(x, y, x);
		glBegin(GL_TRIANGLES);
		glColor3f(volume, 0.0f, 0.0f); glVertex3f(0.0f, volume, 0.0f);
		glColor3f(0.0f, volume, 0.0f); glVertex3f(-volume, -volume, 1.0f);
		glColor3f(0.0f, 0.0f, volume); glVertex3f(volume, -volume, volume);

		glColor3f(volume, 0.0f, 0.0f); glVertex3f(0.0f, volume, 0.0f);
		glColor3f(0.0f, volume, 0.0f); glVertex3f(-volume, -volume, volume);
		glColor3f(0.0f, 0.0f, volume); glVertex3f(0.0f, -volume, -volume);

		glColor3f(volume, 0.0f, 0.0f); glVertex3f(0.0f, volume, 0.0f);
		glColor3f(0.0f, volume, 0.0f); glVertex3f(0.0f, -volume, -volume);
		glColor3f(0.0f, 0.0f, volume); glVertex3f(volume, -volume, volume);


		glColor3f(volume, 0.0f, 0.0f); glVertex3f(-volume, -volume, volume);
		glColor3f(0.0f, volume, 0.0f); glVertex3f(0.0f, -volume, -volume);
		glColor3f(0.0f, 0.0f, volume); glVertex3f(volume, -volume, volume);

		glEnd();

		glPopMatrix();
	}

	void Render::initTatemono(GLint texture){
		ifstream i;
		i.open("o.txt");
		int array[6];
		for (int c = 0; c < 35; c++)
		{
			for (int d = 0; d < 6; d++)
			{
				i >> array[d];
			}
			Prisim p((GLfloat)array[0], (GLfloat)array[4] / 2.0f, (GLfloat)array[1], (GLfloat)array[2], (GLfloat)array[3], (GLfloat)array[4]);
			p.draw(texture);
		}
		i.close();
	}

	void Render::initTatemono2(GLint texture,int step,bool wholeTexture){
		ifstream i;
		i.open("o.txt");
		int array[6];
		for (int c = 0; c < 35; c++)
		{
			for (int d = 0; d < 6; d++)
			{
				i >> array[d];
			}
			Prisim p((GLfloat)array[0], (GLfloat)array[4] / 2.0f, (GLfloat)array[1], (GLfloat)array[2], (GLfloat)array[3], (GLfloat)array[4]);
			p.draw2(texture,step,wholeTexture);
		}
		i.close();
	}

	Render::~Render()
	{
	}
}//namespace gnr