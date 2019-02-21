#pragma once
#include "Object.h"
#include "MyScene.h"
#include "ProjectileObject.h"
class TowerObject :
	public Object
{
public:
	TowerObject(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Vertex*> uvs, std::string mat, MyScene* scn);
	~TowerObject();

	void Fire();
	EnemyObject* FindTarget();
	void Update(const double& deltaTime);

private:
	double damage = 1;
	MyScene* scene;
	EnemyObject* target;
	double fireTime = 0;
};

