#pragma once
#include "Object.h"
#include <vector>
#include "Vertex.h"
#include "Node.h"
class EnemyObject :
	public Object
{
public:
	EnemyObject(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Vertex*> uvs, std::vector<Node*> nodes, std::string mat);
	~EnemyObject();

	void Display();
	void Update(const double& deltaTime);

private:
	std::vector<Node*> nodeList;
	int nextNode = 0;
	bool bDone = false;
};

