#pragma once
#ifndef VERTEX_H
#define VERTEX_H
#include <cmath>
#include <GL/glut.h>
#include "Vector3d.h"
#include <iostream>
namespace gnr{
	class Vector3d;

	class Vertex
	{
	public:
		Vertex();
		Vertex(GLfloat x_i, GLfloat y_i, GLfloat z_i);

		Vertex(GLfloat x_i, GLfloat y_i, GLfloat z_i, GLfloat u_i,GLfloat v_i);

		// + operator
		Vertex operator+(Vertex &v);

		Vertex operator+(Vector3d &vec);

		// - operator
		Vertex operator-(Vertex &v);

		GLfloat & operator[](int index);

		

		GLfloat x, y, z;//coordinates
		GLfloat u, v; //texture coordinates

		~Vertex();
	};

	//triangle
	class Triangle{
	public:
		Vertex vertex[3];
	};

	class mPolygon{
	public:
		Vertex * polygon;
		int size;
		bool isAllocated;
		mPolygon(){
			polygon = nullptr;
			size = 0;
			isAllocated = false;
		}
		mPolygon(int size){
			polygon = new Vertex[size];
			this->size = size;
			isAllocated = true;
		}
		mPolygon(const mPolygon & copy){
			size = copy.size;
			polygon = new Vertex[size];
			isAllocated = true;
			for (int i = 0; i < size; i++)
			{
				polygon[i] = copy.polygon[i];
			}
		}

		Vertex & operator[](int index);
		void print();
		~mPolygon(){
			if (isAllocated)
			{
				delete[] polygon;
			}
		}
		
	};

	class Quad{
	public:
		Vertex quad[4];
	};

	class Normal{
	public:
		Vertex normal;
	};

	//sector
	class Sector{
	public:
		int size;
		mPolygon *polygon;
	};



	class Vector3d
	{
	public:
		//default constructor zero vector
		Vector3d();
		//3 paremeter constructor
		Vector3d(GLfloat x_i, GLfloat y_i, GLfloat z_i);

		Vector3d(Vertex &v);

		//variables
		GLfloat x;//x coordinate
		GLfloat y;//y coordinate
		GLfloat z;//z coordinate



		Vector3d operator+ (Vector3d v);

		Vector3d operator- (Vector3d v);

		//multiple with float
		Vector3d operator* (float f);

		//dot product
		float operator* (Vector3d v);

		//cross product
		static Vector3d crossProduct(Vector3d &v1, Vector3d &v2);

		//get length of vector
		GLfloat getMagnitude();

		//normalize vector
		Vector3d normalize();

		// calculate normals
		static void normalizeCalculater(mPolygon &poly, Vector3d &normal);

		static Vector3d normalizeCalculater(mPolygon &poly);


		~Vector3d(){}
	};

	
}
#endif
