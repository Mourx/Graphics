#include "ArmObject.h"

#define PI 3.14159265

ArmObject::ArmObject(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Vertex*> uvs, std::string mat):Object(verts, norms, uvs, mat)
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
	
}


ArmObject::~ArmObject()
{
}


void ArmObject::Display() {
	bUV = true;
	texID = Scene::GetTexture("Textures/Steel.bmp");

	LimbTop->texID = Scene::GetTexture("Textures/Steel.bmp");
	JointTop->texID = Scene::GetTexture("Textures/Steel.bmp");
	LimbBottom->texID = Scene::GetTexture("Textures/Steel.bmp");
	JointMiddle->texID = Scene::GetTexture("Textures/Steel.bmp");
	scaleZ = 0.45;
	float limbLength = 27 * scaleZ;
	float offsetX = (limbLength - 5) * cos(angleLittle * PI / 180.0);
	float offsetY = (limbLength - 5) * sin(angleLittle * PI / 180.0);

	JointTop->setColour(red, green, blue);
	JointMiddle->setColour(red, green, blue);
	LimbTop->setColour(red, green, blue);
	LimbBottom->setColour(red, green, blue);

	JointTop->setPosition(posX, posY, posZ);
	JointTop->setScale(0.75, 0.4, 0.4);
	LimbTop->setPosition(JointTop->posX, JointTop->posY, JointTop->posZ);
	JointMiddle->setPosition(LimbTop->posX, LimbTop->posY - offsetY, LimbTop->posZ - offsetX);
	JointMiddle->setScale(0.75, 0.4, 0.4);
	LimbBottom->setPosition(JointMiddle->posX, JointMiddle->posY, JointMiddle->posZ);

	JointTop->Display();
	LimbTop->setScale(0.5, 0.6, scaleZ);
	
	LimbTop->setAngle(angleBig, 1.0, 0, 0);
	JointMiddle->setAngle(angleBig, 1.0, 0, 0);
	LimbBottom->setAngle(angleBend, 1.0, 0, 0);
	LimbBottom->setScale(0.4, 0.5, scaleZ*0.9);
	LimbTop->Display();
	
	JointMiddle->Display();
	
	LimbBottom->Display();
	
}
void ArmObject::Update(const double& deltaTime) {
	if (bDirection == 0) {
		if (angleBig <= 15) {
			angleBig += 0.3;
			angleBend += 0.5;
		}
		else {
			bDirection = 1;
		}
	}
	if (bDirection == 1) {
		if (angleBig >= -45) {
			angleBig -= 0.3; 
			angleBend -= 0.5;
		}
		else {
			bDirection = 0;
		}
	}
	
	
	angleLittle = 360 - angleBig;

}

void ArmObject::setBend(float angle) {
	angleBig = angle;
	angleBend = 90+ (angle / 0.3)*0.5;
	if (angleBig <= 15) {
		bDirection = 0;
	}
	else {
		bDirection = 1;
	}
}