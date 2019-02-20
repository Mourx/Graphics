#include "EnemyObject.h"



EnemyObject::EnemyObject(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Vertex*> uvs, std::vector<Node*> nodes,std::string mat) : Object(verts, norms, uvs,mat)
{
	
	nodeList = nodes;
	posX = nodes[nextNode]->posX+5;
	posY = 0;
	posZ = nodes[nextNode]->posY -5;
}


EnemyObject::~EnemyObject()
{
}

void EnemyObject::Display() {
	bUV = false;
	Object::Display();
}


void EnemyObject::Update(const double& deltaTime) {
	Object::Update(deltaTime);
	//if (!bDone) {
		if ((int)posX != (int)nodeList[nextNode]->posX + 5 || (int)posZ != (int)nodeList[nextNode]->posY - 5) {

			double diffx = (nodeList[nextNode]->posX + 5 - posX);
			double diffy = (nodeList[nextNode]->posY - 5 - posZ);
			if (diffx != 0) {
				diffx >= 0 ? diffx = 1 : diffx = -1;
			}if (diffy != 0) {
				diffy >= 0 ? diffy = 1 : diffy = -1;
			}
			posX += diffx * 0.1;
			posZ += diffy * 0.1;
		}
		else {
			posX = nodeList[nextNode]->posX + 5;
			posZ = nodeList[nextNode]->posY - 5;
			nextNode++;
			if (nextNode >= nodeList.size()) {
				nextNode = 0;
				posX = nodeList[nextNode]->posX + 5;
				posZ = nodeList[nextNode]->posY - 5;
			}
		}
	//}
}
