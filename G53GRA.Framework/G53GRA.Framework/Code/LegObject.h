#pragma once
#include "Object.h"
#include "ObjLoader.h"

class LegObject :
	public Object
{
public:
	LegObject(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Vertex*> uvs, std::string mat);
	~LegObject();

	void Display();
	void Update(const double& deltaTime);
	void setBend(float angle);

private:
	Object * JointTop, *JointMiddle;
	Object * LimbTop, *LimbBottom;
	Object * EndObj;
	ObjLoader* ldr;
	double rotation = 0;
	float angleBig = 270;
	float angleBend =270;
	float scalefactor = 0.5;
	float angleLittle = 0;
	bool bDirection = 0;

};

