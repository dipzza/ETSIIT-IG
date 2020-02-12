#include "luz.h"

LuzDireccional::LuzDireccional(const GLenum id, const Tupla4f ambiente, const Tupla4f difuso, const Tupla4f especular, const Tupla2f & orientacion)
{
	this->id = id;
	alpha = 0;
	beta = 0;
	posicion[0] = 0;
	posicion[1] = 0;
	posicion[2] = 100;
	posicion[3] = 0;
	colorAmbiente = ambiente;
	colorDifuso = difuso;
	colorEspecular = especular;
	
	variarAnguloAlpha(orientacion[0]);
	variarAnguloBeta(orientacion[1]);
}

void Luz::activar()
{
	glLightfv(GL_LIGHT0 + id, GL_POSITION, posicion);
	glLightfv(GL_LIGHT0 + id, GL_AMBIENT, colorAmbiente);
	glLightfv(GL_LIGHT0 + id, GL_DIFFUSE, colorDifuso);
	glLightfv(GL_LIGHT0 + id, GL_SPECULAR, colorEspecular);
	glEnable(GL_LIGHT0 + id);
}

void Luz::desactivar()
{
	glDisable(GL_LIGHT0 + id);
}

void LuzDireccional::variarAnguloAlpha(const float incremento)
{
	Tupla3f girado;
	
	alpha += incremento;
	
	girado[0] = posicion[0];
	girado[1] = posicion[1];
	girado[2] = posicion[2];
	
	girado = girarVertice(girado, incremento, Y);
	
	posicion[0] = girado[0];
	posicion[1] = girado[1];
	posicion[2] = girado[2];
}

void LuzDireccional::variarAnguloBeta(const float incremento)
{
	Tupla3f girado;
	
	beta += incremento;
	
	girado[0] = posicion[0];
	girado[1] = posicion[1];
	girado[2] = posicion[2];
	
	girado = girarVertice(girado, incremento, X);
	
	posicion[0] = girado[0];
	posicion[1] = girado[1];
	posicion[2] = girado[2];
}

LuzPosicional::LuzPosicional(const GLenum id, const Tupla3f posicion, const Tupla4f ambiente, const Tupla4f difuso, const Tupla4f especular)
{
	this->id = id;
	this->posicion[0] = posicion[0];
	this->posicion[1] = posicion[1];
	this->posicion[2] = posicion[2];
	this->posicion[3] = 1;
	colorAmbiente = ambiente;
	colorDifuso = difuso;
	colorEspecular = especular;
	up = false;
}

void LuzPosicional::animarAzul(const float incremento)
{
	float n_parametro = up ? colorDifuso[2] + incremento : colorDifuso[2] - incremento;
	
	if ((n_parametro) > 1.005)
	{
		colorDifuso[2] = 1 - fmod(n_parametro, 1.0);
		up = !up;
	}
	else if (n_parametro < -0.005)
	{
		colorDifuso[2] = (-fmod(n_parametro, 1.0));
		up = !up;
	}
	else
	{
		colorDifuso[2] = n_parametro;
		colorEspecular[3] = n_parametro;
	}
}
