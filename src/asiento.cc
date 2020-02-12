#include "asiento.h"

Asiento::Asiento(float tam)
{
	this->tam = tam;
	
	cilindro = new Cilindro(10, 20, tam*4, tam*1.25, true, true);
	cubo = new Cubo(12*tam);
    
    cilindro->setMaterial(MAT_SILVER);
    cubo->setMaterial(MAT_CYAN_RUBBER);
}

void Asiento::draw(const int modo_dibujado, const int modo_visualizacion)
{
	glPushMatrix();
		// Cojin
		glPushMatrix();
			glScalef(1.0, 0.2, 1.0);
			glTranslatef(-6*tam, 0, -6*tam);
			cubo->draw(modo_dibujado, modo_visualizacion);
		glPopMatrix();
		// Brazo izquierdo
		glPushMatrix();
			glTranslatef(5.5*tam, 0, 0);
			cilindro->draw(modo_dibujado, modo_visualizacion);
			glTranslatef(0, 4*tam, 0);
			glScalef(0.2, 0.15, 0.6);
			glTranslatef(-6*tam, 0, -6*tam);
			cubo->draw(modo_dibujado, modo_visualizacion);
		glPopMatrix();
		// Brazo derecho
		glTranslatef(-5.5*tam, 0, 0);
		cilindro->draw(modo_dibujado, modo_visualizacion);
		glTranslatef(0, 4*tam, 0);
		glScalef(0.2, 0.15, 0.6);
		glTranslatef(-6*tam, 0, -6*tam);
		cubo->draw(modo_dibujado, modo_visualizacion);
	glPopMatrix();
}

void Asiento::draw_selection()
{
	glPushMatrix();
		// Cojin
		glPushMatrix();
			glScalef(1.0, 0.2, 1.0);
			glTranslatef(-6*tam, 0, -6*tam);
			cubo->draw_selection();
		glPopMatrix();
		// Brazo izquierdo
		glPushMatrix();
			glTranslatef(5.5*tam, 0, 0);
			cilindro->draw_selection();
			glTranslatef(0, 4*tam, 0);
			glScalef(0.2, 0.15, 0.6);
			glTranslatef(-6*tam, 0, -6*tam);
			cubo->draw_selection();
		glPopMatrix();
		// Brazo derecho
		glTranslatef(-5.5*tam, 0, 0);
		cilindro->draw_selection();
		glTranslatef(0, 4*tam, 0);
		glScalef(0.2, 0.15, 0.6);
		glTranslatef(-6*tam, 0, -6*tam);
		cubo->draw_selection();
	glPopMatrix();
}
