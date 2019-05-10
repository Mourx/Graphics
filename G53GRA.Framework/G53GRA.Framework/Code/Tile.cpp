#include "Tile.h"



Tile::Tile(std::vector<Vertex*> points, Vertex* colour, std::string fileName)
{
	this->points = points;
	this->colour = colour;
	this->fileName = fileName;

	xrot = 0.0f;
	yrot = 0.0f;
	zrot = 0.0f;
	scale = 0.5f;
}


Tile::~Tile()
{
}

void Tile::Display()
{
	glPushMatrix();
	int texID = Scene::GetTexture(fileName);
	
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, texID);
	float specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	float shininess = 128.0f;
	glBegin(GL_QUADS);
	float wDiffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, wDiffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
	//glColor3f(colour->x, colour->y, colour->z);
	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(points[0]->x, points[0]->y, points[0]->z);
	glTexCoord2f(1, 0);
	glVertex3f(points[1]->x, points[1]->y, points[1]->z);
	glTexCoord2f(1, 1);
	glVertex3f(points[2]->x, points[2]->y, points[2]->z);
	glTexCoord2f(0, 1);
	glVertex3f(points[3]->x, points[3]->y, points[3]->z);
	
	

	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void Tile::Update(const double& deltaTime)
{

}

void Tile::HandleKey(unsigned char key, int state, int x, int y)
{

}