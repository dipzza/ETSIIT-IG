#ifndef LUZ_H_INCLUDED
#define LUZ_H_INCLUDED

#include "aux.h"

class Luz
{
	protected:
		Tupla4f posicion; // Si la 4a componente es 0 luz direccional, si no posicional
		GLenum id;
		Tupla4f colorAmbiente, colorDifuso, colorEspecular;

	public:
		void activar();
		void desactivar();
		void girar();
};

class LuzDireccional : public Luz
{
	protected:
		float alpha;
		float beta;

	public:
		// inicializar la fuente de Luz
		LuzDireccional(const GLenum id, const Tupla4f ambiente, const Tupla4f difuso, const Tupla4f especular, const Tupla2f & orientacion);
		// Cambiar angulo
		void variarAnguloAlpha(const float incremento);
		void variarAnguloBeta(const float incremento);
};

class LuzPosicional : public Luz
{
	protected:
		bool up;
	public:
		// inicializar la fuente de Luz
		LuzPosicional(const GLenum id, const Tupla3f posicion, const Tupla4f ambiente, const Tupla4f difuso, const Tupla4f especular);
		void animarAzul(float incremento);
};

#endif
