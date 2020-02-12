#ifndef _SOPORTE_H
#define _SOPORTE_H

#include "cilindro.h"
#include "cubo.h"

class Asiento
{
	private:
		float tam;
		Cilindro * cilindro = nullptr;
		Cubo * cubo = nullptr;

	public:
		Asiento(float tam);
		void draw(const int modo_dibujado, const int modo_visualizacion);
		void draw_selection();
};
#endif
