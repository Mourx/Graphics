#include "ArmObject.h"

#define PI 3.14159265

ArmObject::ArmObject(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Vertex*> uvs, std::string mat):Object(verts, norms, uvs, mat)
{	
		//create limbs
		ldr = new ObjLoader();
		ldr->LoadObj("Models/Robot_Limb.obj", true);
		LimbTop = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), ldr->getMat());
		LimbBottom = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), ldr->getMat());
		//and joints
		ldr = new ObjLoader();
		ldr->LoadObj("Models/Robot_Joint.obj", true);
		JointTop = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), ldr->getMat());
		JointMiddle = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), ldr->getMat());

		//initialise textures
		texID = Scene::GetTexture("Textures/Steel.bmp");
		LimbTop->texID = texID;
		JointTop->texID = texID;
		LimbBottom->texID = texID;
		JointMiddle->texID = texID;

		scaleZ = 0.45;
}


ArmObject::~ArmObject()
{
}


void ArmObject::Display() {
	bUV = true;

	
	//Display parts
	JointTop->Display();
	LimbTop->Display();
	JointMiddle->Display();
	LimbBottom->Display();
	
}
void ArmObject::Update(const double& deltaTime) {
	//switch directions when reached certain bend
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


	//setup values for animation calculations
	float limbLength = 27 * scaleZ;
	float offsetX = (limbLength - 5) * cos(angleLittle * PI / 180.0);
	float offsetY = (limbLength - 5) * sin(angleLittle * PI / 180.0);

	//initialise colours for hit flash
	JointTop->setColour(red, green, blue);
	JointMiddle->setColour(red, green, blue);
	LimbTop->setColour(red, green, blue);
	LimbBottom->setColour(red, green, blue);

	//setup positions
	JointTop->setPosition(posX, posY, posZ);
	LimbTop->setPosition(JointTop->posX, JointTop->posY, JointTop->posZ);
	JointMiddle->setPosition(LimbTop->posX, LimbTop->posY - offsetY, LimbTop->posZ - offsetX);
	LimbBottom->setPosition(JointMiddle->posX, JointMiddle->posY, JointMiddle->posZ);
	
	//scales
	JointTop->setScale(0.75, 0.4, 0.4);
	JointMiddle->setScale(0.75, 0.4, 0.4);
	LimbTop->setScale(0.5, 0.6, scaleZ);
	LimbBottom->setScale(0.4, 0.5, scaleZ*0.9);

	//angles
	LimbTop->setAngle(angleBig, 1.0, 0, 0);
	JointMiddle->setAngle(angleBig, 1.0, 0, 0);
	LimbBottom->setAngle(angleBend, 1.0, 0, 0);
}

void ArmObject::setBend(float angle) {
	//angles for bending arms
	angleBig = angle;
	angleBend = 90+ (angle / 0.3)*0.5;


	if (angleBig <= 15) {
		bDirection = 0;
	}
	else {
		bDirection = 1;
	}
}