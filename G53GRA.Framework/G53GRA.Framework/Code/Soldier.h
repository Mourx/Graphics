#pragma once
#include "DisplayableObject.h"
#include "Animation.h"
#include "Input.h"
#include "Vertex.h"
#include "Node.h"

class Soldier :
	public DisplayableObject
{
public:
	Soldier(std::vector<Vertex*> points, Vertex* colour, std::string fileName, int side);
	~Soldier();

	void Display();
	void Update(const double& deltaTime);
	void HandleKey(unsigned char key, int state, int x, int y);

protected:
	std::vector<Node*> nodes;
private:
	float xrot, yrot, zrot;
	float scale;
	std::vector<Vertex*> points;
	std::string fileName;
	int side;
	Vertex* colour;
};

