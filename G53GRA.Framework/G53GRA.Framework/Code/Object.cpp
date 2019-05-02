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
	glPushMatrix();

	

	glTranslatef(posX, posY, posZ);
	glRotatef(angle, angleX, angleY, angleZ);
	glTranslatef(pos2X, pos2Y, pos2Z);
	glRotatef(angle2, angle2X, angle2Y, angle2Z);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID);
	glScalef(scaleX, scaleY, scaleZ);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < vertices.size(); i+=3) {
		glColor3f(1,1,1);
		glNormal3f(normals[i]->x,normals[i]->y,normals[i]->z);
		points.push_back(vertices[i]);
		points.push_back(vertices[i+1]);
		points.push_back(vertices[i+2]);
		if(bUV) glTexCoord2f(uvs[i]->x, uvs[i]->y);
		glVertex3f(points[0]->x*4, points[0]->y*4, points[0]->z*4);
		if (bUV) glTexCoord2f(uvs[i+1]->x, uvs[i+1]->y);
		glVertex3f(points[1]->x*4, points[1]->y*4, points[1]->z*4);
		if (bUV) glTexCoord2f(uvs[i+2]->x, uvs[i+2]->y);
		glVertex3f(points[2]->x*4, points[2]->y*4, points[2]->z*4);
		

		points.clear();

	}

	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

}
void Object::Update(const double& deltaTime) {
	

}

void Object::setPosition(float x, float y, float z) {
	posX = x;
	posY = y;
	posZ = z;
}

void Object::setPosition2(float x, float y, float z) {
	pos2X = x;
	pos2Y = y;
	pos2Z = z;
}

void Object::setAngle2(float a, float x, float y, float z) {
	angle2 = a;
	angle2X = x;
	angle2Y = y;
	angle2Z = z;
}

void Object::setScale(float x, float y, float z) {
	scaleX = x;
	scaleY = y;
	scaleZ = z;
}

void Object::HandleKey(unsigned char key, int state, int x, int y) {}