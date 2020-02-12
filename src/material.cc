#include "aux.h"
#include "material.h"

Material::Material(Tupla4f mambiente, Tupla4f mdifuso, Tupla4f mespecular, float brillo)
{
	ambiente = mambiente;
	difuso = mdifuso;
	especular = mespecular;
	this->brillo = brillo;
}

void Material::aplicar()
{
	glMaterialfv(GL_FRONT, GL_AMBIENT, ambiente);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, difuso);
	glMaterialfv(GL_FRONT, GL_SPECULAR, especular);
	glMaterialfv(GL_FRONT, GL_SHININESS, &brillo);
}
