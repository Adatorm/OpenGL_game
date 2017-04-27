#pragma once
#ifndef CAMERA_H
#define CAMERA_H


#include <iostream>
#include <cmath>
#include <GL/glut.h>
#include "Vertex.h"
#include <glm/glm.hpp>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/gtx/quaternion.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/gtc/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale, glm::perspective

#ifndef M_PI//pi value definition
#define M_PI 3.1415926535897932384626433832795
#endif
#ifndef M_PI180
#define  M_PI180 (M_PI/180.0f)
#endif

namespace gnr{
	//start of ml namespace
	class Camera
	{
	public:
		Camera();//default construction
		Camera(GLfloat camx, GLfloat camy, GLfloat camz);//position constructor
		void render();// gl function calls ps:before call this function, call glLoadIdentity.
		void move(Vector3d direction);
		void rotateX(GLfloat angle);
		void rotateXY(GLfloat anglex, GLfloat angley);
		void rotateXY2(GLfloat anglex, GLfloat angley);
		void rotateY(GLfloat angle);
		void rotateZ(GLfloat angle);
		void setScreenMidPoint(int x, int y);

		void moveForward(GLfloat distance); // move camera to forward
		void moveUpward(GLfloat distance); //  move camera to upward
		void StrafeRight(GLfloat distance);// move camera without rotating
		void gimbalLock();//lock camera to prevent unwanted roll

		float keyboardVelocity;//movement velocity, our speed
		float mouseVelocity;//cursor sensitivity

		int midX;//screen midpoint
		int midY;//screen midpoint
		bool mouseWarp;// if mouse set with center of screen coordinates
		int mouseX;//last mouse x coordinate
		int mouseY;// last mouse y coordinate
		void walk();

		~Camera();
	
		Vector3d position; //camera position
		Vector3d viewDir; //camera view direction
		Vector3d rightVector;// camera right vector
		Vector3d upVector; // camera up vector

		bool keyboard[256];//keyboard array,hold
		float deltaTime;
		int oldTime;
		int nbFrames;
		void lastTime();
	private:
		//save rotation
		GLfloat rotatedX, rotatedY, rotatedZ;
	};
}//end of ml namespace
#endif