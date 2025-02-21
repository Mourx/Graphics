#pragma once
#include "DisplayableObject.h"
#include "Animation.h"
#include "Vertex.h"

class Light :
	public DisplayableObject
{
public:
	Light(Vertex* position, int light);
	~Light();

	void Display();
	void Update(const double& deltaTime);
	void setPosition(float x, float y, float z);
	inline void ToggleLightType() { _positionalLight = fmod(_positionalLight + 1.f, 2.f); }

	Vertex* position;
private:

	// Taken from Demos to learn.
	// member variable describing radius for rotation
	double _radius;
	
	// reflectance model parameters for LIGHT
	GLfloat *_ambient, *_diffuse, *_specular;
	int lightNo = GL_LIGHT0;
	// flag for indicating positional or directional light source
	// 0.0f for directional, 1.0f for positional
	GLfloat _positionalLight;
};

