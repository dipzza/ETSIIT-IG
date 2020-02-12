#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"

#include "math.h"

// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf, const int eje) {
	std::vector<Tupla3f> perf_orig;
	ply::read_vertices(archivo, perf_orig);
	
	*this = ObjRevolucion(perf_orig, num_instancias, tapa_sup, tapa_inf, eje);
	calcular_normales();
}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)


ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf, const int eje) {
	crearMalla(archivo, num_instancias, tapa_sup, tapa_inf, eje);
	color_solid = std::vector<Tupla4f> (v.size(), AZUL);
	color_line = std::vector<Tupla4f> (v.size(), NEGRO);
	color_point =  std::vector<Tupla4f> (v.size(), VERDE);
}

void ObjRevolucion::mostrarTapas(const bool tapas) 
{ 
	if (tapas)
		num_triangulos = f.size();
	else
		num_triangulos = f.size() - num_triangulos_tapas;
}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, const int num_instancias, const bool tapa_sup, const bool tapa_inf, const int eje) {
	
	// Extraemos las tapas si existen
	Tupla3f poloSup, poloInf;
	bool existePoloSup = false, existePoloInf = false;
	bool bottomUp = perfil_original.front()[eje] <= perfil_original.back()[eje];
	
	if (eje == X && perfil_original.front()[Y] == 0 && perfil_original.front()[Z] == 0 ||
		eje == Y && perfil_original.front()[X] == 0 && perfil_original.front()[Z] == 0 ||
		eje == Z && perfil_original.front()[X] == 0 && perfil_original.front()[Y] == 0)
	{
			existePoloInf = true;
			poloInf = perfil_original.front();
			perfil_original.erase(perfil_original.begin());
	}
	
	if (eje == X && perfil_original.back()[Y] == 0 && perfil_original.back()[Z] == 0 ||
		eje == Y && perfil_original.back()[X] == 0 && perfil_original.back()[Z] == 0 ||
		eje == Z && perfil_original.back()[X] == 0 && perfil_original.back()[Y] == 0)
	{
			existePoloSup = true;
			poloSup = perfil_original.back();
			perfil_original.pop_back();
	}
	
	// Creamos la tabla de vertices
	int num_vertices = perfil_original.size();
	
	for (int i = 0; i < num_instancias; ++i)
	{
		float angle = (2*M_PI*i / num_instancias);
		for (int j = 0; j < num_vertices; ++j)
		{
			v.push_back(girarVertice(perfil_original[j], angle, eje));
		}
	}
	
	// Creamos la tabla de triángulos
	int index_a, index_b;
	
	if (bottomUp)
	{
		for (int i = 0; i < num_instancias; ++i)
		{
			for (int j = 0; j < (num_vertices - 1); ++j)
			{
				index_a = num_vertices * i + j;
				index_b = num_vertices * ((i+1) % num_instancias) + j;
				f.push_back({index_a, index_b, index_b + 1});
				f.push_back({index_a, index_b + 1, index_a + 1});
			}
		}
	}
	else
	{
		for (int i = 0; i < num_instancias; ++i)
		{
			for (int j = 0; j < (num_vertices - 1); ++j)
			{
				index_a = num_vertices * i + j;
				index_b = num_vertices * ((i+1) % num_instancias) + j;
				f.push_back({index_a, index_b + 1, index_b});
				f.push_back({index_a, index_a + 1, index_b + 1});
			}
		}
	}
	
	
	if (!existePoloInf)
	{
		poloInf = {0, 0, 0};
		poloInf[eje] = perfil_original.front()[eje];
	}
	v.push_back(poloInf);
	index_a = v.size() - 1;
	if (!existePoloSup)
	{
		poloSup = {0, 0, 0};
		poloSup[eje] = perfil_original.back()[eje];
	}
	v.push_back(poloSup);
	index_b = v.size() - 1;
	
	if (bottomUp)
		for (int i = 0; i < num_instancias; ++i)
		{
			if (tapa_inf)
				f.push_back({index_a, num_vertices * ((i+1) % num_instancias), num_vertices * i});
			if (tapa_sup)
				f.push_back({index_b,  num_vertices * (i+1) - 1, num_vertices * (((i + 1) % num_instancias)+1) - 1});
		}
	else
		for (int i = 0; i < num_instancias; ++i)
		{
			if (tapa_sup)
				f.push_back({index_a, num_vertices * i, num_vertices * ((i+1) % num_instancias)});
			if (tapa_inf)
				f.push_back({index_b, num_vertices * (((i + 1) % num_instancias)+1) - 1, num_vertices * (i+1) - 1});
		}
		
	
	num_triangulos_tapas = 0;
	if (tapa_inf) num_triangulos_tapas += num_instancias;
	if (tapa_sup) num_triangulos_tapas += num_instancias;
	
	mostrarTapas(true);
	calcular_normales();
}
