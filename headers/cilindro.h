#ifndef CILINDRO_H_INCLUDED
#define CILINDRO_H_INCLUDED

#include "aux.h"
#include "objrevolucion.h"

// *****************************************************************************
//
// clases derivadas de ObjRevolucion (definen constructores específicos)
//
// *****************************************************************************

class Cilindro : public ObjRevolucion
{
	public:
		Cilindro(const int num_vert_perfil,
			const int num_instancias_perf,
			const float altura,
			const float radio, bool tapa_sup=true, bool tapa_inf=true, bool interior=false) ;
} ;

#endif
