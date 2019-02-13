#include "FloorSegment.h"



FloorSegment::FloorSegment(std::vector<Vertex*> points, Vertex* colour, std::string fileName, int side) : Triangle(points, colour, fileName, side)
{
}


FloorSegment::~FloorSegment()
{
}
