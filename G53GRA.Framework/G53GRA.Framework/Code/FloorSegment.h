#pragma once
#include "c:\Users\Joel\Documents\Graphics\Graphics\G53GRA.Framework\G53GRA.Framework\Code\Triangle.h"
class FloorSegment :
	public Triangle
{
public:
	FloorSegment(std::vector<Vertex*> points, Vertex* colour, std::string fileName, int side);
	~FloorSegment();
};

