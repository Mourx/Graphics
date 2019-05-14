#include "PumpkinObject.h"


PumpkinObject::PumpkinObject(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Vertex*> uvs, std::string mat) : Object(verts, norms, uvs, mat)
{

}


PumpkinObject::~PumpkinObject()
{
}

void PumpkinObject::HandleKey(unsigned char key, int state, int x, int y)
{
	switch (key)
	{
	case ' ':
		doFlip();
	default:
		break;
	}
}

void PumpkinObject::doFlip() {
	state = 1;
	
}

void PumpkinObject::Update(const double& deltaTime) {
	
	switch (state) {
	case 0:
		speedX = 0;
		speedY = 0;
		speedZ = 0;
		angleIncrease = 0;
		break;
	case 1:
		if (posY >= 25) {
			state = 2;
			angleIncrease = (360 - angle) / posY;
		}
		else {
			speedY = .5;
			angleIncrease = 2;
			angleY = 1;
			angleZ = 1;
			break;
		}
	case 2:
		if (posY <= 0) {
			posY = 0;
			state = 0;
		}
		speedY = -0.5;
		break;
	}

	posX += speedX;
	posY += speedY;
	posZ += speedZ;

	angle += angleIncrease;
}