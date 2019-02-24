#pragma once

#include "../Framework/Engine/Scene.h"
#include "EnemyObject.h"

class MyScene :
	public Scene
{
public:
	MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight);
	~MyScene() {};
	void AddObj(DisplayableObject* obj);
	std::vector<EnemyObject*> getEnemies();
	void Update(const double& deltaTime);
	void Draw();
	void Clean();
	Camera* GetCam();
private:
	void Initialise();
	void Projection();
	std::vector<EnemyObject*> enemies;
	std::vector<DisplayableObject*> objects;
};