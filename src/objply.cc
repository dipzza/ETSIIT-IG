#include "objply.h"
#include "ply_reader.h"
 

// *****************************************************************************
//
// Clase ObjPLY (práctica 2)
//
// *****************************************************************************

ObjPLY::ObjPLY( const std::string & nombre_archivo )
{
   // leer la lista de caras y vértices
	ply::read( nombre_archivo, this->v, this->f );
	num_triangulos = f.size();
	color_solid = std::vector<Tupla4f> (v.size(), ROJO);
	color_line = std::vector<Tupla4f> (v.size(), VERDE);
	color_point =  std::vector<Tupla4f> (v.size(), AZUL);
	calcular_normales();
}
