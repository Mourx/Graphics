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
	glVertex3f(posX + -1 * dirX, posY +  -1 * dirY, posZ + -1 * dirZ);
	glEnd();
}

void ProjectileObject::Update(const double& deltaTime) {
	
	Object::Update(deltaTime);
	ReTarget();
	posX += speedX * deltaTime * dirX*3;
	posY += speedY * deltaTime * dirY*3;
	posZ += speedZ * deltaTime * dirZ*3;
	if (dirX == 0 && dirY == 0 && dirY == 0) {
		
		bFinished = true;
	}
}

bool ProjectileObject::isFinished() {
	return bFinished;
}

void ProjectileObject::ReTarget() {
	dirX = target->posX - posX;
	if (dirX != 0) {
		if (std::abs(dirX) < 5) {
			dirX = 0;
		}
		else {
			dirX >= 0 ? dirX = 1 : dirX = -1;
		}
	}
	dirY = target->posY+10 - posY;
	if (dirY != 0) {
		if (std::abs(dirY) < 5) {
			dirY = 0;
		}
		else {
			dirY >= 0 ? dirY = 1 : dirY = -1;
		}
	}
	dirZ = target->posZ - posZ;
	if (dirZ != 0) {
		if (std::abs(dirZ) < 5) {
			dirZ = 0;
		}
		else {
			dirZ >= 0 ? dirZ = 1 : dirZ = -1;
		}
	}
}