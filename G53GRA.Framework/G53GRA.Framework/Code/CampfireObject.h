#pragma once
#include "Object.h"
#include "Light.h"

class CampfireObject :
	public Object
{
public:
	CampfireObject(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Vertex*> uvs, std::string mat);
	~CampfireObject();

	void Display();
	void Update(const double& deltaTime);
private:
	Light* light;
	Light* light2;
	Light* light3;
};

