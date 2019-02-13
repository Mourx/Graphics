#include "FloorTile.h"



FloorTile::FloorTile(std::vector<FloorSegment*> segments, MyScene* scene)
{
	this->scene = scene;
	left = segments[0];
	right = segments[1];
}


FloorTile::~FloorTile()
{
}

void FloorTile::AddToScene() {
	scene->AddObj(left);
	scene->AddObj(right);
}
