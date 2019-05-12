#include "TowerObject.h"



TowerObject::TowerObject(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Vertex*> uvs, std::string mat, MyScene* scn) : Object(verts,norms,uvs,mat)
{
	scene = scn;
	ObjLoader* ldr = new ObjLoader();
	ldr->LoadObj("Models/Turret_top.obj", true);
	turret = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), ldr->getMat());
	turret->texID = Scene::GetTexture("Textures/Steel.bmp");
	turret->setPosition(0, 5, 0);
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
	turret->Display();
	glPopMatrix();

}

void TowerObject::Fire() {
	ProjectileObject* proj = new ProjectileObject(new Vertex(posX, posY+5, posZ), new Vertex(1, 1, 1), FindTarget());
	scene->AddObj(proj);
}
void TowerObject::Update(const double& deltaTime) {
	fireTime += deltaTime;
	if (fireTime >= 2) {
		fireTime = 0;
		Fire();
	}

}

