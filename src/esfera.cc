#include "esfera.h"

Esfera::Esfera(const int num_vert_perfil, const int num_instancias_perf, const float radio)
{
	//Rotamos un vertice {0, radio, 0}  sobre x para formar una semiesfera
	std::vector<Tupla3f> perf_orig;
	
	for (int i = 0; i < num_vert_perfil; ++i)
	{
		float angle = (M_PI*i) / num_vert_perfil;
		perf_orig.push_back(girarVertice({0, radio, 0}, angle, X));
		perf_orig.back()[Y] += radio;
	}
	
	crearMalla(perf_orig, num_instancias_perf, true, true, Y);
	
	color_solid = std::vector<Tupla4f> (v.size(), AZUL);
	color_line = std::vector<Tupla4f> (v.size(), NEGRO);
	color_point =  std::vector<Tupla4f> (v.size(), VERDE);
	calcular_normales();
}
