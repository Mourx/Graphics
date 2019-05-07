#pragma once
#include "Object.h"
#include "ObjLoader.h"
class ArmObject :
	public Object
{
public:
	ArmObject(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Vertex*> uvs, std::string mat);
	~ArmObject();
	void Display();
	void Update(const double& deltaTime);
	void setBend(float angle);

private:
	Object * JointTop, *JointMiddle;
	Object * LimbTop, *LimbBottom;
	Object * EndObj;
	ObjLoader* ldr;
	double rotation = 0;
	float angleBig = 0;
	float angleBend = 90;
	float scalefactor = 0.5;
	float angleLittle = 0;
	bool bDirection = 0;
	
};

