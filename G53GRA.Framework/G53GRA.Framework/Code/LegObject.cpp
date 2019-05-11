#include "LegObject.h"

#include "ArmObject.h"

#define PI 3.14159265

LegObject::LegObject(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Vertex*> uvs, std::string mat) :Object(verts, norms, uvs, mat)
{
	ldr = new ObjLoader();
	ldr->LoadObj("Models/Robot_Limb.obj", true);
	LimbTop = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), ldr->getMat());
	LimbBottom = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), ldr->getMat());
	//do arm
	ldr = new ObjLoader();
	ldr->LoadObj("Models/Robot_Joint.obj", true);
	JointTop = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), ldr->getMat());
	JointMiddle = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), ldr->getMat());
	ldr = new ObjLoader();
	ldr->LoadObj("Models/Robot_Foot.obj", true);
	FootObj = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), ldr->getMat());

}
LegObject::~LegObject()
{
}

void LegObject::Display() {
	bUV = true;
	texID = Scene::GetTexture("Textures/Steel.bmp");

	LimbTop->texID = Scene::GetTexture("Textures/Steel.bmp");
	JointTop->texID = Scene::GetTexture("Textures/Steel.bmp");
	LimbBottom->texID = Scene::GetTexture("Textures/Steel.bmp");
	JointMiddle->texID = Scene::GetTexture("Textures/Steel.bmp");
	FootObj->texID = Scene::GetTexture("Textures/Steel.bmp");
	scaleZ = 0.6;
	float limbLength = 24 * scaleZ;
	float offsetX = (limbLength - 5) * cos(angleLittle * PI / 180.0);
	float offsetY = (limbLength - 5) * sin(angleLittle * PI / 180.0);

	JointTop->setColour(red, green, blue);
	JointMiddle->setColour(red, green, blue);
	LimbTop->setColour(red, green, blue);
	LimbBottom->setColour(red, green, blue);
	FootObj->setColour(red, green, blue);

	JointTop->setPosition(posX, posY, posZ);
	JointTop->setScale(0.75, 0.4, 0.4);
	LimbTop->setPosition(JointTop->posX, JointTop->posY, JointTop->posZ);
	JointMiddle->setPosition(LimbTop->posX, LimbTop->posY - offsetY, LimbTop->posZ - offsetX);
	JointMiddle->setScale(0.75, 0.4, 0.4);
	LimbBottom->setPosition(JointMiddle->posX, JointMiddle->posY, JointMiddle->posZ);

	JointTop->Display();
	LimbTop->setScale(0.6, 0.6, scaleZ);

	LimbTop->setAngle(angleBig, 1.0, 0, 0);
	JointMiddle->setAngle(angleBig, 1.0, 0, 0);
	LimbBottom->setAngle(angleBend, 1.0, 0, 0);
	LimbBottom->setScale(0.5, 0.5, scaleZ*0.9);
	LimbTop->Display();

	JointMiddle->Display();

	LimbBottom->Display();
	limbLength = 24 * scaleZ;
	offsetX = (limbLength - 5) * cos(angleLittle * PI / 180.0);
	offsetY = (limbLength - 5) * sin(angleLittle * PI / 180.0);
	FootObj->setScale(0.5, 0.5, 0.5);
	FootObj->setPosition(LimbBottom->posX, LimbBottom->posY - offsetY, LimbBottom->posZ - offsetX);
	FootObj->Display();
}
void LegObject::Update(const double& deltaTime) {
	if (bDirection == 0) {
		if (angleBig <= 300) {
			angleBig += 0.5;
			angleBend += 0.4;
		}
		else {
			bDirection = 1;
		}
	}
	if (bDirection == 1) {
		if (angleBig >= 240) {
			angleBig -= 0.5;
			angleBend -= 0.4;
		}
		else {
			bDirection = 0;
		}
	}


	angleLittle = 360 - angleBig;

}

void LegObject::setBend(float angle) {
	angleBig = angle;
	angleBend = 45 + (angle / 0.5)*0.4;
	if (angleBig <= 300) {
		bDirection = 0;
	}
	else {
		bDirection = 1;
	}
}