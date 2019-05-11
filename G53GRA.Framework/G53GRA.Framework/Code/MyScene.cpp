#include "MyScene.h"
#include "Triangle.h"
#include "FloorTile.h"
#include "Light.h"
#include "Tile.h"
#include "Soldier.h"
#include "Path.h"
#include "ObjLoader.h"
#include "Object.h"
#include "CampfireObject.h"
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
	Light* light = new Light(new Vertex(-40,100,0),GL_LIGHT0);
	
	//AddObj(light);

	
	//AddObj(light);
	std::vector<Vertex*> points;
	points.push_back(new Vertex(0.f, -10.f, 0.f));
	points.push_back(new Vertex(20.f, -10.f, 0.f));
	points.push_back(new Vertex(0.f, -10.f, -20.f));

	std::vector<Node*> corners;
	corners = InitialiseNodes(corners);

	ObjLoader* ldr = new ObjLoader();
	ldr->LoadObj("Models/Tower.obj",true);
	TowerObject* obj = new TowerObject(ldr->getVerts(),ldr->getNorms(),ldr->getUVs(),ldr->getMat(),this);
	obj->texID = GetTexture("Textures/Log.bmp");
	//std::vector<Vertex*> vertices = ldr->getVerts();
	//std::vector<Vertex*> uvs = ldr->getUVs();
	//std::vector<Vertex*> normals = ldr->getNorms();
	AddObj(obj);

	//SkyBox
	ldr = new ObjLoader();
	ldr->LoadObj("Models/SkyBox.obj",true);
	SkyBox* sky = new SkyBox(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), "Textures/space2.bmp");
	AddObj(sky);

	//house
	//ldr = new ObjLoader();
	//ldr->LoadObj("Models/cottage_obj.obj", true);
	//Object* house = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), "Textures/cottage_diffuse.bmp");
	//house->texID = GetTexture("Textures/cottage_diffuse.bmp");
	//AddObj(house);

	//hedges
	ldr = new ObjLoader();
	ldr->LoadObj("Models/hedge.obj", true);
	for (int i = 0; i < 4; i++) {
		Object* hedge = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), "Textures/hedge.bmp");
		hedge->texID = GetTexture("Textures/hedge.bmp");
		hedge->setPosition(100, -5, i*50-70);
		hedge->setScale(1.85, 1, 1);
		hedge->setAngle(90, 0, 1, 0);
		//hedge->setScale(0.1, 0.1, 0.1);
		AddObj(hedge);
	}
	for (int i = 0; i < 4; i++) {
		Object* hedge = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), "Textures/hedge.bmp");
		hedge->texID = GetTexture("Textures/hedge.bmp");
		hedge->setPosition(i * 48 - 70, -5, -97);
		hedge->setScale(1.75, 1, 1);
		hedge->setAngle(0, 0, 1, 0);
		//hedge->setScale(0.1, 0.1, 0.1);
		AddObj(hedge);
	}
	for (int i = 0; i < 4; i++) {
		Object* hedge = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), "Textures/hedge.bmp");
		hedge->texID = GetTexture("Textures/hedge.bmp");
		hedge->setPosition(-98, -5, i * 50 - 70);
		hedge->setScale(1.85, 1, 1);
		hedge->setAngle(90, 0, 1, 0);
		//hedge->setScale(0.1, 0.1, 0.1);
		AddObj(hedge);
	}
	Object* hedge = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), "Textures/hedge.bmp");
	hedge->texID = GetTexture("Textures/hedge.bmp");
	hedge->setPosition(-80, -5, 98);
	hedge->setScale(1.85, 1, 1);
	hedge->setAngle(0, 0, 1, 0);
	//hedge->setScale(0.1, 0.1, 0.1);
	AddObj(hedge);
	hedge = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), "Textures/hedge.bmp");
	hedge->texID = GetTexture("Textures/hedge.bmp");
	hedge->setPosition(-40, -5, 98);
	hedge->setScale(1.5, 1, 1);
	hedge->setAngle(0, 0, 1, 0);
	//hedge->setScale(0.1, 0.1, 0.1);
	AddObj(hedge);
	hedge = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), "Textures/hedge.bmp");
	hedge->texID = GetTexture("Textures/hedge.bmp");
	hedge->setPosition(25, -5, 98);
	hedge->setScale(1.2, 1, 1);
	hedge->setAngle(0, 0, 1, 0);
	//hedge->setScale(0.1, 0.1, 0.1);
	AddObj(hedge);
	hedge = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), "Textures/hedge.bmp");
	hedge->texID = GetTexture("Textures/hedge.bmp");
	hedge->setPosition(55, -5, 98);
	hedge->setScale(1.2, 1, 1);
	hedge->setAngle(0, 0, 1, 0);
	//hedge->setScale(0.1, 0.1, 0.1);
	AddObj(hedge);

	//portals
	ldr = new ObjLoader();
	ldr->LoadObj("Models/Portal.obj", true);
	Object* portal = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), "Textures/Log.bmp");
	portal->texID = GetTexture("Textures/Log.bmp");
	portal->setPosition(85, 0, 97);
	portal->setAngle(90, 0, 1, 0);
	AddObj(portal);
	portal = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), "Textures/Log.bmp");
	portal->texID = GetTexture("Textures/Log.bmp");
	portal->setPosition(-5, 0, 97);
	portal->setAngle(90, 0, 1, 0);
	AddObj(portal);

	//portal images
	points.clear();
	points.push_back(new Vertex(93, 0.f, 98.f));
	points.push_back(new Vertex(75.f, 0.f, 98.f));
	points.push_back(new Vertex(75.f, 25.f, 98.f));
	points.push_back(new Vertex(93.f, 25.f, 98.f));
	Tile* tile = new Tile(points, new Vertex(255, 255, 255), "Textures/Portal.bmp");
	AddObj(tile);
	points.clear();
	points.clear();
	points.push_back(new Vertex(3, 0.f, 98.f));
	points.push_back(new Vertex(-15.f, 0.f, 98.f));
	points.push_back(new Vertex(-15.f, 25.f, 98.f));
	points.push_back(new Vertex(3.f, 25.f, 98.f));
	tile = new Tile(points, new Vertex(255, 255, 255), "Textures/Portal.bmp");
	AddObj(tile);

	ldr = new ObjLoader();
	ldr->LoadObj("Models/Tree.obj", true);
	Object* tree = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), "Textures/Log.bmp");
	tree->texID = GetTexture("Textures/tree.bmp");
	tree->setPosition(0, 0, -10);
	//tree->setAngle(90, 0, 0, 0);
	AddObj(tree);
	tree = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), "Textures/Log.bmp");
	tree->texID = GetTexture("Textures/tree.bmp");
	tree->setPosition(-10, 0, -10);
	//tree->setAngle(90, 0, 0, 0);
	AddObj(tree);

	//Campfire
	ldr = new ObjLoader();
	ldr->LoadObj("Models/FullFire.obj",true);
	CampfireObject* player = new CampfireObject(ldr->getVerts(), ldr->getNorms(),ldr->getUVs(), ldr->getMat());
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
	//floorTile->AddToScene();
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
	

	points.push_back(new Vertex(30.f, 10.f, 0.f));
	points.push_back(new Vertex(40.f, 10.f, 0.f));
	points.push_back(new Vertex(40.f, 20.f, 0.f));
	points.push_back(new Vertex(30.f, 20.f, 0.f));
	Soldier* soldier = new Soldier(points, new Vertex(255, 255, 255), "Textures/monster_nose_squid.bmp",1);
	//AddObj(soldier);
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