#pragma once
#include "DisplayableObject.h"
#include "Animation.h"
#include "Input.h"
#include "Vertex.h"

class Tile :
	public DisplayableObject
{
public:
	Tile(std::vector<Vertex*> points, Vertex* colour,double size, std::string fileName);
	~Tile();

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
	Vertex* colour;
	double size = 0;
};

