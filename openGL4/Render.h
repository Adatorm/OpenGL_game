#pragma once
#ifndef RENDER_H
#define RENDER_H
#include "GL/glut.h"
#include "Mayuri.h"
#include "Vertex.h"
#include <vector>
#include <fstream>
#include "Mayuri.h"
#include "Prisim.h"
namespace gnr{
	class Render
	{
	public:
		Render();
		void platform();
		void DrawNet(GLfloat size, GLint LinesX, GLint LinesZ);
		void sky(GLfloat s,Vertex v);
		void line(GLfloat width, Vector3d color, Vertex st, Vertex end);
		void groundLine();
		void pyramid(GLfloat x, GLfloat y, GLfloat z, GLfloat volume);
		std::vector<Prisim> tatemono;//buildings
		void initTatemono2(GLint texture, int step, bool wholeTexture);
		void initTatemono(GLint texture);
		~Render();
	};
}//namespace gnr
#endif