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

EnemyObject* TowerObject::FindTarget() {
	target = scene->getEnemies()[0];
	return target;
}

void TowerObject::Display() {
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
	
	bSide = bSide * -1;
	ProjectileObject* proj = new ProjectileObject(new Vertex(2 * bSide, 2,0), new Vertex(1, 1, 1), FindTarget(),this);
	projs.push_back(proj);
	
}

void TowerObject::Update(const double& deltaTime) {
	fireTime += deltaTime;
	if (fireTime >= 2) {
		fireTime = 0;
		Fire();
	}
	for (int i = 0; i < projs.size(); i++) {
		projs[i]->Update(deltaTime);
		if (projs[i]->isFinished()) {
			delete projs[i];
			projs.erase(projs.begin() + i, projs.begin() + i + 1);
			
		}
	}
	if (target != nullptr) {
		
		double diffx =target->posX - posX;
		double diffz = target->posZ- posZ;
		double totaldiff = sqrt(pow(diffx, 2) + pow(diffz, 2));
		//double arcsin = asin(-diffz / totaldiff) * 180 / PI;
		double arctan = atan2(diffz, diffx) * 180 / PI;
		//double inversesin = (arcsin >= 0 ? 180-arcsin : 0-arcsin);
		

		angle = 180 - arctan;
	}
}

