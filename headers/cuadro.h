#ifndef CUADRO_H_INCLUDED
#define CUADRO_H_INCLUDED

#include "aux.h"
#include "malla.h"

// *****************************************************************************
// Cuadro con un punto en el origen y anchura unidad por defecto
// (tiene 4 vertices y 2 caras)

class Cuadro : public Malla3D
{
   public:
   Cuadro(float width=1) ;

} ;
#endif
