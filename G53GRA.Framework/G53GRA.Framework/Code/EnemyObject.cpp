#include "EnemyObject.h"



EnemyObject::EnemyObject(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Vertex*> uvs, std::vector<Node*> nodes,std::string mat) : Object(verts, norms, uvs,mat)
{
	
	nodeList = nodes;
	posX = nodes[nextNode]->posX+5;
	posY = 0;
	posZ = nodes[nextNode]->posY -5;
	ldr = new ObjLoader();
	ldr->LoadObj("Models/Cube.obj", true);
	Object* orb1 = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), ldr->getMat());
	Object* orb2 = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), ldr->getMat());
	orbitals.push_back(orb1);
	orbitals.push_back(orb2);

}


EnemyObject::~EnemyObject()
{
}

void EnemyObject::UpdateChildren(double deltaTime) {
	animateTime += deltaTime;
	if (animateTime >= 4) {
		animateTime = 0;
		orb1TranslateX = -50;
		orb1TranslateZ = 50;
		orb2TranslateX = 50;
		orb2TranslateZ = -50;
		keyframe = 0;
	}
	if (animateTime <= 1) {
		if (keyframe != 1) {
			interpOrb1XA = -50;
			interpOrb1XB = -50;
			interpOrb1ZA = 50;
			interpOrb1ZB = -50;

			interpOrb2XA = 50;
			interpOrb2XB = 50;
			interpOrb2ZA = -50;
			interpOrb2ZB = 50;


			orb1MoveX = 0;
			orb1MoveZ = -1;
			orb2MoveX = 0;
			orb2MoveZ = 1;
			keyframe = 1;
		}
	}
	else if (animateTime <= 2) {
		if (keyframe != 2) {

			interpOrb1XA = -50;
			interpOrb1XB = 50;
			interpOrb1ZA = -50;
			interpOrb1ZB = -50;

			interpOrb2XA = 50;
			interpOrb2XB = -50;
			interpOrb2ZA = 50;
			interpOrb2ZB = 50;
			orb1MoveX = 1;
			orb1MoveZ = 0;
			orb2MoveX = -1;
			orb2MoveZ = 0;
			keyframe = 2;
		}
	}
	else if (animateTime <= 3) {
		if (keyframe != 3) {
			interpOrb1XA = 50;
			interpOrb1XB = 50;
			interpOrb1ZA = -50;
			interpOrb1ZB = 50;

			interpOrb2XA = -50;
			interpOrb2XB = -50;
			interpOrb2ZA = 50;
			interpOrb2ZB = -50;

			orb1MoveX = 0;
			orb1MoveZ = 1;
			orb2MoveX = 0;
			orb2MoveZ = -1;
			keyframe = 3;
		}
	}
	else if (animateTime <= 4) {
		if (keyframe != 4) {
			interpOrb1XA = 50;
			interpOrb1XB = -50;
			interpOrb1ZA = 50;
			interpOrb1ZB = 50;

			interpOrb2XA = -50;
			interpOrb2XB = 50;
			interpOrb2ZA = -50;
			interpOrb2ZB = -50;

			orb1MoveX = -1;
			orb1MoveZ = 0;
			orb1MoveX = 1;
			orb1MoveZ = 0;
			keyframe = 4;
		}
	}
	orb1TranslateX += (deltaTime) * (interpOrb1XB - interpOrb1XA);
	orb1TranslateZ += (deltaTime) * (interpOrb1ZB - interpOrb1ZA);
	orb2TranslateX += (deltaTime) * (interpOrb2XB - interpOrb2XA);
	orb2TranslateZ += (deltaTime) * (interpOrb2ZB - interpOrb2ZA);
	orbitals[0]->posX = posX * 10;
	orbitals[0]->posY = posY * 10;
	orbitals[0]->posZ = posZ * 10;
	orbitals[1]->posX = posX * 10;
	orbitals[1]->posY = posY * 10;
	orbitals[1]->posZ = posZ * 10;
}

void EnemyObject::Display() {
	bUV = true;
	texID = Scene::GetTexture("Textures/Steel.bmp");

	Object::Display();

	//glPushMatrix();
	//glTranslatef(0, 0, 0);
	glScalef(0.1,0.1,0.1);
	//glPushMatrix();
	glTranslatef(orb1TranslateX, 150, orb1TranslateZ);
	orbitals[0]->Display();
	glTranslatef(-orb1TranslateX, -150, -orb1TranslateZ);

	//glPopMatrix;

	//glPushMatrix();
	glTranslatef(orb2TranslateX, 150, orb2TranslateZ);
	orbitals[1]->Display();
	glTranslatef(-orb2TranslateX, -150, -orb2TranslateZ);

	//glPopMatrix();
	glScalef(10, 10, 10);
	//glPopMatrix;
}


void EnemyObject::Update(const double& deltaTime) {
	Object::Update(deltaTime);
	//if (!bDone) {
		if ((int)posX != (int)nodeList[nextNode]->posX + 5 || (int)posZ != (int)nodeList[nextNode]->posY - 5) {

			diffx = (nodeList[nextNode]->posX + 5 - posX);
			diffz = (nodeList[nextNode]->posY - 5 - posZ);
			if (diffx != 0) {
				diffx >= 0 ? diffx = 1 : diffx = -1;
			}if (diffz != 0) {
				diffz >= 0 ? diffz = 1 : diffz = -1;
			}
			posX += diffx * 0.1;
			posZ += diffz * 0.1;
		}
		else {
			posX = nodeList[nextNode]->posX + 5;
			posZ = nodeList[nextNode]->posY - 5;
			nextNode++;
			if (nextNode >= nodeList.size()) {
				nextNode = 0;
				posX = nodeList[nextNode]->posX + 5;
				posZ = nodeList[nextNode]->posY - 5;
			}
		}
		UpdateChildren(deltaTime);
	//}
}
