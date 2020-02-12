#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"

const int PERSPECTIVA = 0, ORTOGONAL = 1;

class Camara
{
	private:
		Tupla3f eye, at, up;
		
		int tipo;
		float width, height, near, far, zoom_factor;
	
	public:
		Camara(int tipo, Tupla3f eye, Tupla3f up, float width, float height, float near, float far);
		void girar_alrededor(float angle_x, float angle_y);
		void girar_primera_persona(float angle_x, float angle_y);
		void mover(float right, float upward, float forward, bool first_person);
		void zoom(float factor);
		void setObservador();
		void setProyeccion();
		
		float getWidth();
		float getHeight();
		void setWidth(float width);
		void setHeight(float height);
		void setAt(Tupla3f at);
};

#endif
