#include "MyScene.h"
#include "Triangle.h"
#include "FloorTile.h"
#include "Light.h"
#include "Tile.h"
#include "Soldier.h"
#include "Path.h"
#include "ObjLoader.h"
#include "Object.h"
#include "PlayerObject.h"
#include "TowerObject.h"

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{

}

void MyScene::AddObj(DisplayableObject* obj) {
	AddObjectToScene(obj);
}

std::vector<Node*> InitialiseNodes(std::vector<Node*> crnrs) {
	crnrs.push_back(new Node(-10, 100));
	crnrs.push_back(new Node(-10, 60));
	crnrs.push_back(new Node(-70, 60));
	crnrs.push_back(new Node(-70, -60));
	crnrs.push_back(new Node(0, -60));
	crnrs.push_back(new Node(0, 0));
	crnrs.push_back(new Node(40, 0));
	crnrs.push_back(new Node(40, 70));
	crnrs.push_back(new Node(80, 70));
	crnrs.push_back(new Node(80, 100));
	return crnrs;
}

void MyScene::Initialise()
{
	Light* light = new Light(new Vertex(50,60,10),GL_LIGHT0);
	AddObjectToScene(light);

	light = new Light(new Vertex(-50, 60, 10), GL_LIGHT1);
	AddObjectToScene(light);
	std::vector<Vertex*> points;
	points.push_back(new Vertex(0.f, -10.f, 0.f));
	points.push_back(new Vertex(20.f, -10.f, 0.f));
	points.push_back(new Vertex(0.f, -10.f, -20.f));

	std::vector<Node*> corners;
	corners = InitialiseNodes(corners);

	ObjLoader* ldr = new ObjLoader();
	ldr->LoadObj("Models/cube.obj",true);
	TowerObject* obj = new TowerObject(ldr->getVerts(),ldr->getNorms(),ldr->getUVs(),ldr->getMat(),this);
	//std::vector<Vertex*> vertices = ldr->getVerts();
	//std::vector<Vertex*> uvs = ldr->getUVs();
	//std::vector<Vertex*> normals = ldr->getNorms();
	AddObjectToScene(obj);

	//Player
	ldr = new ObjLoader();
	ldr->LoadObj("Models/Man.obj",false);
	PlayerObject* player = new PlayerObject(ldr->getVerts(), ldr->getNorms(),ldr->getUVs(), ldr->getMat());
	AddObjectToScene(player);

	//Monster
	ldr = new ObjLoader();
	ldr->LoadObj("Models/Monster.obj",false);
	EnemyObject* enemy = new EnemyObject(ldr->getVerts(), ldr->getNorms(),ldr->getUVs(),corners, ldr->getMat());
	AddObjectToScene(enemy);
	enemies.push_back(enemy);
	
	
	//AddObjectToScene(new Triangle(points,new Vertex(200,0,0), "Textures/Tex1.bmp",0));
	std::vector<FloorSegment*> segments;
	segments.push_back(new FloorSegment(points, new Vertex(100, 100, 0), "Textures/Tex1.bmp", 0));
	points.clear();

	points.push_back(new Vertex(20.f, -10.f, -20.f));
	points.push_back(new Vertex(0.f, -10.f, -20.f));
	points.push_back(new Vertex(20.f, -10.f, 0.f));

	//AddObjectToScene(new Triangle(points, new Vertex(0,200,0), "Textures/Tex1.bmp",1));
	segments.push_back(new FloorSegment(points, new Vertex(100, 100, 0), "Textures/Tex1.bmp", 1));
	FloorTile* floorTile = new FloorTile(segments, this);
	floorTile->AddToScene();
	points.clear();

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			points.push_back(new Vertex(-100.f + 10 * j, 0.f, -90.f + 10 * i));
			points.push_back(new Vertex(-90.f + 10 * j, 0.f, -90.f + 10 * i));
			points.push_back(new Vertex(-90.f + 10 * j, 0.f, - 100.f + 10 * i));
			points.push_back(new Vertex(-100.f + 10 * j, 0.f, -100.f + 10 * i));
			Tile* tile = new Tile(points, new Vertex(255, 255, 255), "Textures/Grass.bmp");
			AddObj(tile);
			points.clear();

		}
	}
	points.push_back(new Vertex(30.f, 0.f, 0.f));
	points.push_back(new Vertex(40.f, 0.f, 0.f));
	points.push_back(new Vertex(40.f,10.f, 0.f));
	points.push_back(new Vertex(30.f, 10.f, 0.f));
	Tile* tile = new Tile(points, new Vertex(255, 255, 255), "Textures/science_lab.bmp");
	AddObj(tile);
	points.clear();

	points.push_back(new Vertex(30.f, -10.f, 0.f));
	points.push_back(new Vertex(40.f, -10.f, 0.f));
	points.push_back(new Vertex(40.f, 0.f, 0.f));
	points.push_back(new Vertex(30.f, 0.f, 0.f));
	Soldier* soldier = new Soldier(points, new Vertex(255, 255, 255), "Textures/monster_nose_squid.bmp",1);
	AddObj(soldier);
	points.clear();
	Path* path = new Path(corners, this);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	

}

void MyScene::Projection()
{
	GLdouble aspect = static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight);
	gluPerspective(60.0, aspect, 1.0, 1000.0);
}


std::vector<EnemyObject*> MyScene::getEnemies() {
	return enemies;
}