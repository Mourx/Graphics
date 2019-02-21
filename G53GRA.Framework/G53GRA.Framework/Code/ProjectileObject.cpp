#include "ProjectileObject.h"



ProjectileObject::ProjectileObject(Vertex* position,Vertex* speed,Object* tg)
{
	posX = position->x;
	posY = position->y;
	posZ = position->z;
	speedX = speed->x;
	speedY = speed->y;
	speedZ = speed->z;
	target = tg;
	ReTarget();
}


ProjectileObject::~ProjectileObject()
{
}


void ProjectileObject::Display() {
	glBegin(GL_LINES);
	glColor3f(255, 1, 1);
	glVertex3f(posX, posY, posZ);
	glVertex3f(posX + -1 * speedX, posY +  -1 * speedY, posZ + -1 * speedZ);
	glEnd();
}

void ProjectileObject::Update(const double& deltaTime) {
	
	Object::Update(deltaTime);
	ReTarget();
	posX += speedX * deltaTime * dirX;
	posY += speedY * deltaTime * dirY;
	posZ += speedZ * deltaTime * dirZ;
	if (dirX == 0 && dirY == 0 && dirY == 0) {
		//delete this;
	}
}

void ProjectileObject::ReTarget() {
	dirX = target->posX - posX;
	if (dirX != 0) {
		dirX >= 0 ? dirX = 1 : dirX = -1;
	}
	dirY = target->posY - posY;
	if (dirY != 0) {
		dirY >= 0 ? dirY = 1 : dirY = -1;
	}
	dirZ = target->posZ - posZ;
	if (dirZ != 0) {
		dirZ >= 0 ? dirZ = 1 : dirZ = -1;
	}
}