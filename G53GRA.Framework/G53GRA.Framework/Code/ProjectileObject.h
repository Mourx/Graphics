#pragma once
#include "Object.h"
class ProjectileObject :
	public Object
{
public:
	ProjectileObject(Vertex* position, Vertex* speed,Object* tg);
	~ProjectileObject();
	void Display();

	void ReTarget();
	void Update(const double& deltaTime);

private:
	double speedX, speedY, speedZ;
	double dirX, dirY, dirZ;
	Object* target;
};

