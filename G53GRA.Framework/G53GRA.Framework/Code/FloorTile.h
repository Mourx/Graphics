#pragma once
#include "DisplayableObject.h"
#include "FloorSegment.h"
#include "MyScene.h"

class FloorTile
{
public:
	FloorTile(std::vector<FloorSegment*> segments, MyScene* scene);
	~FloorTile();
	void AddToScene();
	
	MyScene* scene;
	FloorSegment* left;
	FloorSegment* right;

};

