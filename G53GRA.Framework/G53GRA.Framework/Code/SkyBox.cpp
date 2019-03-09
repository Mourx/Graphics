#include "SkyBox.h"



SkyBox::SkyBox(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Vertex*> uvs, std::string mat) : Object(verts, norms, uvs, mat)
{
	posX = 0;
	posY = -1;
	posZ = 0;
	this->material = mat;
	texID = Scene::GetTexture(material);
}


SkyBox::~SkyBox()
{
}


void SkyBox::Display() {
	glFrontFace(GL_CW);
	glScalef(100, 100, 100);
	Object::Display();
	glScalef(0.01, 0.01, 0.01);
	glFrontFace(GL_CCW);
}