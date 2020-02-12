#include "aux.h"

Tupla3f girarVertice(const Tupla3f vert, const float angle, const int eje_giro)
{
	Tupla3f girado;
	
	if (eje_giro == X)
	{
		girado = {vert[X],
				 float(cos(angle)) * vert[Y] - float(sin(angle)) * vert[Z],
				 float(sin(angle)) * vert[Y] + float(cos(angle)) * vert[Z]};
	} else if (eje_giro == Y)
	{
		girado = {float(cos(angle)) * vert[X] + float(sin(angle)) * vert[Z], 
				 vert[Y], 
				 -float(sin(angle)) * vert[X] + float(cos(angle)) * vert[Z]};
	} else if (eje_giro == Z)
	{
		girado = {float(cos(angle)) * vert[X] - float(sin(angle)) * vert[Y],
				 float(sin(angle)) * vert[X] + float(cos(angle)) * vert[Y],
				 vert[Z]};
	}
	
	return girado;
}

Tupla3f girarVerticeEje(const Tupla3f vert, const float angle, const Tupla3f eje_giro)
{
	Tupla3f girado;
	
	float cosen = float(cos(angle));
	float sen = float(sin(angle));

	girado = {((cosen + eje_giro[X] * eje_giro[X] * (1 - cosen)) * vert[X])
		+ ((eje_giro[X] * eje_giro[Y] * (1 - cosen) - eje_giro[Z] * sen) * vert[Y])
		+ ((eje_giro[X] * eje_giro[Z] * (1 - cosen) + eje_giro[Y] * sen) * vert[Z]),
		((eje_giro[Y] * eje_giro[X] * (1 - cosen) + eje_giro[Z] * sen) * vert[X])
		+ ((cosen + eje_giro[Y] * eje_giro[Y] * (1 - cosen)) * vert[Y])
		+ (((eje_giro[Y] * eje_giro[Z] * (1 - cosen)) - eje_giro[X] * sen) * vert[Z]),
		((eje_giro[Z] * eje_giro[X] * (1 - cosen) - eje_giro[Y] * sen) * vert[X])
		+ ((eje_giro[Z] * eje_giro[Y] * (1 - cosen) + eje_giro[X] * sen) * vert[Y])
		+ ((cosen + eje_giro[Z] * eje_giro[Z] * (1 - cosen)) * vert[Z])};
	
	return girado;
}
