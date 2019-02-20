#pragma once
#include "Object.h"
class PlayerObject :
	public Object
{
public:
	PlayerObject(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Vertex*> uvs, std::string mat);
	~PlayerObject();

	void Display();


};

