#include "cono.h"

Cono::Cono(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio)
{
	std::vector<Tupla3f> perf_orig;
	
	float l_seg_radio = radio/(num_vert_perfil - 1);
	float l_seg_altura = altura/(num_vert_perfil - 1);
	
	for (int i=0; i  < num_vert_perfil; ++i)
		perf_orig.push_back({l_seg_radio * i, altura - l_seg_altura * i, 0});
	
// 	perf_orig.push_back({0, altura, 0});
// 	perf_orig.push_back({radio, 0, 0});
	
	crearMalla(perf_orig, num_instancias_perf, true, true, Y);
	
	color_solid = std::vector<Tupla4f> (v.size(), ROSA);
	color_line = std::vector<Tupla4f> (v.size(), AZUL);
	color_point =  std::vector<Tupla4f> (v.size(), VERDE);
	calcular_normales();
}
