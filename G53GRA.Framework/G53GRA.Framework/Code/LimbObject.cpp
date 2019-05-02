#include "LimbObject.h"

#define PI 3.14159265

LimbObject::LimbObject(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Vertex*> uvs, std::string mat):Object(verts, norms, uvs, mat)
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


LimbObject::~LimbObject()
{
}


void LimbObject::Display() {
	bUV = true;
	texID = Scene::GetTexture("Textures/Steel.bmp");

	LimbTop->texID = Scene::GetTexture("Textures/Steel.bmp");
	JointTop->texID = Scene::GetTexture("Textures/Steel.bmp");
	LimbBottom->texID = Scene::GetTexture("Textures/Steel.bmp");
	JointMiddle->texID = Scene::GetTexture("Textures/Steel.bmp");
	scaleZ = 0.6;
	float limbLength = 24 * scaleZ;
	float offsetX = (limbLength - 5) * cos(angleLittle * PI / 180.0);
	float offsetY = (limbLength - 5) * sin(angleLittle * PI / 180.0);


	JointTop->setPosition(posX, posY, posZ);
	JointTop->setPosition2(pos2X, pos2Y,pos2Z);
	JointTop->setScale(0.75, 0.4, 0.4);
	LimbTop->setPosition(JointTop->posX, JointTop->posY, JointTop->posZ);
	LimbTop->setPosition2(JointTop->pos2X, JointTop->pos2Y, JointTop->pos2Z);
	JointMiddle->setPosition(LimbTop->posX, LimbTop->posY, LimbTop->posZ);
	JointMiddle->setPosition2(LimbTop->pos2X, LimbTop->pos2Y - offsetY, LimbTop->pos2Z - offsetX);
	JointMiddle->setScale(0.75, 0.4, 0.4);
	LimbBottom->setPosition(JointMiddle->posX, JointMiddle->posY, JointMiddle->posZ);
	LimbBottom->setPosition2(JointMiddle->pos2X, JointMiddle->pos2Y, JointMiddle->pos2Z);

	JointTop->Display();
	LimbTop->setScale(0.6, 0.6, scaleZ);
	
	LimbTop->setAngle2(angleBig, 1.0, 0, 0);
	JointMiddle->setAngle2(angleBig, 1.0, 0, 0);
	LimbBottom->setAngle2(angleBend, 1.0, 0, 0);
	LimbBottom->setScale(0.5, 0.5, scaleZ*0.9);
	LimbTop->Display();
	
	JointMiddle->Display();
	
	LimbBottom->Display();
	
}
void LimbObject::Update(const double& deltaTime) {
	if (bDirection == 0) {
		if (angleBig <= 15) {
			angleBig += 0.2;
			angleBend += 0.5;
		}
		else {
			bDirection = 1;
		}
	}
	if (bDirection == 1) {
		if (angleBig >= -45) {
			angleBig -= 0.2; 
			angleBend -= 0.5;
		}
		else {
			bDirection = 0;
		}
	}
	
	
	angleLittle = 360 - angleBig;

	
	JointTop->angle = angle;
	JointTop->angleX = angleX;
	JointTop->angleY = angleY;
	JointTop->angleZ = angleZ;

	LimbTop->angle = angle;
	LimbTop->angleX = angleX;
	LimbTop->angleY = angleY;
	LimbTop->angleZ = angleZ;

	JointMiddle->angle = angle;
	JointMiddle->angleX = angleX;
	JointMiddle->angleY = angleY;
	JointMiddle->angleZ = angleZ;

	LimbBottom->angle = angle;
	LimbBottom->angleX = angleX;
	LimbBottom->angleY = angleY;
	LimbBottom->angleZ = angleZ;
	

}