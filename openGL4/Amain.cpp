/* Copyright (c) Mark J. Kilgard, 1997. */

/* This program is freely distributable without licensing fees
and is provided without guarantee or warrantee expressed or
implied. This program is -not- in the public domain. */

/* This program was requested by Patrick Earl; hopefully someone else
will write the equivalent Direct3D immediate mode program. */

#include <GL/glut.h>	
#include <iostream>
#include <cstdio>
#include "SOIL.h"
#include "Mayuri.h"
#include <csignal>
#define SPEED 5.0f
#define LOGFILE "mayuri.log"
#define LOGFILE2 "runningtime.log"
#define STEPTIME 1000

using namespace std;
using namespace gnr;

GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };  /*diffuse light. */
GLfloat light_position[] = { 1.0, 10.0, -90.0, 1.0 };  /* Infinite light location. */

GLfloat light_amb2[] = { 1.0, 1.0, 1.0, 1.0 };  /* light. */
GLfloat light_position2[] = { 0.0, 100.0, 0.0, 1.0 };  /* Infinite light location. */
GLfloat n[6][3] = {  /* Normals for the 6 faces of a cube. */
	{ -1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 1.0, 0.0, 0.0 },
	{ 0.0, -1.0, 0.0 }, { 0.0, 0.0, 1.0 }, { 0.0, 0.0, -1.0 } };
GLint faces[6][4] = {  /* Vertex indices for the 6 faces of a cube. */
	{ 0, 1, 2, 3 }, { 3, 2, 6, 7 }, { 7, 6, 5, 4 },
	{ 4, 5, 1, 0 }, { 5, 6, 2, 1 }, { 7, 4, 0, 3 } };
GLfloat v[8][3];  /* Will be filled in with X,Y,Z vertexes. */

GLfloat fl = 60.0;

Cube c(0,0,-5);
Plane zemin(0.0f, -0.001f, 0.001f, 1282, 1573, Vector3d(0.0f, 1.0f, 0.0f));

mPolygon zemn(4);
Camera camera(0.0f,1.5f,0.0f);
Render render;
int x = 0;
int y = 0;//mouse old coordinate
ofstream o,runningLog;//log file
GLuint	myTexture,mugiwara,grass;

GLuint terrarianList;
GLuint tatemono;

GLfloat old_time;

Prisim p(5.0f, 5.0f, 5.0f, 2.0f, 3.0f, 10.0f);

mPolygon ggg(4);

void keyboardOperations();


void buildList()
{
	terrarianList = glGenLists(1);
	
	glNewList(terrarianList, GL_COMPILE);
	Plane::drawPlaneMultiple(zemn, Vector3d(0.0f, 1.0f, 0.0f), 50, grass, false);
	glEndList();

	tatemono = glGenLists(1);
	glNewList(tatemono, GL_COMPILE);
	render.initTatemono2(mugiwara, 10, true);
	glEndList();
}

int LoadGLTextures(GLuint &texture,const char * filename)                                    // Load Bitmaps And Convert To Textures
{
	/* load an image file directly as a new OpenGL texture */
	texture = SOIL_load_OGL_texture
		(
		filename,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

	if (texture == 0)
	{
		o << "SOIL loading error:" << SOIL_last_result() << endl;
		return false;
	}
		


	// Typical Texture Generation Using Data From The Bitmap
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	return true;                                        // Return Success
}


void logfile(){
	o.open(LOGFILE);
	runningLog.open(LOGFILE2);
}


void drawBox(void)
{
	int i;

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


void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	camera.lastTime();
	//cerr << "time: " << deltaTime << endl;
	//cerr << "deltatime " << camera.deltaTime << endl;
	camera.walk();
	camera.render();

	keyboardOperations();

	glMatrixMode(GL_MODELVIEW);

	glPushMatrix();
	//Vector3d v = camera.position;
	//render.sky(2, v);
	//c.rotate();
	//c.draw();
	p.draw();

	glColor4f(1.0, 1.0, 1.0, 1.0);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	//render.initTatemono(mugiwara);
	//render.initTatemono2(mugiwara, 10, true);
	render.pyramid(-58,0,-4,3);
	render.pyramid(-82, 0, -20, 3);
	render.pyramid(-143, 0, 31, 3);
	render.pyramid(-195, 0, 20, 3);

	//glBindTexture(GL_TEXTURE_2D, texture[0]);
	//glEnable(GL_TEXTURE_2D);
	//glColor4f(1.0, 1.0, 1.0, 1.0);

	glCallList(terrarianList);

	glCallList(tatemono);

	//Plane::drawPlaneMultiple(zemn, Vector3d(0.0f, 1.0f, 0.0f), 100, grass, false);
	//glBindTexture(GL_TEXTURE_2D, mugiwara);
	//Plane::drawPlane2(ggg, Vector3d(0.0f,0.0f,1.0f));
	//zemin.draw(grass);
	//wwglDisable(GL_TEXTURE_2D);
	//render.DrawNet(1, 300, 300);
	//render.groundLine();
	glPopMatrix();
	//old_time = glutGet(GLUT_ELAPSED_TIME);
	//cerr << "time " << old_time << endl;
	glutSwapBuffers();

	glutPostRedisplay();
	
}

void reshape(int w,int h){
	glViewport(0, 0, w, h);
	camera.setScreenMidPoint(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
}

void init(void)
{
	cerr << "init start" << endl;
	/* Setup cube vertex data. */
	o << "init function start" << endl;
	LoadGLTextures(myTexture,"grass.png");
	o << "test.bmp loaded" << endl;
	LoadGLTextures(mugiwara, "mugiwara.bmp");
	o << "mugiwara.bmp loaded" << endl;
	LoadGLTextures(grass, "grass_2.png");
	o << "grass_2.png loaded" << endl;

	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping ( NEW )
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations


	o << "texture, depth enabled" << endl;
	/* Enable a single OpenGL light. */
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position2);

	glEnable(GL_LIGHT0);


	glLightfv(GL_LIGHT1, GL_AMBIENT, light_amb2);

	glEnable(GL_LIGHT1);

	glEnable(GL_LIGHTING);

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_DIFFUSE);

	o << "ligth and color material enabled" << endl;
	glMatrixMode(GL_PROJECTION);
	gluPerspective( /* field of view in degree */ fl,
		/* aspect ratio */ 1.0,
		/* Z near */ 1.0, /* Z far */ 100.0);
	glMatrixMode(GL_MODELVIEW);

	/* Adjust cube position to be asthetic angle. */
	cerr << "init end" << endl;


	/*mylibset*/
	//get screen resolution and um, divide it
	camera.setScreenMidPoint(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	camera.oldTime = glutGet(GLUT_ELAPSED_TIME);
	o << "camera mid point set" << endl;
	o << "end of init" << endl;
	cerr << M_PI180 << endl;


	zemn[0]= Vertex(-800.0f, -0.001f, 800.0f);
	zemn[1] = Vertex(800.0f, -0.001f, 800.0f);
	zemn[2] = Vertex(800.0f, -0.001f, -800.0f);
	zemn[3] = Vertex(-800.0f, -0.001f, -800.0f);



	buildList();
	ggg[0] = Vertex(-15.0f, 5.0f, 0,0.0f,0.0f);
	ggg[1] = Vertex(15.0f, 5.0f, 0, 1.0f, 0.0f);
	ggg[2] = Vertex(15.0f, 25.0f, 0, 1.0f, 1.0f);
	ggg[3] = Vertex(-15.0f, 25.0f, 0, 0.0f, 1.0f);

	old_time = glutGet(GLUT_ELAPSED_TIME);
}


void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		o.close();//close log file
		runningLog.close();
		exit(0);
	}
		
	if (button == 3)
	{
		fl += 10;
		glutPostRedisplay();
	}

	else if (button == 4)
	{
		fl -= 10;
		glutPostRedisplay();
	}
}

