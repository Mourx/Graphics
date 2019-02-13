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
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_COLOR_MATERIAL);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID);
	float specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float shininess = 128.0f;
	glBegin(GL_TRIANGLES);
	//glColor3f(colour->x, colour->y, colour->z);
	glMaterialfv(GL_FRONT, GL_SPECULAR, static_cast<GLfloat*>(specular));
	glMaterialf(GL_FRONT, GL_SHININESS, static_cast<GLfloat>(shininess));
	if (side == 0) {
		glTexCoord2f(0, 0);
		glVertex3f(points[0]->x, points[0]->y, points[0]->z);
		glTexCoord2f(1, 0);
		glVertex3f(points[1]->x, points[1]->y, points[1]->z);
		glTexCoord2f(0, 1);
		glVertex3f(points[2]->x, points[2]->y, points[2]->z);
	}
	else {
		glTexCoord2f(1, 0);
		glVertex3f(points[0]->x, points[0]->y, points[0]->z);
		glTexCoord2f(0, 1);
		glVertex3f(points[1]->x, points[1]->y, points[1]->z);
		glTexCoord2f(1, 1);
		glVertex3f(points[2]->x, points[2]->y, points[2]->z);
	}

	glEnd();
	glEnable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glPopAttrib();
	glPopMatrix();
}

void Triangle::Update(const double& deltaTime)
{

}

void Triangle::HandleKey(unsigned char key, int state, int x, int y)
{

}