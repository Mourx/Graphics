#include "Light.h"



Light::~Light()
{
}


Light::Light(Vertex* position,int light)
{
	lightNo = light;
	_radius = 200;
	// Set ambient colour of the light (off-grey)
	static GLfloat ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	
	//robot spotlight
	if (lightNo == GL_LIGHT0 || GL_LIGHT5) {
		// Set diffuse colour of the light (white)
		static GLfloat diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		static GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		this->position = position;
		_positionalLight = 1.0f;
		_ambient = ambient;
		_diffuse = diffuse;
		_specular = specular;
	}
	// campfire embers
	else if (lightNo == GL_LIGHT1 || lightNo == GL_LIGHT2 || lightNo == GL_LIGHT3);
	{
		// Set diffuse colour of the light (orangey)
		static GLfloat diffuse[] = { 1.0f, 0.45f, 0.f, 1.0f };
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

	//robot spotlight, points in front of it
	if (lightNo == GL_LIGHT0 || lightNo == GL_LIGHT5) {
		
		//lots of GL stuff to initialise light
		_position[0] = position->x;
		_position[1] = position->y;
		_position[2] = position->z;
		_position[3] = 1.0;
		glLightfv(lightNo, GL_POSITION, _position);
		glLightfv(lightNo, GL_AMBIENT, _ambient);
		glLightfv(lightNo, GL_DIFFUSE, _diffuse);
		glLightfv(lightNo, GL_SPECULAR, _specular);
		glLightf(lightNo, GL_SPOT_CUTOFF, 20.0);
		
		//point diagonally down
		GLfloat spot_direction[] = { 0, -1, -.5};
		glLightfv(lightNo, GL_SPOT_DIRECTION, spot_direction);
		glLightf(lightNo, GL_CONSTANT_ATTENUATION, 1);
		glLightf(lightNo, GL_SPOT_EXPONENT, 20.0);
		glColor3f(1, 1, 1);

		glEnable(lightNo);
	}
	else if (lightNo == GL_LIGHT1 || lightNo == GL_LIGHT2 || lightNo == GL_LIGHT3) {
		_position[0] = position->x;
		_position[1] = position->y;
		_position[2] = position->z;
		_position[3] = 1.0;
		glLightfv(lightNo, GL_POSITION, _position);
		glLightfv(lightNo, GL_AMBIENT, _ambient);
		glLightfv(lightNo, GL_DIFFUSE, _diffuse);
		glLightfv(lightNo, GL_SPECULAR, _specular);
		glLightf(lightNo, GL_LINEAR_ATTENUATION, 0.5f);
		glEnable(lightNo);
		glPushMatrix();

		//draw some points to look like embers
		glColor3f(1, 0.45, 0);
		glBegin(GL_POINTS);
		glVertex3f(position->x, position->y, position->z);
		glVertex3f(position->x+2, position->y+1, position->z+5);
		glVertex3f(position->x-1, position->y-2, position->z-4);
		glVertex3f(position->x - 6, position->y - 2, position->z - 4);
		glVertex3f(position->x - 10, position->y - 4, position->z - 4);
		glVertex3f(position->x - 15, position->y - 6, position->z - 4);
		glEnd();
		glPopMatrix();
	}	
}

void Light::Update(const double& deltaTime) {
	
}

void Light::setPosition(float x, float y, float z) {
	position->x = x;
	position->y = y;
	position->z = z;
}