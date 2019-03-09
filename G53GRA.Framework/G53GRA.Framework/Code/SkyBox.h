#pragma once
#include "Object.h"
#include "Node.h"
class SkyBox :
	public Object
{
public:
	SkyBox(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Vertex*> uvs, std::string mat);
	~SkyBox();

	void Display();

};

