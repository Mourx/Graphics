#pragma once
#include "Object.h"
class PlayerObject :
	public Object
{
public:
	PlayerObject(std::vector<Vertex*> verts, std::vector<Vertex*> norms);
	~PlayerObject();

	void Display();


};

