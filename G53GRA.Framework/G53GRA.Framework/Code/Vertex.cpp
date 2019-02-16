#include "Vertex.h"



Vertex::Vertex(float x,float y,float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vertex::Vertex(float x, float y)
{
	this->x = x;
	this->y = y;
	this->z = 0;
}


Vertex::Vertex() {}


Vertex::~Vertex()
{
}
