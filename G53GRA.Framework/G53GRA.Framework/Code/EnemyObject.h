#pragma once
#include "Object.h"
#include <vector>
#include "Vertex.h"
#include "Node.h"
class EnemyObject :
	public Object
{
public:
	EnemyObject(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Node*> nodes);
	~EnemyObject();

	void Display();
	void Update(const double& deltaTime);

private:
	std::vector<Node*> nodeList;
	int nextNode = 0;
	bool bDone = false;
};

