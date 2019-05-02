#include "PlayerObject.h"



CampfireObject::CampfireObject(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Vertex*> uvs, std::string mat) : Object(verts,norms,uvs,mat)
{
	posX = -5;
	posY = 0;
	posZ = 25;
	material = "Textures/CampfireMap.bmp";
	texID = Scene::GetTexture(material);
}


CampfireObject::~CampfireObject()
{
}

void CampfireObject::Display() {
	texID = Scene::GetTexture(material);
	glScalef(0.5, 0.5, 0.5);
	Object::bUV = true;
	Object::Display();
	glScalef(2, 2, 2);
}
