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
	Object(std::vector<Vertex*> verts, std::vector<Vertex*> norms, std::vector<Vertex*> uvs, std::string mat);
	~Object();
	
	void Display();
	void Update(const double& deltaTime);
	void HandleKey(unsigned char key, int state, int x, int y);
	void setPosition(float x, float y, float z);
	void setAngle(float a, float x, float y, float z);
	void setScale(float x, float y, float z);

	std::vector<Vertex*> vertices;
	std::vector<Vertex*> uvs;
	std::vector<Vertex*> normals;

	double posX, posY, posZ;
	double scaleX = 1, scaleY = 1, scaleZ = 1;
	bool bUV = true;
	std::string material;
	int texID = Scene::GetTexture("Textures/cube.bmp");
	double angle = 0, angleX = 0, angleY = 0, angleZ = 0;
};

