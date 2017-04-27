#include "Plane.h"
namespace gnr
{


	Plane::Plane(GLfloat x, GLfloat y, GLfloat z, GLfloat length, GLfloat width, Vector3d &dir) :Shape(x, y, z), planelength(length), planewidth(width), direction(dir){

	}

	Plane::Plane()
	{
		planelength = 1;
		planewidth = 1;
		direction = Vector3d(0.0f, 1.0f, 0.0f);
	}

	void Plane::draw(GLint a){
		glBindTexture(GL_TEXTURE_2D, a);
		glBegin(GL_QUADS);
		glNormal3f(0.0f, 1.0f, 0.0f);

		glTexCoord2f(0.0f, 100.0f); glVertex3f(x - planewidth / 2.0f, y, z - planelength / 2.0f);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x - planewidth / 2.0f, y, z + planelength / 2.0f);
		glTexCoord2f(60.0f, 0.0f); glVertex3f(x + planewidth / 2.0f, y, z + planelength / 2.0f);
		glTexCoord2f(60.0f, 100.0f); glVertex3f(x + planewidth / 2.0f, y, z - planelength / 2.0f);
		glEnd();
	}
	void Plane::draw(){
		glBegin(GL_QUADS);
		glVertex3f(x - planewidth / 2.0f, y, z - planelength / 2.0f);
		glVertex3f(x - planewidth / 2.0f, y, z + planelength / 2.0f);
		glVertex3f(x + planewidth / 2.0f, y, z + planelength / 2.0f);
		glVertex3f(x + planewidth / 2.0f, y, z - planelength / 2.0f);
		glEnd();
	}

	// draw a plane with n polygon
	// v[0] left bottom corner, v[1] right bottom corner and so on, anti clockwise 
	void Plane::drawPlaneMultiple(mPolygon polygon, Vector3d &normal, int step, GLint texture, bool wholeTexture){
		Vector3d distancex(polygon[2] - polygon[3]);
		Vector3d distancey(polygon[0] - polygon[3]);

		GLfloat textureDifx = (float)(1.0 / (double)step);
		GLfloat textureDify = (float)(1.0 / (double)step);

		GLfloat ctu = 0.0f;//artacak(current texture u)
		GLfloat ctv = 1.0f;//azalacak(current texture v)

		Vector3d difx = distancex*(float)(1.0 / (double)step);// calculate step vector
		//std::cerr << "disx " << distancex.x << " " << distancex.y << " " << distancex.z << std::endl;
		//std::cerr << "disy " << distancey.x << " " << distancey.y << " " << distancey.z << std::endl;

		Vector3d dify = distancey*(float)(1.0 / (double)step);// calculate step vector
		//std::cerr << "difx " << difx.x << " " << difx.y << " " << difx.z << std::endl;
		//std::cerr << "dify " << dify.x << " " << dify.y << " " << dify.z << std::endl;
		Vertex plane[4];
		Vertex vx,vstart;
		vx = polygon[3];
		vstart = vx;
		//std::cerr << "\nvx " << vx.x << " " << vx.y << " " << vx.z << std::endl << std::endl;
		
		for (int x = 0; x < step; x++)
		{
			for (int y = 0; y < step; y++)
			{
				//std::cerr << "\nvx " << vx.x << " " << vx.y << " " << vx.z << std::endl << std::endl;
				polygon[3] = vx;
				polygon[2] = vx + difx;
				polygon[1] = vx + difx + dify;
				polygon[0] = vx + dify;



				if (wholeTexture)
				{
					polygon[0].u = ctu; polygon[0].v = ctv - textureDify;
					polygon[1].u = ctu + textureDifx; polygon[1].v = ctv - textureDify;
					polygon[2].u = ctu+textureDifx; polygon[2].v = ctv;
					polygon[3].u = ctu; polygon[3].v = ctv;
				}
				else
				{
					polygon[0].u = 0.0f; polygon[0].v = 0.0f;
					polygon[1].u = 1.0f; polygon[1].v = 0.0f;
					polygon[2].u = 1.0f; polygon[2].v = 1.0f;
					polygon[3].u = 0.0f; polygon[3].v = 1.0f;
				}

				Vector3d::normalizeCalculater(polygon, normal);
				glBindTexture(GL_TEXTURE_2D, texture);
				drawPlane2(polygon, normal);
				vx = vx + dify;
				ctv -= textureDify;
			}
			vx = vstart + (difx*x);
			ctv = 1.0f;
			ctu += textureDifx;
			vx = vx + difx;
		}

	}

	void Plane::drawPlane2(mPolygon &vertexes, Vector3d &normal){
		glBegin(GL_QUADS);
		glNormal3f(normal.x, normal.y, normal.z);
		glTexCoord2f(vertexes[0].u, vertexes[0].v); glVertex3f(vertexes[0].x, vertexes[0].y, vertexes[0].z);
		glTexCoord2f(vertexes[1].u, vertexes[1].v); glVertex3f(vertexes[1].x, vertexes[1].y, vertexes[1].z);
		glTexCoord2f(vertexes[2].u, vertexes[2].v); glVertex3f(vertexes[2].x, vertexes[2].y, vertexes[2].z);
		glTexCoord2f(vertexes[3].u, vertexes[3].v); glVertex3f(vertexes[3].x, vertexes[3].y, vertexes[3].z);
		glEnd();

	}
	
	void Plane::drawPlane(mPolygon &p, GLint texture)
	{

	}

	Plane::~Plane()
	{
	}
}//namespace gnr