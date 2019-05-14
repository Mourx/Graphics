#include "EnemyObject.h"



EnemyObject::EnemyObject(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Vertex*> uvs, std::vector<Node*> nodes,std::string mat,int light) : Object(verts, norms, uvs,mat)
{
	
	nodeList = nodes;
	posX = nodes[nextNode]->posX+5;
	posY = 20;
	posZ = nodes[nextNode]->posY -5;

	// initialise orbitals and positions
	ldr = new ObjLoader();
	ldr->LoadObj("Models/Cube.obj", true);
	Object* orb1 = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), ldr->getMat());
	Object* orb2 = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), ldr->getMat());
	orb1->texID = Scene::GetTexture("Textures/Steel.bmp");
	orb2->texID = Scene::GetTexture("Textures/Steel.bmp");
	orbitals.push_back(orb1);
	orbitals.push_back(orb2);
	orbitals[0]->setPosition(0, 130, 0);
	orbitals[1]->setPosition(0, 130, 0);
	

	//initialise limbs and positions
	ldr->LoadObj("Models/Robot_Limb.obj", true);
	leftArm = new ArmObject(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), ldr->getMat());
	rightArm = new ArmObject(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), ldr->getMat());
	leftLeg = new LegObject(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), ldr->getMat());
	rightLeg = new LegObject(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), ldr->getMat());
	
	rightArm->posX = 5;
	rightArm->posY = 10;
	rightArm->posZ = 0;

	rightLeg->posX = 4;
	rightLeg->posY = 2;
	rightLeg->posZ = 0;

	leftLeg->posX = -4;
	leftLeg->posY = 2;
	leftLeg->posZ = 0;

	leftArm->posX = -5;
	leftArm->posY = 10;
	leftArm->posZ = 0;
	
	leftArm->setBend(15);
	rightArm->setBend(-45);
	leftLeg->setBend(300);
	rightLeg->setBend(240);

	angle = 0;

	//initialise spotlight
	spotLight = new Light(new Vertex(0, 10, -5), GL_LIGHT0 + light);
}


EnemyObject::~EnemyObject()
{
}

void EnemyObject::UpdateChildren(double deltaTime) {

	//animate the orbital blocks, using time based keyframes
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
	//modify orbital positions based on time
	orbitals[0]->posX += (deltaTime) * (interpOrb1XB - interpOrb1XA);
	orbitals[0]->posZ += (deltaTime) * (interpOrb1ZB - interpOrb1ZA);
	orbitals[1]->posX += (deltaTime) * (interpOrb2XB - interpOrb2XA);
	orbitals[1]->posZ += (deltaTime) * (interpOrb2ZB - interpOrb2ZA);
	

	//update limbs
	leftArm->Update(deltaTime);
	rightArm->Update(deltaTime);
	leftLeg->Update(deltaTime);
	rightLeg->Update(deltaTime);
	
}

void EnemyObject::Display() {

	//not using default Object Draw() to ensure the limbs are 
	// rotated correctly (angle would be popped otherwise)
	glPushMatrix();
	bUV = true;
	texID = Scene::GetTexture("Textures/Steel.bmp");
	Object::angleY = 1.0;
	std::vector<Vertex*> points;

	posY = 20;
	scaleX = 2;
	scaleY = 1.2;
	scaleZ = 2;
	glScalef(scaleX, scaleY, scaleZ);

	glTranslatef(posX, posY, posZ);
	glRotatef(angle, angleX, angleY, angleZ);
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID);
	glColor3f(red, green, blue);
	glEnable(GL_COLOR_MATERIAL);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < vertices.size(); i += 3) {
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

	//show spotlight
	spotLight->Display();

	//draw orbitals
	glPushMatrix();
	glScalef(0.1, 0.1, 0.1);
	orbitals[0]->Display();
	glPopMatrix();
	glPushMatrix();
	glScalef(0.1, 0.1, 0.1);
	orbitals[1]->Display();
	glPopMatrix();
	 
	//make sure colour is correct (for flash)
	leftArm->setColour(red, green, blue);
	leftLeg->setColour(red, green, blue);
	rightArm->setColour(red, green, blue);
	rightLeg->setColour(red, green, blue);

	//display limbs
	leftArm->Display();
	leftLeg->Display();
	rightArm->Display();
	rightLeg->Display();

	//reset colour since it doesn't pop
	glColor3f(1, 1, 1);
	glPopMatrix();
}


void EnemyObject::Update(const double& deltaTime) {

	//update path navigation using difference to next node x,z position
	// nodes use x and y because they are flat
	Object::Update(deltaTime);
	//move toward a node
	if ((int)posX != (int)nodeList[nextNode]->posX + 5 || (int)posZ != (int)nodeList[nextNode]->posY - 5) {

		diffx = (nodeList[nextNode]->posX + 5 - posX);
		diffz = (nodeList[nextNode]->posY - 5 - posZ);
		if (diffx != 0) {
			diffx >= 0 ? diffx = 1 : diffx = -1;
		}if (diffz != 0) {
			diffz >= 0 ? diffz = 1 : diffz = -1;
		}
		posX += diffx * 0.3;
		posZ += diffz * 0.3;
	}
	//start to turn if at a node, acquire new node target
	else {
		bRotate = true;
		posX = nodeList[nextNode]->posX + 5;
		posZ = nodeList[nextNode]->posY - 5;
		nextNode++;

		//if at end of the path, teleport to beginning
		if (nextNode >= nodeList.size()) {
			nextNode = 0;
			posX = nodeList[nextNode]->posX + 5;
			posZ = nodeList[nextNode]->posY - 5;
			angle = 0;
		}
	}
	//if turning, work out which way to turn based on where next node is
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
		angle += incdir*1.5;
		if (angle == 360) angle = 0;
		if (angle == targetangle) {
			bRotate = false;
		}
	}
	//update the orbitals and limbs
	UpdateChildren(deltaTime);

	//flash if hit by a projectile
	flashtime += deltaTime;
	if (flashtime >= 0.5) {
		red = 1;
		green = 1;
		blue = 1;
		flashtime = 0;
	}
}

	// when hit, briefly flash red
void EnemyObject::Flash(const double& deltaTime) {
	red = 1;
	green = 0.2;
	blue = 0.2;
}

	// allows setting robots start point
void EnemyObject::setNextNode(int node) {
	nextNode = node;
	posX = nodeList[nextNode]->posX;
	posZ = nodeList[nextNode]->posY;
}