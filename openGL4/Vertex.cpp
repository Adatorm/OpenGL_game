#include"Vertex.h"

namespace gnr{
	Vertex::Vertex(){
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		u = 0.0f;
		v = 0.0f;
	}

	Vertex::Vertex(GLfloat x_i, GLfloat y_i, GLfloat z_i){
		x = x_i;
		y = y_i;
		z = z_i;
		u = 0.0f;
		v = 0.0f;
	}

	Vertex::Vertex(GLfloat x_i, GLfloat y_i, GLfloat z_i, GLfloat u_i, GLfloat v_i){
		x = x_i;
		y = y_i;
		z = z_i;
		u = u_i;
		v = v_i;
	}
	// + operator
	Vertex Vertex::operator+(Vertex &ver){
		return Vertex(x + ver.x, y + ver.y, z + ver.z,u,v);
	}

	Vertex Vertex::operator+(Vector3d &vec)
	{
		return Vertex(x + vec.x, y + vec.y, z + vec.z,u,v);
	}

	// - operator
	Vertex Vertex::operator-(Vertex &ver){
		return Vertex(x - ver.x, y - ver.y, z - ver.z,u,v);
	}


	GLfloat & Vertex::operator[](int index){
		if (index == 0)
		{
			return x;
		}
		else if(index==1){
			return y;
		}
		else{
			return z;
		}
	}

	void mPolygon::print(){
		std::cerr << "polygon" << std::endl;
		for (int i = 0; i < size; i++)
		{
			std::cerr << "point:" << i << " x:" << polygon[i].x << " y:" << polygon[i].y << " z:" << polygon[i].z << std::endl;

		} 
		std::cerr << std::endl;
	}

	Vertex::~Vertex(){
	}

	Vertex & mPolygon::operator[](int index){
		return polygon[index];
	}

}// end of namespace