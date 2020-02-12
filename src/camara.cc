#include "camara.h"

Camara::Camara(int tipo, Tupla3f eye, Tupla3f up, float width, float height, float near, float far)
{
	at = {0, 0, 0};
	
	this->eye = eye;
	this->tipo = tipo;
	this->up = up;
	this->width = width;
	this->height = height;
	this->near = near;
	this->far = far;
	zoom_factor = 1.0;
}

void Camara::girar_alrededor(float angle_x, float angle_y)
{
	Tupla3f cameraDirection = (at- eye).normalized();
	Tupla3f cameraRight = up.cross(cameraDirection).normalized();
	
	if (up[Y] < 0)
		angle_y = -angle_y;
	
	eye = girarVerticeEje((eye - at), -angle_x, cameraRight) + at;
	eye = girarVertice((eye - at), angle_y, Y) + at;
}

void Camara::girar_primera_persona(float angle_x, float angle_y)
{
	Tupla3f cameraDirection = (at- eye).normalized();
	Tupla3f cameraRight = up.cross(cameraDirection).normalized();
	
	if (up[Y] < 0)
		angle_y = -angle_y;

	at = girarVerticeEje((at - eye), angle_x, cameraRight) + eye;
	at = girarVertice((at - eye), -angle_y, Y) + eye;
}

void Camara::mover(float right, float upward, float forward, bool first_person)
{
	Tupla3f cameraDirection = (eye - at).normalized();
	Tupla3f cameraRight = up.cross(cameraDirection).normalized();
		
	eye = eye + right * cameraRight;
	eye = eye + upward * up.normalized();
	eye = eye + forward * -cameraDirection;
	
	if (first_person)
	{
		at = at + right * cameraRight;
		at = at + upward * up.normalized();
		at = at + forward * -cameraDirection;
	}
}

void Camara::zoom(float factor)
{
	zoom_factor += factor;
}

void Camara::setObservador()
{
	gluLookAt(eye[X], eye[Y], eye[Z],
				at[X], at[Y], at[Z],
				up[X], up[Y], up[Z]);
}

void Camara::setProyeccion()
{
	float ancho = width * zoom_factor;
	float alto = height * zoom_factor;
	
	if (tipo == PERSPECTIVA)
		glFrustum(-ancho/2, ancho/2, -alto/2, alto/2, near, far);
	else if (tipo == ORTOGONAL)
		glOrtho(-ancho/2, ancho/2, -alto/2, alto/2, near, far);
}

void Camara::setWidth(float width) { this->width = width; }
void Camara::setHeight(float height) { this->height = height; }
void Camara::setAt(Tupla3f at) { this->at = at; }

float Camara::getWidth() { return width; }
float Camara::getHeight() { return height; }
