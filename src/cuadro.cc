#include "cuadro.h"

Cuadro::Cuadro(float width)
{
   // inicializar la tabla de vértices
	v.push_back(Tupla3f(-0.5, -0.5, 0.0)*width);
	v.push_back(Tupla3f(0.5, -0.5, 0.0)*width);
	v.push_back(Tupla3f(-0.5, 0.5, 0.0)*width);
	v.push_back(Tupla3f(0.5, 0.5, 0.0)*width);

   // inicializar la tabla de caras o triángulos
	f.push_back(Tupla3i(2, 0, 1));
	f.push_back(Tupla3i(1, 3, 2));
	num_triangulos = f.size();
	
	// incializar la tabla de coordenadas de textura
	ct.push_back(Tupla2f(0, 1));
	ct.push_back(Tupla2f(1, 1));
	ct.push_back(Tupla2f(0, 0));
	ct.push_back(Tupla2f(1, 0));
	
	// inicializar la tabla de normales
	calcular_normales();
	
	// inicializar la tabla de colores:
	color_solid = std::vector<Tupla4f> (v.size(), BLANCO);
	color_line = std::vector<Tupla4f> (v.size(), NEGRO);
	color_point =  std::vector<Tupla4f> (v.size(), ROSA);
}
