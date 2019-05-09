#include "EnemyObject.h"



EnemyObject::EnemyObject(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Vertex*> uvs, std::vector<Node*> nodes,std::string mat) : Object(verts, norms, uvs,mat)
{
	
	nodeList = nodes;
	posX = nodes[nextNode]->posX+5;
	posY = 20;
	posZ = nodes[nextNode]->posY -5;
	ldr = new ObjLoader();
	ldr->LoadObj("Models/Cube.obj", true);
	Object* orb1 = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), ldr->getMat());
	Object* orb2 = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), ldr->getMat());
	orb1->texID = Scene::GetTexture("Textures/Steel.bmp");
	orb2->texID = Scene::GetTexture("Textures/Steel.bmp");
	orbitals.push_back(orb1);
	orbitals.push_back(orb2);
	orbitals[0]->posY = 80;
	orbitals[1]->posY = 80;
	ldr->LoadObj("Models/Robot_Limb.obj", true);
	leftArm = new ArmObject(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), ldr->getMat());
	rightArm = new ArmObject(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), ldr->getMat());
	leftLeg = new LegObject(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), ldr->getMat());
	rightLeg = new LegObject(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), ldr->getMat());
	
	rightArm->posX = 5;
	rightArm->posY = 10;
	rightArm->posZ = 0;

	rightLeg->posX = 2;
	rightLeg->posY = 2;
	rightLeg->posZ = 0;

	leftLeg->posX = -4;
	leftLeg->posY = 2;
	leftLeg->posZ = 0;

	leftArm->posX = -6;
	leftArm->posY = 10;
	leftArm->posZ = 0;
	
	leftArm->setBend(15);
	rightArm->setBend(-45);
	leftLeg->setBend(300);
	rightLeg->setBend(240);

	angle = 270;
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
	orbitals[0]->posX += (deltaTime) * (interpOrb1XB - interpOrb1XA);
	orbitals[0]->posZ += (deltaTime) * (interpOrb1ZB - interpOrb1ZA);
	orbitals[1]->posX += (deltaTime) * (interpOrb2XB - interpOrb2XA);
	orbitals[1]->posZ += (deltaTime) * (interpOrb2ZB - interpOrb2ZA);
	

	
	leftArm->Update(deltaTime);
	rightArm->Update(deltaTime);
	leftLeg->Update(deltaTime);
	rightLeg->Update(deltaTime);
	
}

void EnemyObject::Display() {
	glPushMatrix();
	bUV = true;
	texID = Scene::GetTexture("Textures/Steel.bmp");
	Object::angleY = 1.0;
	std::vector<Vertex*> points;



	glTranslatef(posX, posY, posZ);
	glRotatef(angle, angleX, angleY, angleZ);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID);
	glScalef(scaleX, scaleY, scaleZ);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < vertices.size(); i += 3) {
		glColor3f(1, 1, 1);
		glNormal3f(normals[i]->x, normals[i]->y, normals[i]->z);
		points.push_back(vertices[i]);
		points.push_back(vertices[i + 1]);
		points.push_back(vertices[i + 2]);
		if (bUV) glTexCoord2f(uvs[i]->x, uvs[i]->y);
		glVertex3f(points[0]->x * 4, points[0]->y * 4, points[0]->z * 4);
		if (bUV) glTexCoord2f(uvs[i + 1]->x, uvs[i + 1]->y);
		glVertex3f(points[1]->x * 4, points[1]->y * 4, points[1]->z * 4);
		if (bUV) glTexCoord2f(uvs[i + 2]->x, uvs[i + 2]->y);
		glVertex3f(points[2]->x * 4, points[2]->y * 4, points[2]->z * 4);


		points.clear();

	}

	glEnd();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);


	glPushMatrix();
	glScalef(0.1, 0.1, 0.1);

	//glTranslatef(orb1TranslateX, 150, orb1TranslateZ);
	orbitals[0]->Display();

	glPopMatrix();

	glPushMatrix();
	glScalef(0.1, 0.1, 0.1);

	//glTranslatef(orb2TranslateX, 150, orb2TranslateZ);
	orbitals[1]->Display();
	glPopMatrix();
	 
	
	leftArm->Display();
	leftLeg->Display();
	rightArm->Display();
	rightLeg->Display();
	glPopMatrix();
}


void EnemyObject::Update(const double& deltaTime) {
	Object::Update(deltaTime);
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
		bRotate = true;
		posX = nodeList[nextNode]->posX + 5;
		posZ = nodeList[nextNode]->posY - 5;
		nextNode++;
		if (nextNode >= nodeList.size()) {
			nextNode = 0;
			posX = nodeList[nextNode]->posX + 5;
			posZ = nodeList[nextNode]->posY - 5;
		}
	}
	if (bRotate) {
		diffx = (nodeList[nextNode]->posX + 5 - posX);
		diffz = (nodeList[nextNode]->posY - 5 - posZ);
		if (diffx != 0) {
			diffx >= 0 ? (diffx = 1, targetangle <=90 ? targetangle = -90: targetangle = 270) : (diffx = -1,targetangle = 90);
			
		}if (diffz != 0) {
			diffz >= 0 ? (diffz = 1, targetangle>0 ? targetangle = 180:targetangle = -180) : (diffz = -1, targetangle = 0);
		}
		float incdir = 0;
		if(angle - targetangle >= 0){
			if (angle > 180) {
				incdir = 1;
			}
			else {
				incdir = -1;
			}
		}
		else {
			incdir = 1;
		}
		angle += incdir;
		if (angle == 360) angle = 0;
		if (angle == targetangle) {
			bRotate = false;
		}
	}
	UpdateChildren(deltaTime);
}
