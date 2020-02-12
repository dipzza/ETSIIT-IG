#include "pata.h"

Pata::Pata(float tam)
{
	this->tam = tam;
	cilindro = new Cilindro(10, 20, tam*6, tam-tam/10, true, true);
	esfera = new Esfera(20, 20, tam);
    
    esfera->setMaterial(MAT_BLACK_PLASTIC);
    cilindro->setMaterial(MAT_BLACK_PLASTIC);
}

void Pata::draw(const int modo_dibujado, const int modo_visualizacion)
{
	glPushMatrix();
		glTranslatef(0.866025*8*tam, tam, 0);
		glRotatef(60, 0.0, 0.0, 1.0);
		glPushMatrix();
			glTranslatef(0, -tam, 0);
			esfera->draw(modo_dibujado, modo_visualizacion);
		glPopMatrix();
		glTranslatef(0, tam, 0);
		cilindro->draw(modo_dibujado, modo_visualizacion);
	glPopMatrix();
}

void Pata::draw_selection()
{
	glPushMatrix();
		glTranslatef(0.866025*8*tam, tam, 0);
		glRotatef(60, 0.0, 0.0, 1.0);
		glPushMatrix();
			glTranslatef(0, -tam, 0);
			esfera->draw_selection();
		glPopMatrix();
		glTranslatef(0, tam, 0);
		cilindro->draw_selection();
	glPopMatrix();
}