void mouseMovement(int x, int y){
	//if (camera.mouseWarp==false)
	{
		int diffx = camera.midX - x;
		int diffy = camera.midY - y;
		if (diffx == 0 && diffy == 0) return;
		
		if (camera.mouseX != camera.midX || camera.mouseY != camera.midY)
		{
			//set mouse pointer to center.
			glutWarpPointer(camera.midX, camera.midY);
			camera.mouseWarp = true;
		}

		camera.mouseX = x;
		camera.mouseY = y;
		/*mouse movement*/
		//saga dogru icin eksi - angle,sola +

		camera.rotateY(diffx*0.1f);
		camera.rotateX(diffy*0.1f);
		//camera.rotateXY(diffx*0.1f, diffy*0.1f);

		//yukari dogru icin artý + angle, asagi -
		
		//camera.rotateXY(diffy*0.1f, diffy*0.1f);
		glutPostRedisplay();
	}
	/*else
	{
		camera.mouseWarp = false;
		camera.mouseX = x;
		camera.mouseY = y;
	}*/
	
}

void keyb(unsigned char key, int x, int y){
	switch (key)
	{

	case 'w':
	case 'W':
		camera.moveForward(-0.1f*SPEED);
		break;
	case 's':
	case 'S':
		camera.moveForward(0.1f*SPEED);
		break;
	case 'a':
	case 'A':
		camera.StrafeRight(-0.1f*SPEED);
		break;
	case 'd':
	case 'D':
		camera.StrafeRight(0.1f*SPEED);
		break;
	}
	glutPostRedisplay();
}


void keyboardPressed(unsigned char a, int x, int y)
{
	camera.keyboard[a] = true;
}

void keyboardUp(unsigned char key, int x, int y) {
	camera.keyboard[key] = false;
}

void keyboardOperations(){
	if (camera.keyboard['w'] || camera.keyboard['W'])
	{
		camera.moveForward(-0.1f*SPEED);
	}
	if (camera.keyboard['s'] || camera.keyboard['S'])
	{
		camera.moveForward(0.1f*SPEED);
	}
	if (camera.keyboard['a'] || camera.keyboard['A'])
	{
		camera.StrafeRight(-0.1f*SPEED);
	}
	if (camera.keyboard['d'] || camera.keyboard['D'])
	{
		camera.StrafeRight(0.1f*SPEED);
	}
}




void keyboard2(int key, int x, int y)
{
	cout << "key2 " << key << endl;
	switch (key)
	{
	case GLUT_KEY_UP:
		c.angler -= 10, c.xr = 1, c.yr = 0, c.zr = 0;
		break;
	case GLUT_KEY_DOWN:
		c.angler += 10, c.xr = 1, c.yr = 0, c.zr = 0;
		break;
	case GLUT_KEY_LEFT:
		c.angler -= 10, c.xr = 0, c.yr = 0, c.zr = 1;
		break;
	case GLUT_KEY_RIGHT:
		c.angler += 10, c.xr = 0, c.yr = 0, c.zr = 1;
		break;
	}
	glutPostRedisplay();
}


int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(600, 600);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("FPS Game");
	logfile();
	glutMouseFunc(mouse);
	//glutKeyboardFunc(keyb);
	glutKeyboardFunc(keyboardPressed);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(keyboard2);//special for keyboard arrow keys
	glutPassiveMotionFunc(mouseMovement);//mouse movement
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	
	init();
	glutMainLoop();

	return 0;             /* ANSI C requires main to return int. */
}
