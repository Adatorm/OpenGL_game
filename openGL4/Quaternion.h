#pragma once
#ifndef QUATERNION_H
#define QUATERNION_H

#include <GL/glut.h>
#include "Vertex.h"
namespace gnr{
	class Quaternion
	{
	public:
		Quaternion();
		Quaternion(GLfloat w_, GLfloat x_, GLfloat y_, GLfloat z_) :w(w_), v(x_, y_,z_){}
		Quaternion(GLfloat w_,Vector3d v_):w(w_),v(v_){}
		GLfloat w;
		Vector3d v;

		Quaternion operator *(Quaternion q){
			Quaternion result;
			result.w = w*q.w - v.x*q.v.x - v.y - q.v.y - v.z*q.v.z;
			result.v.x = w*q.v.x + v.x*q.w + v.y*q.v.z - v.z*q.v.y;
			result.v.y = w*q.v.y + v.y*q.w + v.z*q.v.x - v.x*q.v.z;
			result.v.z = w*q.v.z + v.z*q.w + v.x*q.v.y - v.y*q.v.x;
			return result;
		}
		~Quaternion();
	};

}
#endif
