#ifndef _RESPALDO_H
#define _RESPALDO_H

#include "cubo.h"

class Respaldo
{
	private:
		float tam, inclinacion;
		Cubo * cubo = nullptr;

	public:
		Respaldo(float tam, float inclinacion);
		void draw(const int modo_dibujado, const int modo_visualizacion);
		void draw_selection();
		
		void setInclinacion(float valor);
};
#endif
