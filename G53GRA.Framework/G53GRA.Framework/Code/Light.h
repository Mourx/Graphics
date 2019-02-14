#pragma once
#include "DisplayableObject.h"
#include "Animation.h"

class Light :
	public DisplayableObject
{
public:
	Light();
	~Light();

	void Display();
	void Update(const double& deltaTime);
	inline void ToggleLightType() { _positionalLight = fmod(_positionalLight + 1.f, 2.f); }
private:

	// Taken from Demos to learn.
	// member variable describing radius for rotation
	double _radius;

	// reflectance model parameters for LIGHT
	GLfloat *_ambient, *_diffuse, *_specular;

	// flag for indicating positional or directional light source
	// 0.0f for directional, 1.0f for positional
	GLfloat _positionalLight;
};

