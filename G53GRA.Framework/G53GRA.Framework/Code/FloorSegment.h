#pragma once
#include "Triangle.h"
class FloorSegment :
	public Triangle
{
public:
	FloorSegment(std::vector<Vertex*> points, Vertex* colour, std::string fileName, int side);
	~FloorSegment();
};

