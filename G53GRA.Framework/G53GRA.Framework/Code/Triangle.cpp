#include "Triangle.h"

Triangle::Triangle(std::vector<Vertex*> points,Vertex* colour, std::string fileName,int side) {
	this->points = points;
	this->colour = colour;
	this->fileName = fileName;
	this->side = side;
	xrot = 0.0f;
	yrot = 0.0f;
	zrot = 0.0f;
	scale = 0.5f;
}

void Triangle::Display()
{
	int texID = Scene::GetTexture(fileName);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID);
	glBegin(GL_TRIANGLES);
	//glColor3f(colour->x, colour->y, colour->z);
	if (side == 0) {
		glTexCoord2f(0, 0);
		glVertex3f(points[0]->x, points[0]->y, points[0]->z);
		glTexCoord2f(1, 0);
		glVertex3f(points[1]->x, points[1]->y, points[1]->z);
		glTexCoord2f(0, 1);
		glVertex3f(points[2]->x, points[2]->y, points[2]->z);
	}	else {		glTexCoord2f(1, 0);
		glVertex3f(points[0]->x, points[0]->y, points[0]->z);
		glTexCoord2f(0, 1);
		glVertex3f(points[1]->x, points[1]->y, points[1]->z);
		glTexCoord2f(1, 1);
		glVertex3f(points[2]->x, points[2]->y, points[2]->z);	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}

void Triangle::Update(const double& deltaTime)
{

}

void Triangle::HandleKey(unsigned char key, int state, int x, int y)
{

}