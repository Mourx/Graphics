#include "CampfireObject.h"



CampfireObject::CampfireObject(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Vertex*> uvs, std::string mat) : Object(verts,norms,uvs,mat)
{
	
	posX = -5;
	posY = 0;
	posZ = 25;
	material = "Textures/CampfireMap.bmp";
	texID = Scene::GetTexture(material);
	light = new Light(new Vertex(posX, posY+2, posZ-10), GL_LIGHT1);
	light2 = new Light(new Vertex(posX+2, posY + 4, posZ - 8), GL_LIGHT2);
	light3 = new Light(new Vertex(posX+4, posY + 6, posZ - 12), GL_LIGHT3);
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
	light->Display();
	light2->Display();
	light3->Display();
}

void CampfireObject::Update(const double& deltaTime) {
	light->setPosition(light->position->x, light->position->y + 0.2, light->position->z);
	if (light->position->y >= 10) {
		light->position->y = 0;
	}
	light2->setPosition(light2->position->x, light2->position->y + 0.3, light2->position->z);
	if (light2->position->y >= 10) {
		light2->position->y = 0;
	}
	light3->setPosition(light3->position->x, light3->position->y + 0.1, light3->position->z);
	if (light3->position->y >= 10) {
		light3->position->y = 0;
	}
}
