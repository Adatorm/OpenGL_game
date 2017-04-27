
#include "Camera.h"
using namespace std;
namespace gnr{
	//start of gnr namespace

	//default constructor
	Camera::Camera(){
		position = Vector3d(0.0, 0.0, 0.0);
		viewDir = Vector3d(0.0, 0.0, -1.0);
		rightVector = Vector3d(1.0, 0.0, 0.0);
		upVector = Vector3d(0.0, 1.0, 0.0);

		rotatedX = rotatedY = rotatedZ = 0.0;
		keyboardVelocity = 1.0f;
		mouseVelocity = 1.0f;
		midX = 0;
		midY = 0;
		mouseWarp = false;
		mouseX = 0;
		mouseY = 0;
		
		for (int i = 0; i < 255; ++i)
		{
			keyboard[i] = false;//init button activity
		}
		oldTime = glutGet(GLUT_ELAPSED_TIME);
		//oldTime = 0;//delta time
		nbFrames = 0;//fps counter
	}

	Camera::Camera(GLfloat camx, GLfloat camy, GLfloat camz){
		position = Vector3d(camx, camy, camz);
		viewDir = Vector3d(0.0, 0.0, -1.0);
		rightVector = Vector3d(1.0, 0.0, 0.0);
		upVector = Vector3d(0.0, 1.0, 0.0);

		rotatedX = rotatedY = rotatedZ = 0.0;
		keyboardVelocity = 1.0f;
		mouseVelocity = 1.0f;
		midX = 0;
		midY = 0;
		mouseWarp = false;
		mouseX = 0;
		mouseY = 0;

		for (int i = 0; i < 255; ++i)
		{
			keyboard[i] = false;//init button activity
		}
		oldTime = glutGet(GLUT_ELAPSED_TIME);
		//oldTime = 0;//delta time
		nbFrames = 0;//fps counter
	}

	//move camera
	void Camera::move(Vector3d direction){
		position = position + direction;
	}

	//rotate camera x
	void Camera::rotateX(GLfloat angle){
		rotatedX += angle;
		//rotate viewdir around right vector
		viewDir = ((viewDir*cos(angle*(M_PI / 180.0f))) + (upVector*sin(angle*(M_PI / 180.0f)))).normalize();
		//cerr << rightVector.x << " " << rightVector.y << " " << rightVector.z << " roz:" << rotatedZ << endl;
		//new upvector
		upVector = (Vector3d::crossProduct(viewDir, rightVector)*-1).normalize();
	}

	//rotate camera xy
	void Camera::rotateXY(GLfloat anglex, GLfloat angley){
		rotatedX += anglex;
		rotatedY += angley;

		//calculate upVector
		
		upVector = ((upVector*cos(angley*(M_PI / 180.0f))) - (viewDir*sin(angley*(M_PI / 180.0f)))).normalize();
		//calculate right vector
		rightVector = ((rightVector*cos(anglex*(M_PI / 180.0f))) +(viewDir*sin(anglex*(M_PI / 180.0f)))).normalize();

		viewDir = Vector3d::crossProduct(upVector, rightVector).normalize();

		cerr << "upvect x" << upVector.x << " " << upVector.y << " " << upVector.z << endl;
	}


	//rotate camera y
	void Camera::rotateY(GLfloat angle){
		rotatedY += angle;

		//rotate viewdir around up vector
		viewDir = (((viewDir*cos(angle*(M_PI / 180.0f))) - (rightVector*sin(angle*(M_PI / 180.0f)))).normalize());

		//new right vector
		rightVector = Vector3d::crossProduct(viewDir, upVector);
	}

	//rotate camera z
	void Camera::rotateZ(GLfloat angle){
		rotatedZ += angle;

		//rotate viewdir around right vector
		rightVector = ((rightVector*cos(angle*(M_PI / 180.0f))) + (upVector*sin(angle*(M_PI / 180.0f)))).normalize();

		//new up vector
		upVector = Vector3d::crossProduct(viewDir, rightVector)*-1;
	}

	//if screen changed or sometime id we need it :3
	void Camera::setScreenMidPoint(int x, int y){
		midX = x;
		midY = y;
	}

	//######################################## 
	void Camera::render(){
		//camera  look point 
		Vector3d viewPoint = position + viewDir;
		//gluLookAt call
		gluLookAt(position.x, position.y, position.z,
			viewPoint.x, viewPoint.y, viewPoint.z,
			0, 1, 0);

	}

	void Camera::moveForward(GLfloat distance){
		position = position + (viewDir*-distance);
	}

	void Camera::moveUpward(GLfloat distance){
		position = position + (upVector*distance);
	}

	void Camera::StrafeRight(GLfloat distance)
	{
		position = position + (rightVector*distance);
	}

	void Camera::gimbalLock(){
		if (rotatedX > 90)
		{
			rotatedX = 90.0;
		}
		if (rotatedX < -90)
		{
			rotatedX = -90.0;
		}
		if (rotatedY < 0.0)
		{
			rotatedY += 360.0;
		}
		if (rotatedY > 360.0)
		{
			rotatedY -= 360.0;
		}

	}

	void Camera::walk(){
		if (position.y < 1.5f)
		{
			position.y = 1.5f;
		}
	}
	void Camera::lastTime(){
		int t;
		/* Delta time in seconds. */
		float dt;
		t = glutGet(GLUT_ELAPSED_TIME);
		dt =(float)( (t - oldTime) / 1000.0);
		oldTime = t;
	}

	Camera::~Camera()
	{
	}

	void Camera::rotateXY2(GLfloat anglex, GLfloat angley){
		rotatedX += anglex;
		rotatedY += angley;

		gimbalLock();

		//calculate upVector
		upVector = ((upVector*cos(angley*(M_PI / 180.0f))) - (viewDir*sin(angley*(M_PI / 180.0f)))).normalize();
		//calculate right vector
		rightVector = ((rightVector*cos(anglex*(M_PI / 180.0f))) + (viewDir*sin(anglex*(M_PI / 180.0f)))).normalize();

		viewDir = Vector3d::crossProduct(upVector, rightVector).normalize();

		cerr << "upvect x" << upVector.x << " " << upVector.y << " " << upVector.z << endl;
	}


}//end of gnr namespace