#include "ProjectileObject.h"
#include "ObjLoader.h"
#define PI 3.14159265

ProjectileObject::ProjectileObject(Vertex* position,Vertex* speed,Object* tg,Object* p)
{
	posX = position->x;
	posY = position->y;
	posZ = position->z;
	speedX = speed->x;
	speedY = speed->y;
	speedZ = speed->z;
	target = tg;
	parent = p;
	ReTarget();
	ObjLoader* ldr = new ObjLoader();
	ldr->LoadObj("Models/Missile.obj", true);
	missile = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), ldr->getMat());
	missile->texID = Scene::GetTexture("Textures/Steel.bmp");
	missile->setScale(0.2, 0.2, 0.2);
}


ProjectileObject::~ProjectileObject()
{
}


void ProjectileObject::Display() {
	
	glPushMatrix();
	double cosAngle = cos((angle* PI)/180);
	double sinAngle = sin((angle* PI) / 180);
	double xPartX = cosAngle * posX;
	std::vector<Vertex*> points;

	glRotatef(-angle, 0, 1, 0);
	//glTranslatef(-cosAngle*posX + -sinAngle * posZ, posY, -cosAngle * posZ + -sinAngle * posX);
	//glTranslatef(posX, posY, posZ);
	glColor3f(1, 0, 0);
	glutSolidSphere(0.5, 10, 5);
	missile->setAngle(angle-90, 0, 1, 0);
	
	missile->setPosition(posX, posY, posZ);
	missile->Display();
	glPopMatrix();

}

void ProjectileObject::Update(const double& deltaTime) {
	
	Object::Update(deltaTime);
	ReTarget();
	posX += speedX * deltaTime * dirX*25;
	posY += speedY * deltaTime * dirY * 25;
	posZ += speedZ * deltaTime * dirZ*25;
	if (std::abs(target->posX - (posX + parent->posX)) < 5 &&
		std::abs(target->posY-5 - (posY + parent->posY)) < 5 &&
		std::abs(target->posZ - (posZ + parent->posZ)) < 5) {
		EnemyObject* enemy = (EnemyObject*)target;
		enemy->Flash(deltaTime);
		bFinished = true;
	}
	missile->setScale(missile->scaleX + 0.01, missile->scaleY + 0.01, missile->scaleZ + 0.01);
}

bool ProjectileObject::isFinished() {
	return bFinished;
}

void ProjectileObject::ReTarget() {

	Vertex* vert = new Vertex(posX + parent->posX, posY + parent->posY, posZ + parent->posZ);
	Vertex* targetv = new Vertex(target->posX, target->posY-5, target->posZ);
	vert->x = targetv->x - vert->x;
	vert->y = targetv->y - vert->y;
	vert->z = targetv->z - vert->z;
	double vertLength = sqrt(pow(vert->x, 2) + pow(vert->y, 2) + pow(vert->z, 2));
	dirX = vert->x / vertLength;
	dirZ = vert->z / vertLength;
	dirY = vert->y / vertLength;
	
}