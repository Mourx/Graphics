#include "PumpkinObject.h"


PumpkinObject::PumpkinObject(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Vertex*> uvs, std::string mat) : Object(verts, norms, uvs, mat)
{

}


PumpkinObject::~PumpkinObject()
{
}

void PumpkinObject::HandleKey(unsigned char key, int state, int x, int y)
{
	// flip when space is pressed
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
	
	// jump up and spin the pumpkin
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
			angleIncrease = 20;
		}
		else {
			speedY = .7;
			angleIncrease = 10;
			angleY = 1;
			angleZ = 1;
			break;
		}
	case 2:
		if (posY <= 0) {
			posY = 0;
			state = 0;
			angle = -angle;
		}
		speedY = -0.7;
		break;
	}

	posX += speedX;
	posY += speedY;
	posZ += speedZ;

	angle += angleIncrease;
}