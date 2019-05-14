#pragma once
#include "Object.h"
#include "EnemyObject.h"
class ProjectileObject :
	public Object
{
public:
	ProjectileObject(Vertex* position, Vertex* speed,Object* tg,Object* p);
	~ProjectileObject();
	void Display();

	void ReTarget();
	void Update(const double& deltaTime);
	bool isFinished();

private:
	double speedX, speedY, speedZ;
	double dirX, dirY, dirZ;
	Object* target;
	Object* parent;
	bool bFinished = false;
	Object* missile;
};

