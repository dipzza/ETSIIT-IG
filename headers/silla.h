#ifndef _SILLA_H
#define _SILLA_H

#include "pata.h"
#include "asiento.h"
#include "respaldo.h"

class Silla
{
	private:
		float tam;
		// Atributo >= 0.0 y <= 1.0 que controla el desplazamiento de la parte superior de la silla
		float altura;
		// Atributo >= 0.0 y <= 1.0 que controla el giro de la parte superior de la silla
		float giro;
		// Atributo >= 0.0 y <= 1.0 que controla la inclinación del respaldo
		float inclinacion;
		
		bool upAltura, upGiro, upInclinacion;
		
		Pata * pata = nullptr;
		Asiento * asiento = nullptr;
		Respaldo * respaldo = nullptr;
		Cilindro * cilindro = nullptr;
		
		void modificaParametro(float &parametro, float variacion, bool &up);
		
		
	public:
		Silla(float tam);
		void draw(const int modo_dibujado, const int modo_visualizacion);
		void draw_selection();
		void modificaAltura(float valor);
		void modificaGiro(float valor);
		void modificaInclinacion(float valor);
};
#endif
