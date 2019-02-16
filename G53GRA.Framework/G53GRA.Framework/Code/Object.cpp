#include "Object.h"



Object::Object()
{
}

Object::Object(std::vector<Vertex*> verts, std::vector<Vertex*> norms) {
	vertices = verts;
	normals = norms;
	posX = -5;
	posY = 0;
	posZ = -5;
}

Object::~Object()
{
}

void Object::Display() {
	std::vector<Vertex*> points;

	//glScalef(1, 1, 1);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < vertices.size(); i+=3) {
		glColor3f(255,255,255);
		points.push_back(vertices[i]);
		points.push_back(vertices[i+1]);
		points.push_back(vertices[i+2]);
		glVertex3f(posX+points[0]->x*4, points[0]->y*4, posZ + points[0]->z*4);
		glVertex3f(posX + points[1]->x*4, points[1]->y*4, posZ + points[1]->z*4);
		glVertex3f(posX + points[2]->x*4, points[2]->y*4, posZ + points[2]->z*4);
		

		points.clear();

	}
	
	glEnd();


}
void Object::Update(const double& deltaTime) {}
void Object::HandleKey(unsigned char key, int state, int x, int y) {}