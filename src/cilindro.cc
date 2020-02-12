#include "cilindro.h"

Cilindro::Cilindro(const int num_vert_perfil, const int num_instancias_perf, const float altura, const float radio, bool tapa_sup, bool tapa_inf, bool interior)
{
	std::vector<Tupla3f> perf_orig;
	float l_seg = altura/(num_vert_perfil - 1);
	
	for (int i=0; i < num_vert_perfil; ++i)
		perf_orig.push_back({radio, l_seg * i, 0});
	
	crearMalla(perf_orig, num_instancias_perf, tapa_sup, tapa_inf, Y);
	
	color_solid = std::vector<Tupla4f> (v.size(), ROJO);
	color_line = std::vector<Tupla4f> (v.size(), VERDE);
	color_point =  std::vector<Tupla4f> (v.size(), AZUL);
	
	if (interior)
	{
		int tmp;
		for (int i = 0; i < f.size(); ++i)
		{
			tmp = f[i][1];
			f[i][1] = f[i][2];
			f[i][2] = tmp;
		}
	}
	calcular_normales();
}
