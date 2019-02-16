#include "PlayerObject.h"



PlayerObject::PlayerObject(std::vector<Vertex*> verts, std::vector<Vertex*> norms) : Object(verts,norms)
{
	posX = -5;
	posY = 0;
	posZ = 25;
}


PlayerObject::~PlayerObject()
{
}

void PlayerObject::Display() {
	Object::Display();
}
