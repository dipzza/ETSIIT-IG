#include "respaldo.h"

Respaldo::Respaldo(float tam, float inclinacion)
{
	this->tam = tam;
	this->inclinacion = inclinacion;
	
	cubo = new Cubo(12*tam);
	
	cubo->setMaterial(MAT_CYAN_RUBBER);
}

void Respaldo::draw(const int modo_dibujado, const int modo_visualizacion)
{
	glPushMatrix();
		glRotatef((inclinacion * 110) - 90, 1.0, 0.0, 0.0);
		glScalef(1.0, 1.5, 0.2);
		glTranslatef(-6*tam, 0, -6*tam);
		cubo->draw(modo_dibujado, modo_visualizacion);
	glPopMatrix();
}

void Respaldo::draw_selection()
{
	glPushMatrix();
		glRotatef((inclinacion * 110) - 90, 1.0, 0.0, 0.0);
		glScalef(1.0, 1.5, 0.2);
		glTranslatef(-6*tam, 0, -6*tam);
		cubo->draw_selection();
	glPopMatrix();
}

void Respaldo::setInclinacion(float valor)
{
	inclinacion = valor;
}
