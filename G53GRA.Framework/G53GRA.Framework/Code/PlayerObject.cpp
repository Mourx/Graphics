#include "PlayerObject.h"



PlayerObject::PlayerObject(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Vertex*> uvs, std::string mat) : Object(verts,norms,uvs,mat)
{
	posX = -5;
	posY = 0;
	posZ = 25;
	material = "Textures/Dirt.bmp";
	texID = Scene::GetTexture(material);
}


PlayerObject::~PlayerObject()
{
}

void PlayerObject::Display() {
	bUV = false;
	Object::Display();
}
