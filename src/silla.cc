#include "silla.h"
#include "math.h"

Silla::Silla(float tam)
{
	this->tam = tam;
	this->altura = 0.0;
	this->giro = 0.0;
	this->inclinacion = 0.8;
	
	upAltura = true;
	upGiro = true;
	upInclinacion = true;
	
	pata = new Pata(tam);
	asiento = new Asiento(tam);
	respaldo = new Respaldo(tam, inclinacion);
	cilindro = new Cilindro(10, 20, tam*4, tam*2.5, true, true);
    
    cilindro->setMaterial(MAT_SILVER);
}

void Silla::draw(const int modo_dibujado, const int modo_visualizacion)
{
	glPushMatrix();
		// Patas
		glPushMatrix();
			pata->draw(modo_dibujado, modo_visualizacion);
			glRotatef(72, 0.0, 1.0, 0.0);
			pata->draw(modo_dibujado, modo_visualizacion);
			glRotatef(72, 0.0, 1.0, 0.0);
			pata->draw(modo_dibujado, modo_visualizacion);
			glRotatef(72, 0.0, 1.0, 0.0);
			pata->draw(modo_dibujado, modo_visualizacion);
			glRotatef(72, 0.0, 1.0, 0.0);
			pata->draw(modo_dibujado, modo_visualizacion);
		glPopMatrix();
		glTranslatef(0, 4*tam, 0);
		cilindro->draw(modo_dibujado, modo_visualizacion);
		glTranslatef(0.0, altura * tam * 4, 0.0);
		glPushMatrix();
			glScalef(0.5, 1.0, 0.5);
			cilindro->draw(modo_dibujado, modo_visualizacion);
		glPopMatrix();
		glRotatef(360*giro, 0.0, 1.0, 0.0);
		glTranslatef(0, 4*tam, 0);
		asiento->draw(modo_dibujado, modo_visualizacion);
		glTranslatef(0, 0, -6*tam);
		respaldo->draw(modo_dibujado, modo_visualizacion);
	glPopMatrix();
}

void Silla::draw_selection()
{
	glPushMatrix();
		// Patas
		glPushMatrix();
			pata->draw_selection();
			glRotatef(72, 0.0, 1.0, 0.0);
			pata->draw_selection();
			glRotatef(72, 0.0, 1.0, 0.0);
			pata->draw_selection();
			glRotatef(72, 0.0, 1.0, 0.0);
			pata->draw_selection();
			glRotatef(72, 0.0, 1.0, 0.0);
			pata->draw_selection();
		glPopMatrix();
		glTranslatef(0, 4*tam, 0);
		cilindro->draw_selection();
		glTranslatef(0.0, altura * tam * 4, 0.0);
		glPushMatrix();
			glScalef(0.5, 1.0, 0.5);
			cilindro->draw_selection();
		glPopMatrix();
		glRotatef(360*giro, 0.0, 1.0, 0.0);
		glTranslatef(0, 4*tam, 0);
		asiento->draw_selection();
		glTranslatef(0, 0, -6*tam);
		respaldo->draw_selection();
	glPopMatrix();
}

void Silla::modificaParametro(float &parametro, float variacion, bool &up)
{
	float n_parametro = up ? parametro + variacion : parametro - variacion;
	
	if ((n_parametro) > 1.005)
	{
		parametro = 1 - fmod(n_parametro, 1.0);
		up = !up;
	}
	else if (n_parametro < -0.005)
	{
		parametro = (-fmod(n_parametro, 1.0));
		up = !up;
	}
	else
		parametro = n_parametro;
}

void Silla::modificaAltura(float valor)
{
	modificaParametro(altura, valor, upAltura);
}

void Silla::modificaGiro(float valor)
{
	modificaParametro(giro, valor, upGiro);
}

void Silla::modificaInclinacion(float valor)
{
	modificaParametro(inclinacion, valor, upInclinacion);
	respaldo->setInclinacion(inclinacion);
}
