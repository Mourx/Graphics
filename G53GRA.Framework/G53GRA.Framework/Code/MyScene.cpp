#include "MyScene.h"
#include "Light.h"
#include "Tile.h"
#include "Path.h"
#include "ObjLoader.h"
#include "Object.h"
#include "CampfireObject.h"
#include "TowerObject.h"
#include "SkyBox.h"
#include "PumpkinObject.h"

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{

}

	// new add to scene function to allow for creation and deletion of objects during the scene
void MyScene::AddObj(DisplayableObject* obj) {
	objects.push_back(obj);
}

	// need custom Update to be able to add to objects
void MyScene::Update(const double& deltaTime)
{
	Animation* animated_obj;
	// Update camera/view
	this->GetCamera()->Update(deltaTime);
	// Iterate through objects to update animations
	// can't use a real iterator since it breaks when adding / removing projectiles
	for (int i = 0; i<objects.size(); i++)
	{
		DisplayableObject* obj = objects[i];
		animated_obj = dynamic_cast<Animation*>(obj); // Cast to animation
		if (animated_obj != NULL) // If cast successful
			animated_obj->Update(deltaTime); // Call update sequence for obj
	}
	
}

	// same as Update, new function for custom addObject
void MyScene::HandleKey(unsigned char key, int state, int x, int y)
{
	Input* input_obj;
	Scene::HandleKey(key, state, x, y);
	for (int i = 0; i<objects.size(); i++)
	{
		DisplayableObject* obj = objects[i];
		input_obj = dynamic_cast<Input*>(obj);
		if (input_obj != NULL)
			input_obj->HandleKey(key, state, x, y);
	}
}


	// custom draw, basically the same but allows for projectiles to be created / destroyed without breaking
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

	// setup the path for the robot to walk
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

	// add all the objects to the scene
void MyScene::Initialise()
{
	
	//vector for adding points for non- .obj objects
	std::vector<Vertex*> points;
	//setup node corners
	std::vector<Node*> corners;
	corners = InitialiseNodes(corners);

	//setup middle turret
	ObjLoader* ldr = new ObjLoader();
	ldr->LoadObj("Models/Turret_top.obj",true);
	TowerObject* turret = new TowerObject(ldr->getVerts(),ldr->getNorms(),ldr->getUVs(),ldr->getMat(),this);
	turret->texID = GetTexture("Textures/Steel.bmp");
	turret->setPosition(-15, 5, 10);
	AddObj(turret);

	//SkyBox
	ldr = new ObjLoader();
	ldr->LoadObj("Models/SkyBox.obj",true);
	SkyBox* sky = new SkyBox(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), "Textures/space2.bmp");
	AddObj(sky);

	// setup hedges around the garden
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

	//portal frames
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
	points.push_back(new Vertex(48, 0.f, 49.f));
	points.push_back(new Vertex(37.f, 0.f, 49.f));
	points.push_back(new Vertex(37.f, 12.f, 49.f));
	points.push_back(new Vertex(48.f, 12.f, 49.f));
	Tile* tile = new Tile(points, new Vertex(255, 255, 255),0, "Textures/Portal.bmp");
	tile->setScale(2);
	AddObj(tile);
	points.clear();
	points.clear();
	points.push_back(new Vertex(2, 0.f, 49.f));
	points.push_back(new Vertex(-7.f, 0.f, 49.f));
	points.push_back(new Vertex(-7.f, 12.f, 49.f));
	points.push_back(new Vertex(2.f, 12.f, 49.f));
	tile = new Tile(points, new Vertex(255, 255, 255),0, "Textures/Portal.bmp");
	tile->setScale(2);
	AddObj(tile);

	// treees
	ldr = new ObjLoader();
	ldr->LoadObj("Models/Tree.obj", true);
	Object* tree = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), "Textures/Log.bmp");
	tree->texID = GetTexture("Textures/tree.bmp");
	tree->setPosition(50, 0, -20);
	AddObj(tree);

	tree = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), "Textures/Log.bmp");
	tree->texID = GetTexture("Textures/tree.bmp");
	tree->setPosition(-50, 0, 20);
	AddObj(tree);

	tree = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), "Textures/Log.bmp");
	tree->texID = GetTexture("Textures/tree.bmp");
	tree->setPosition(50, -10, 55);
	AddObj(tree);

	tree = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), "Textures/Log.bmp");
	tree->texID = GetTexture("Textures/tree.bmp");
	tree->setPosition(20, -10, 70);
	AddObj(tree);

	tree = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), "Textures/Log.bmp");
	tree->texID = GetTexture("Textures/tree.bmp");
	tree->setPosition(-15, -20, -40);
	AddObj(tree);

	// jumping pumpkin
	ldr = new ObjLoader();
	ldr->LoadObj("Models/Pumpkin2.obj", true);
	PumpkinObject* pumpkin = new PumpkinObject(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), "Textures/Log.bmp");
	pumpkin->texID = GetTexture("Textures/pumpkin2.bmp");
	pumpkin->setPosition(75, 0, -20);
	pumpkin->setScale(0.6, 0.6, 0.6);
	AddObj(pumpkin);

	// house
	ldr = new ObjLoader();
	ldr->LoadObj("Models/House.obj", true);
	Object* house = new Object(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), "Textures/Log.bmp");
	house->texID = GetTexture("Textures/house.bmp");
	house->setPosition(50, 0, -50);
	house->setAngle(145, 0, 1, 0);
	AddObj(house);

	//Campfire
	ldr = new ObjLoader();
	ldr->LoadObj("Models/FullFire.obj",true);
	CampfireObject* fire = new CampfireObject(ldr->getVerts(), ldr->getNorms(),ldr->getUVs(), ldr->getMat());
	fire->setPosition(45, 0, -50);
	AddObj(fire);

	// Robots
	ldr = new ObjLoader();
	ldr->LoadObj("Models/Monster.obj",true);
	EnemyObject* enemy = new EnemyObject(ldr->getVerts(), ldr->getNorms(),ldr->getUVs(),corners, ldr->getMat(),0);
	AddObj(enemy);
	enemies.push_back(enemy);

	enemy = new EnemyObject(ldr->getVerts(), ldr->getNorms(), ldr->getUVs(), corners, ldr->getMat(),5);
	enemy->setNextNode(4);
	enemy->setAngle(-90,0,1,0);
	AddObj(enemy);
	enemies.push_back(enemy);

	// grass floor
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 20; j++) {
			points.push_back(new Vertex(-100.f + 10 * j, 0.f, -90.f + 10 * i));
			points.push_back(new Vertex(-90.f + 10 * j, 0.f, -90.f + 10 * i));
			points.push_back(new Vertex(-90.f + 10 * j, 0.f, - 100.f + 10 * i));
			points.push_back(new Vertex(-100.f + 10 * j, 0.f, -100.f + 10 * i));
			Tile* tile = new Tile(points, new Vertex(255, 255, 255), 10, "Textures/Grass.bmp");
			tile->setScale(2);
			AddObj(tile);
			points.clear();

		}
	}
	points.clear();
	//make the path using corners
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