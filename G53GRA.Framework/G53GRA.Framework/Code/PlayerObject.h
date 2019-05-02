#pragma once
#include "Object.h"
class CampfireObject :
	public Object
{
public:
	CampfireObject(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Vertex*> uvs, std::string mat);
	~CampfireObject();

	void Display();


};

