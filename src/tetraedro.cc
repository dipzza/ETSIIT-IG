#include "aux.h"
#include "malla.h"
#include "tetraedro.h"

Tetraedro::Tetraedro()
{

   // inicializar la tabla de vértices
	v.push_back(Tupla3f(0.0, 0.0, 0.0));
	v.push_back(Tupla3f(50.0, 0.0, 0.0));
	v.push_back(Tupla3f(25.0, 0.0, 50.0));
	v.push_back(Tupla3f(25.0, 50.0, 25.0));

   // inicializar la tabla de caras o triángulos:
	f.push_back(Tupla3i(0, 1, 2));
	f.push_back(Tupla3i(0, 3, 1));
	f.push_back(Tupla3i(1, 3, 2));
	f.push_back(Tupla3i(2, 3, 0));
	num_triangulos = f.size();
	
	// inicializar la tabla de normales
	calcular_normales();
	
	// inicializar la tabla de colores
	color_solid = std::vector<Tupla4f> (v.size(), ROJO);
	color_line = std::vector<Tupla4f> (v.size(), ROSA);
	color_point =  std::vector<Tupla4f> (v.size(), VERDE);
}
