#pragma once
#include "Node.h"
#include "Tile.h"
#include "MyScene.h"

class Path
{
public:
	Path(std::vector<Node*> crnrs, MyScene* scn);
	~Path();
	void FixPath();
	void AddPathToScene();

protected:
	MyScene* scene;
	std::vector<Node*> corners;
	std::vector<Tile*> tiles;
};

