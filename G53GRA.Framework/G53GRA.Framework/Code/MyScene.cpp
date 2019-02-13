#include "MyScene.h"
#include "Triangle.h"
#include "FloorTile.h"
#include "Light.h"

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{

}

void MyScene::AddObj(DisplayableObject* obj) {
	AddObjectToScene(obj);
}

void MyScene::Initialise()
{
	Light* light = new Light();
	AddObjectToScene(light);
	std::vector<Vertex*> points;
	points.push_back(new Vertex(0.f, -10.f, 0.f));
	points.push_back(new Vertex(20.f, -10.f, 0.f));
	points.push_back(new Vertex(0.f, -10.f, -20.f));

	//AddObjectToScene(new Triangle(points,new Vertex(200,0,0), "Textures/Tex1.bmp",0));
	std::vector<FloorSegment*> segments;
	segments.push_back(new FloorSegment(points, new Vertex(200, 0, 0), "Textures/Tex1.bmp", 0));
	points.clear();

	points.push_back(new Vertex(20.f, -10.f, -20.f));
	points.push_back(new Vertex(0.f, -10.f, -20.f));
	points.push_back(new Vertex(20.f, -10.f, 0.f));

	//AddObjectToScene(new Triangle(points, new Vertex(0,200,0), "Textures/Tex1.bmp",1));
	segments.push_back(new FloorSegment(points, new Vertex(200, 0, 0), "Textures/Tex1.bmp", 1));
	FloorTile* floorTile = new FloorTile(segments, this);
	floorTile->AddToScene();
	points.clear();

	

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	

}

void MyScene::Projection()
{
	GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
	gluPerspective(60.0, aspect, 1.0, 1000.0);
}
