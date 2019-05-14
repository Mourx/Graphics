#include "TowerObject.h"

#define PI 3.14159265


TowerObject::TowerObject(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Vertex*> uvs, std::string mat, MyScene* scn) : Object(verts,norms,uvs,mat)
{
	scene = scn;
	ObjLoader* ldr = new ObjLoader();
	ldr->LoadObj("Models/Turret_bottom.obj", true);
	turret = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), ldr->getMat());
	turret->texID = Scene::GetTexture("Textures/Steel.bmp");
	turret->setPosition(0, -5, 0);
	this->setAngle(90, 0, 1, 0);
}


TowerObject::~TowerObject()
{
}

	//finds the first enemy, shoots it
EnemyObject* TowerObject::FindTarget() {
	target = scene->getEnemies()[0];
	return target;
}

void TowerObject::Display() {

	//Object Display code but without popping til after drawing all parts
	std::vector<Vertex*> points;
	glPushMatrix();
	glTranslatef(posX, posY, posZ);
	glRotatef(angle, angleX, angleY, angleZ);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texID);
	glEnable(GL_COLOR_MATERIAL);
	glScalef(scaleX, scaleY, scaleZ);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < vertices.size(); i += 3) {
		glColor3f(red, green, blue);
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
	for (int i = 0; i < projs.size(); i++) {
		projs[i]->angle = angle;
		projs[i]->Display();
	}

	turret->Display();

	glPopMatrix();
	
}

void TowerObject::Fire() {
	
	// make it fire alternating from one side of the turret to the other
	bSide = bSide * -1;
	ProjectileObject* proj = new ProjectileObject(new Vertex(sin(angle*PI/180)*2 * bSide, 2,0+cos(angle*PI/180)*2*bSide), new Vertex(1, 1, 1), FindTarget(),this);
	projs.push_back(proj);
	
}

void TowerObject::Update(const double& deltaTime) {
	fireTime += deltaTime;
	if (fireTime >= 2) {
		fireTime = 0;
		Fire();
	}
	// update projectiles, delete if they're finished
	for (int i = 0; i < projs.size(); i++) {
		projs[i]->Update(deltaTime);
		if (projs[i]->isFinished()) {
			delete projs[i];
			projs.erase(projs.begin() + i, projs.begin() + i + 1);
			
		}
	}
	if (target != nullptr) {
		
		//if we have a target, work out the angle to point at it
		double diffx =target->posX - posX;
		double diffz = target->posZ- posZ;
		double totaldiff = sqrt(pow(diffx, 2) + pow(diffz, 2));
		double arctan = atan2(diffz, diffx) * 180 / PI;
		angle = 180 - arctan;
	}
}

