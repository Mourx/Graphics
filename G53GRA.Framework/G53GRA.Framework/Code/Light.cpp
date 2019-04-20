#include "Light.h"



Light::~Light()
{
}


Light::Light(Vertex* position,int light)
	: _radius(200.0), _positionalLight(1.0f)
{
	lightNo = light;

	// Set ambient colour of the light (off-grey)
	static GLfloat ambient[] = { 0.15f, 0.15f, 0.1f, 1.0f };
	
	if (lightNo == GL_LIGHT0) {
		// Set diffuse colour of the light (red)
		static GLfloat diffuse[] = { 0.8f, 0.0f, 0.8f, 1.0f };
		// Set specular icolour (white)
		static GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		this->position = position;
		_ambient = ambient;
		_diffuse = diffuse;
		_specular = specular;
	}
	else
	{
		// Set diffuse colour of the light (red)
		static GLfloat diffuse[] = { 0.0f, 0.8f, 0.f, 1.0f };
		// Set specular icolour (white)
		static GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		this->position = position;
		_ambient = ambient;
		_diffuse = diffuse;
		_specular = specular;
	}

	
}

void Light::Display() {

	// Disable lighting on this geometry (since it is the source
	// of the light) so it will only be coloured by glColor call
	glEnable(GL_LIGHTING);
	GLfloat _position[4];
	_position[0] = position->x;
	_position[1] = position->y;
	_position[2] = position->z;
	_position[3] = _positionalLight;
	glLightfv(lightNo, GL_AMBIENT, _ambient);
	glLightfv(lightNo, GL_DIFFUSE, _diffuse);
	glLightfv(lightNo, GL_SPECULAR, _specular);
	glLightfv(lightNo, GL_POSITION, _position);

	glEnable(lightNo);


	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
	// Match colour of sphere to diffuse colour of light
	glColor4fv(_diffuse);
	glTranslatef(_position[0], _position[1], _position[2]);
	glutSolidSphere(5.0, 5, 5);
	// Re-enable lighting after light source has been drawn
	glEnable(GL_LIGHTING);
	glPopAttrib();
	glPopMatrix();
	
	
}

void Light::Update(const double& deltaTime) {
	
}
