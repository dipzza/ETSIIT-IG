#ifndef _PATA_H
#define _PATA_H

#include "cilindro.h"
#include "esfera.h"

class Pata
{
	private:
		float tam;
		Cilindro * cilindro = nullptr;
		Esfera * esfera = nullptr;
		
	public:

		Pata(float tam);
		void draw(const int modo_dibujado, const int modo_visualizacion);
		void draw_selection();
};
#endif
