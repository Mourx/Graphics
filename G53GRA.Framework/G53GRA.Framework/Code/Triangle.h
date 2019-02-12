#pragma once
#include "DisplayableObject.h"
#include "Animation.h"
#include "Input.h"
#include "Vertex.h"

class Triangle :
	public DisplayableObject,
	public Animation,
	public Input
{
public:
	Triangle(std::vector<Vertex*> points,Vertex* colour,std::string fileName,int side);
	~Triangle() {};

	void Display();
	void Update(const double& deltaTime);
	void HandleKey(unsigned char key, int state, int x, int y);

	void HandleSpecialKey(int key, int state, int x, int y) {}
	void HandleMouse(int button, int state, int x, int y) {}
	void HandleMouseDrag(int x, int y) {}
	void HandleMouseMove(int x, int y) {}

private:
	float xrot, yrot, zrot;
	float scale;
	std::vector<Vertex*> points;
	std::string fileName;
	int side;
	Vertex* colour;
};

