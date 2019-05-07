#pragma once
#include "Object.h"
#include <vector>
#include "Vertex.h"
#include "Node.h"
#include "ObjLoader.h"
#include "ArmObject.h"
#include "LegObject.h"

class EnemyObject :
	public Object
{
public:
	EnemyObject(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Vertex*> uvs, std::vector<Node*> nodes, std::string mat);
	~EnemyObject();

	void Display();
	void Update(const double& deltaTime);
	void UpdateChildren(double deltaTime);
private:
	std::vector<Node*> nodeList;
	int nextNode = 0;
	double diffx = 0;
	double diffz = 0;
	bool bDone = false;
	std::vector<Object*> orbitals;
	ArmObject* leftArm;
	ArmObject* rightArm;
	LegObject* leftLeg;
	LegObject* rightLeg;
	ObjLoader* ldr;
	double animateTime = 0;
	double orb1MoveX = 0, orb1MoveZ = 0, orb2MoveX = 0, orb2MoveZ = 0;
	double orb1TranslateX = -50, orb1TranslateZ = 50, orb2TranslateX = 50, orb2TranslateZ = -50;
	double interpOrb1XA, interpOrb1XB, interpOrb1ZA, interpOrb1ZB;
	double interpOrb2XA, interpOrb2XB, interpOrb2ZA, interpOrb2ZB;
	double keyframe = 1.0;
	
};

