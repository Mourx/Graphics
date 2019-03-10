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
#include "SkyBox.h"

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{

}

void MyScene::AddObj(DisplayableObject* obj) {
	objects.push_back(obj);
}

void MyScene::Update(const double& deltaTime)
{
	Animation* animated_obj;
	// Update camera/view
	this->GetCamera()->Update(deltaTime);
	// Iterate through objects to update animations
	for (int i = 0; i<objects.size(); i++)
	{
		DisplayableObject* obj = objects[i];
		animated_obj = dynamic_cast<Animation*>(obj); // Cast to animation
		if (animated_obj != NULL) // If cast successful
			animated_obj->Update(deltaTime); // Call update sequence for obj
	}
	Clean();
	
}

Camera* MyScene::GetCam() {
	return GetCamera();
}

void MyScene::Clean() {
	for (int i = 0; i < objects.size(); i++)
	{
		ProjectileObject* animated_obj = dynamic_cast<ProjectileObject*>(objects[i]);
		if (animated_obj != NULL) {
			if (animated_obj->isFinished()) {
				delete objects[i];
				objects.erase(objects.begin()+i,objects.begin()+i+1);
			}
		}

	}
}

void MyScene::Draw() {
	// Clear colour and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Update based on window details (also sets initial projection properties)
	Reshape(windowWidth, windowHeight);
	// Reset MODELVIEW matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Setup viewing properties
	this->GetCamera()->SetupCamera();
	// Display all objects in the Scene
	for (int i = 0; i < objects.size(); i++)
	{
		DisplayableObject* obj = objects[i];
		if(obj != nullptr)
			objects[i]->Display();
		
	}
	// Zealous reset of MODELVIEW matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Dump silent GL errors into console output
	CheckGLError();
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
	AddObj(light);

	light = new Light(new Vertex(-50, 60, 10), GL_LIGHT1);
	AddObj(light);
	std::vector<Vertex*> points;
	points.push_back(new Vertex(0.f, -10.f, 0.f));
	points.push_back(new Vertex(20.f, -10.f, 0.f));
	points.push_back(new Vertex(0.f, -10.f, -20.f));

	std::vector<Node*> corners;
	corners = InitialiseNodes(corners);

	ObjLoader* ldr = new ObjLoader();
	ldr->LoadObj("Models/Tower.obj",true);
	TowerObject* obj = new TowerObject(ldr->getVerts(),ldr->getNorms(),ldr->getUVs(),ldr->getMat(),this);
	//std::vector<Vertex*> vertices = ldr->getVerts();
	//std::vector<Vertex*> uvs = ldr->getUVs();
	//std::vector<Vertex*> normals = ldr->getNorms();
	AddObj(obj);

	//SkyBox
	ldr = new ObjLoader();
	ldr->LoadObj("Models/Cube.obj",true);
	SkyBox* sky = new SkyBox(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), "Textures/Sky.bmp");
	AddObj(sky);

	//Player
	ldr = new ObjLoader();
	ldr->LoadObj("Models/Man.obj",false);
	PlayerObject* player = new PlayerObject(ldr->getVerts(), ldr->getNorms(),ldr->getUVs(), ldr->getMat());
	AddObj(player);

	//Monster
	ldr = new ObjLoader();
	ldr->LoadObj("Models/Monster.obj",true);
	EnemyObject* enemy = new EnemyObject(ldr->getVerts(), ldr->getNorms(),ldr->getUVs(),corners, ldr->getMat());
	AddObj(enemy);
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