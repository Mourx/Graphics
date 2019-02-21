#include "Object.h"



Object::Object()
{
}

Object::Object(std::vector<Vertex*> verts, std::vector<Vertex*> norms,std::vector<Vertex*> uvs,std::string mat) {
	vertices = verts;
	normals = norms;
	this->uvs = uvs;
	posX = -5;
	posY = 0;
	posZ = -5;
	material = mat;
}

Object::~Object()
{
}

void Object::Display() {
	std::vector<Vertex*> points;
	int texID = Scene::GetTexture("Textures/cube.bmp");

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID);
	//glScalef(1, 1, 1);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < vertices.size(); i+=3) {
		glColor3f(1,1,1);
		glNormal3f(normals[i]->x,normals[i]->y,normals[i]->z);
		points.push_back(vertices[i]);
		points.push_back(vertices[i+1]);
		points.push_back(vertices[i+2]);
		if(bUV) glTexCoord2f(uvs[i]->x, uvs[i]->y);
		glVertex3f(posX+points[0]->x*4, points[0]->y*4, posZ + points[0]->z*4);
		if (bUV) glTexCoord2f(uvs[i+1]->x, uvs[i+1]->y);
		glVertex3f(posX + points[1]->x*4, points[1]->y*4, posZ + points[1]->z*4);
		if (bUV) glTexCoord2f(uvs[i+2]->x, uvs[i+2]->y);
		glVertex3f(posX + points[2]->x*4, points[2]->y*4, posZ + points[2]->z*4);
		

		points.clear();

	}

	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);


}
void Object::Update(const double& deltaTime) {}
void Object::HandleKey(unsigned char key, int state, int x, int y) {}