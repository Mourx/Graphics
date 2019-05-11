#include "ProjectileObject.h"

#define PI 3.14159265

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
	//glBegin(GL_LINES);
	glPushMatrix();
	glTranslatef(posX, posY, posZ);
	glColor3f(1, 0, 0);
	glutSolidSphere(0.5, 10, 5);
	glPopMatrix();
	//glVertex3f(posX, posY, posZ);
	//glVertex3f(posX + -1 * dirX, posY, posZ + -1 * dirZ);
	//glEnd();
}

void ProjectileObject::Update(const double& deltaTime) {
	
	Object::Update(deltaTime);
	ReTarget();
	posX += speedX * deltaTime * dirX*15;
	posY += speedY * deltaTime * dirY * 15;
	posZ += speedZ * deltaTime * dirZ*15;
	if (std::abs(target->posX - posX) < 5 &&
		std::abs(target->posY - posY) < 5 && 
		std::abs(target->posZ - posZ) < 5) {
		EnemyObject* enemy = (EnemyObject*)target;
		enemy->Flash(deltaTime);
		bFinished = true;
	}
}

bool ProjectileObject::isFinished() {
	return bFinished;
}

void ProjectileObject::ReTarget() {
	dirX = target->posX - posX;
	dirZ = target->posZ - posZ;
	Vertex* vert = new Vertex(posX, posY, posZ);
	Vertex* targetv = new Vertex(target->posX, target->posY, target->posZ);
	vert->x = targetv->x - vert->x;
	vert->y = targetv->y - vert->y;
	vert->z = targetv->z - vert->z;
	double vertLength = sqrt(pow(vert->x, 2) + pow(vert->y, 2) + pow(vert->z, 2));
	dirX = vert->x/vertLength;
	dirZ = vert->z/vertLength;
	if (abs(dirX) >= 1) {
		//if (std::abs(dirX) < 5) {
		//	dirX = 0;
		//}
		//else {
			//dirX >= 0 ? dirX = 1 *cos(angle) : dirX = -1 * cos(angle);
		//}
	}
	dirY = target->posY - posY;
	if (abs(dirY) >= 1) {
		//if (std::abs(dirY) < 5) {
		//	dirY = 0;
		//}
		//else {
			//dirY >= 0 ? dirY = 1 : dirY = -1;
		//}
	}
	
	if (dirZ != 0) {
		//if (std::abs(dirZ) < 5) {
		//	dirZ = 0;
		//}
		//else {
			//dirZ >= 0 ? dirZ = 1 * sin(angle): dirZ = -1 * sin(angle);
		//}
	}
}