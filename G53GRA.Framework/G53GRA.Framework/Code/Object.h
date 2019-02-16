#pragma once
#include "DisplayableObject.h"
#include "Animation.h"
#include "Vertex.h"
class Object :
	public DisplayableObject,
	public Animation
{
public:
	Object();
	Object(std::vector<Vertex*> verts, std::vector<Vertex*> norms);
	~Object();
	
	void Display();
	void Update(const double& deltaTime);
	void HandleKey(unsigned char key, int state, int x, int y);

	std::vector<Vertex*> vertices;
	std::vector<Vertex*> uvs;
	std::vector<Vertex*> normals;

	double posX, posY, posZ;
};

