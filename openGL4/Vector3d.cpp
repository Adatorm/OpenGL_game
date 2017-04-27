#include "Vertex.h"

namespace gnr{

	//default constructor zero vector
	Vector3d::Vector3d(){
		x = 0;
		y = 0;
		z = 0;
	}
	//3 paremeter constructor
	Vector3d::Vector3d(GLfloat x_i, GLfloat y_i, GLfloat z_i){
		x = x_i;
		y = y_i;
		z = z_i;
	}

	Vector3d::Vector3d(Vertex &v) :x(v.x), y(v.y), z(v.z)
	{

	}

	Vector3d Vector3d::operator+ (Vector3d v){
		Vector3d result;
		result.x = x + v.x;
		result.y = y + v.y;
		result.z = z + v.z;
		return result;
	}


	Vector3d Vector3d::operator- (Vector3d v){
		Vector3d result;
		result.x = x - v.x;
		result.y = y - v.y;
		result.z = z - v.z;
		return result;
	}

	//multiple with float
	Vector3d Vector3d::operator* (float f){
		Vector3d result;
		result.x = x * f;
		result.y = y * f;
		result.z = z * f;
		return result;
	}

	//dot product
	float Vector3d::operator* (Vector3d v){
		return x*v.x + y*v.y + z*v.z;
	}

	//cross product
	Vector3d Vector3d::crossProduct(Vector3d &v1, Vector3d &v2)
	{
		Vector3d result;
		result.x = v1.y*v2.z - v1.z*v2.y;
		result.y = v1.z*v2.x - v1.x*v2.z;
		result.z = v1.x*v2.y - v1.y*v2.x;
		return result;
	}

	//get length of vector
	GLfloat Vector3d::getMagnitude(){
		return (GLfloat)(sqrt(x*x + y*y + z*z));
	}

	//normalize vector
	Vector3d Vector3d::normalize()
	{
		Vector3d normal;
		float length = getMagnitude();
		if (length == 0.0f)
			return normal;//sends zero vector which has not filled yet
		normal.x = x / length;
		normal.y = y / length;
		normal.z = z / length;
		return normal;
	}
	void Vector3d::normalizeCalculater(mPolygon &poly, Vector3d &normal){
		// create two new vector with the given polygon points
		Vector3d v1(poly.polygon[0] - poly.polygon[1]);
		Vector3d v2(poly.polygon[0] - poly.polygon[3]);

		// cross product and normalization on normal vector and return it with call by referance 
		normal = Vector3d::crossProduct(v1, v2).normalize();

	}
	Vector3d Vector3d::normalizeCalculater(mPolygon &poly){
		// create two new vector with the given polygon points
		Vector3d v1(poly.polygon[0] - poly.polygon[1]);
		Vector3d v2(poly.polygon[0] - poly.polygon[3]);

		//cross product and normalization on normal vector
		Vector3d normal(Vector3d::crossProduct(v1, v2).normalize());

		// return normal vector
		return normal;
	}

}