#include "aux.h"
#include "malla.h"
#include "cubo.h"

Cubo::Cubo(float lado)
{
   // inicializar la tabla de vértices
	v.push_back(Tupla3f(0.0, 0.0, 0.0)*lado);
	v.push_back(Tupla3f(1.0, 0.0, 0.0)*lado);
	v.push_back(Tupla3f(1.0, 0.0, 1.0)*lado);
	v.push_back(Tupla3f(0.0, 0.0, 1.0)*lado);
	v.push_back(Tupla3f(0.0, 1.0, 0.0)*lado);
	v.push_back(Tupla3f(1.0, 1.0, 0.0)*lado);
	v.push_back(Tupla3f(1.0, 1.0, 1.0)*lado);
	v.push_back(Tupla3f(0.0, 1.0, 1.0)*lado);

   // inicializar la tabla de caras o triángulos:
	f.push_back(Tupla3i(0, 1, 2));
	f.push_back(Tupla3i(0, 2, 3));
	f.push_back(Tupla3i(0, 3, 7));
	f.push_back(Tupla3i(0, 7, 4));
	f.push_back(Tupla3i(0, 4, 5));
	f.push_back(Tupla3i(0, 5, 1));
	f.push_back(Tupla3i(6, 1, 5));
	f.push_back(Tupla3i(6, 2, 1));
	f.push_back(Tupla3i(6, 7, 3));
	f.push_back(Tupla3i(6, 3, 2));
	f.push_back(Tupla3i(4, 7, 6));
	f.push_back(Tupla3i(4, 6, 5));
	num_triangulos = f.size();
	
	// inicializar la tabla de normales
	calcular_normales();
	
	// inicializar la tabla de colores:
	color_solid = std::vector<Tupla4f> (v.size(), MORADO);
	color_line = std::vector<Tupla4f> (v.size(), VERDE);
	color_point =  std::vector<Tupla4f> (v.size(), AMARILLO);
}
