#include "TowerObject.h"



TowerObject::TowerObject(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Vertex*> uvs, std::string mat, MyScene* scn) : Object(verts,norms,uvs,mat)
{
	scene = scn;

}


TowerObject::~TowerObject()
{
}

EnemyObject* TowerObject::FindTarget() {
	target = scene->getEnemies()[0];
	return target;
}

void TowerObject::Fire() {
	ProjectileObject* proj = new ProjectileObject(new Vertex(posX, posY+10, posZ), new Vertex(1, 1, 1), FindTarget());
	scene->AddObj(proj);
}
void TowerObject::Update(const double& deltaTime) {
	fireTime += deltaTime;
	if (fireTime >= 1) {
		fireTime = 0;
		//Fire();
	}

}

