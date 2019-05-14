#pragma once
#include "Object.h"
class PumpkinObject :
	public Object,
	public Input
{
public:
	PumpkinObject(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Vertex*> uvs, std::string mat);
	~PumpkinObject();

	void HandleKey(unsigned char key, int state, int x, int y);
	void Update(const double& deltaTime);
	void doFlip();
private:
	int state = 0;
	double speedX =0, speedY= 0, speedZ =0;
	double angleIncrease;
};

