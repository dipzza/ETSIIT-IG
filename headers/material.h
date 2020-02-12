// #############################################################################
//
// Declaraciones de clase Material (parámetros para el modelo de iluminación relativos a los objetos)
//
// #############################################################################

#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "aux.h"

class Material
{
	private:
		Tupla4f ambiente;
		Tupla4f difuso;
		Tupla4f especular;
		float brillo;

	public:
		Material(Tupla4f mambiente, Tupla4f mdifuso, Tupla4f mespecular, float brillo);
		
		void aplicar();
};

const int
    MAT_BRASS=0,
    MAT_BRONZE=1,
    MAT_POLISHED_BRONZE=2,
    MAT_CHROME=3,
    MAT_COPPER=4,
    MAT_POLISHED_COPPER=5,
    MAT_GOLD=6,
    MAT_POLISHED_GOLD=7,
    MAT_TIN=8,
    MAT_SILVER=9,
    MAT_POLISHED_SILVER=10,
    MAT_EMERALD=11,
    MAT_JADE=12,
    MAT_OBSIDIAN=13,
    MAT_PERL=14,
    MAT_RUBY=15,
    MAT_TURQUOISE =16,
    MAT_BLACK_PLASTIC=17,
    MAT_CYAN_PLASTIC=18,
    MAT_GREEN_PLASTIC=19,
    MAT_RED_PLASTIC=20,
    MAT_WHITE_PLASTIC=21,
    MAT_YELLOW_PLASTIC=22,
    MAT_BLACK_RUBBER=23,
    MAT_CYAN_RUBBER=24,
    MAT_GREEN_RUBBER=25,
    MAT_RED_RUBBER=26,
    MAT_WHITE_RUBBER=27,
    MAT_YELLOW_RUBBER=28,
    MAT_BRIGHT_WHITE=29,
    MAT_LESS_BRIGHT_WHITE=30,
    MAT_WARM_WHITE=31;


const Tupla4f ambient[50]=
{
	Tupla4f(0.329412, 0.223529, 0.027451,1.0),	//MAT_BRASS=0;
	Tupla4f(0.2125, 0.1275, 0.054,1.0),	//MAT_BRONZE=1;
	Tupla4f(0.25, 0.148, 0.06475,1.0),	//MAT_POLISHED_BRONZE=2;
	Tupla4f(0.25, 0.25, 0.25,1.0),	//MAT_CHROME=3;
	Tupla4f(0.19125, 0.0735, 0.0225,1.0),	//MAT_CUPPER=4;
	Tupla4f(0.2295, 0.08825, 0.0275,1.0),	//MAT_POLISHED_CUPPER=5;
	Tupla4f(0.24725, 0.1995, 0.0745,1.0),	//MAT_GOLD=6;
	Tupla4f(0.24725, 0.2245, 0.0645,1.0),	//MAT_POLISHED_GOLD=7;
	Tupla4f(0.105882, 0.058824, 0.113725,1.0),	//MAT_TIN=8;
	Tupla4f(0.19225, 0.19225, 0.19225,1.0),	//MAT_SILVER=9;
	Tupla4f(0.23125, 0.23125, 0.23125,1.0),	//MAT_POLISHED_SILVER=10;
	Tupla4f(0.0215, 0.1745, 0.0215, 0.55),	//MAT_EMERALD=11;
	Tupla4f(0.135, 0.2225, 0.1575, 0.95),	//MAT_JADE=12;
	Tupla4f(0.05375, 0.05, 0.06625, 0.82),	//MAT_OBSIDIAN=13;
	Tupla4f(0.25, 0.20725, 0.20725, 0.922),	//MAT_PERL=14;
	Tupla4f(0.1745, 0.01175, 0.01175, 0.55),	//MAT_RUBY=15;
	Tupla4f(0.1, 0.18725, 0.1745, 0.8),	//MAT_TURQUOISE=16;
	Tupla4f(0.0, 0.0, 0.0, 1.0),	//MAT_BLACK_PLASTIC=17;
	Tupla4f(0.0,0.1,0.06,1.0),	//MAT_CYAN_PLASTIC=18;
	Tupla4f(0.0,0.0,0.0,1.0),	//MAT_GREEN_PLASTIC=19;
	Tupla4f(0.0,0.0,0.0,1.0),	//MAT_RED_PLASTIC=20;
	Tupla4f(0.0,0.0,0.0,1.0),	//MAT_WHITE_PLASTIC=21;
	Tupla4f(0.0,0.0,0.0,1.0),	//MAT_YELLOW_PLASTIC=22;
	Tupla4f(0.02, 0.02, 0.02, 1.0),	//MAT_BLACK_RUBBER=23;
	Tupla4f(0.0,0.05,0.05,1.0),	//MAT_CYAN_RUBBER=24;
	Tupla4f(0.0,0.05,0.0,1.0),	//MAT_GREEN_RUBBER=25;
	Tupla4f(0.05,0.0,0.0,1.0),	//MAT_RED_RUBBER=26;
	Tupla4f(0.05,0.05,0.05,1.0),	//MAT_WHITE_RUBBER=27;
	Tupla4f(0.05,0.05,0.0,1.0),	//MAT_YELLOW_RUBBER=28;
	Tupla4f(0.2, 0.2, 0.2,1.0),	//MAT_BRIGHT_WHITE=29;
	Tupla4f(0.2, 0.2, 0.2,1.0),	//MAT_LESS_BRIGHT_WHITE=30;
	Tupla4f(0.3, 0.2, 0.2,1.0) //MAT_WARM_WHITE=31;
};

const Tupla4f diffuse[50]=
{
	{0.780392, 0.568627, 0.113725, 1.0},	//MAT_BRASS=0;
	{0.714, 0.4284, 0.18144, 1.0},	//MAT_BRONZE=1;
	{0.4, 0.2368, 0.1036, 1.0},	//MAT_POLISHED_BRONZE=2;
	{0.4, 0.4, 0.4, 1.0},	//MAT_CHROME=3;
	{0.7038, 0.27048, 0.0828, 1.0},	//MAT_COPPER=4;
	{0.5508, 0.2118, 0.066, 1.0},	//MAT_POLISHED_COPPER=5;
	{0.75164, 0.60648, 0.22648, 1.0},	//MAT_GOLD=6;
	{0.34615, 0.3143, 0.0903, 1.0},	//MAT_POLISHED_GOLD=7;
	{0.427451, 0.470588, 0.541176, 1.0},	//MAT_TIN=8;
	{0.50754, 0.50754, 0.50754, 1.0},	//MAT_SILVER=9;
	{0.2775, 0.2775, 0.2775, 1.0},	//MAT_POLISHED_SILVER=10;
	{0.07568, 0.61424, 0.07568, 0.55},	//MAT_EMERALD=11;
	{0.54, 0.89, 0.63, 0.95},	//MAT_JADE=12;
	{0.18275, 0.17, 0.22525, 0.82},	//MAT_OBSIDIAN=13;
	{1.0, 0.829, 0.829, 0.922},	//MAT_PERL=14;
	{0.61424, 0.04136, 0.04136, 0.55},	//MAT_RUBY=15;
	{0.396, 0.74151, 0.69102, 0.8},	//MAT_TURQUOISE=16;
	{0.01, 0.01, 0.01, 1.0},	//MAT_BLACK_PLASTIC=17;
	{0.0,0.50980392,0.50980392,1.0},	//MAT_CYAN_PLASTIC=18;
	{0.1,0.35,0.1,1.0},	//MAT_GREEN_PLASTIC=19;
	{0.5,0.0,0.0,1.0},	//MAT_RED_PLASTIC=20;
	{0.55,0.55,0.55,1.0},	//MAT_WHITE_PLASTIC=21;
	{0.5,0.5,0.0,1.0},	//MAT_YELLOW_PLASTIC=22;
	{0.01, 0.01, 0.01, 1.0},	//MAT_BLACK_RUBBER=23;
	{0.4,0.5,0.5,1.0},	//MAT_CYAN_RUBBER=24;
	{0.4,0.5,0.4,1.0},	//MAT_GREEN_RUBBER=25;
	{0.5,0.4,0.4,1.0},	//MAT_RED_RUBBER=26;
	{0.5,0.5,0.5,1.0},	//MAT_WHITE_RUBBER=27;
	{0.5,0.5,0.4,1.0},	//MAT_YELLOW_RUBBER=28;
	{1.0, 1.0, 1.0, 1.0},	//MAT_BRIGHT_WHITE=29;
	{0.8, 0.8, 0.8, 1.0},	//MAT_LESS_BRIGHT_WHITE=30;
	{1.0, 0.9, 0.8, 1.0} //MAT_WARM_WHITE=31;
};

const Tupla4f specular[50]=
{
	{0.992157, 0.941176, 0.807843, 1.0},	//MAT_BRASS=0;
	{0.393548, 0.271906, 0.166721, 1.0},	//MAT_BRONZE=1;
	{0.774597, 0.458561, 0.200621, 1.0},	//MAT_POLISHED_BRONZE=2;
	{0.774597, 0.774597, 0.774597, 1.0},	//MAT_CHROME=3;
	{0.256777, 0.137622, 0.086014, 1.0},	//MAT_CUPPER=4;
	{0.580594, 0.223257, 0.0695701, 1.0},	//MAT_POLISHED_CUPPER=5;
	{0.628281, 0.555802, 0.366065, 1.0},	//MAT_GOLD=6;
	{0.797357, 0.723991, 0.208006, 1.0},	//MAT_POLISHED_GOLD=7;
	{0.333333, 0.333333, 0.521569, 1.0},	//MAT_TIN=8;
	{0.508273, 0.508273, 0.508273, 1.0},	//MAT_SILVER=9;
	{0.773911, 0.773911, 0.773911, 1.0},	//MAT_POLISHED_SILVER=10;
	{0.633, 0.727811, 0.633, 0.55},	//MAT_EMERALD=11;
	{0.316228, 0.316228, 0.316228, 0.95},	//MAT_JADE=12;
	{0.332741, 0.328634, 0.346435, 0.82},	//MAT_OBSIDIAN=13;
	{0.296648, 0.296648, 0.296648, 0.922},	//MAT_PERL=14;
	{0.727811, 0.626959, 0.626959, 0.55},	//MAT_RUBY=15;
	{0.297254, 0.30829, 0.306678, 0.8},	//MAT_TURQUOISE=16;
	{0.50, 0.50, 0.50, 1.0},	//MAT_BLACK_PLASTIC=17;
	{0.50196078,0.50196078,0.50196078,1.0},	//MAT_CYAN_PLASTIC=18;
	{0.45,0.55,0.45,1.0},	//MAT_GREEN_PLASTIC=19;
	{0.7,0.6,0.6,1.0},	//MAT_RED_PLASTIC=20;
	{0.70,0.70,0.70,1.0},	//MAT_WHITE_PLASTIC=21;
	{0.60,0.60,0.50,1.0},	//MAT_YELLOW_PLASTIC=22;
	{0.4, 0.4, 0.4, 1.0},	//MAT_BLACK_RUBBER=23;
	{0.04,0.7,0.7,1.0},	//MAT_CYAN_RUBBER=24;
	{0.04,0.7,0.04,1.0},	//MAT_GREEN_RUBBER=25;
	{0.7,0.04,0.04,1.0},	//MAT_RED_RUBBER=26;
	{0.7,0.7,0.7,1.0},	//MAT_WHITE_RUBBER=27;
	{0.7,0.7,0.04,1.0},	//MAT_YELLOW_RUBBER=28;
	{0.8, 0.8, 0.8, 1.0},	//MAT_BRIGHT_WHITE=29;
	{0.5, 0.5, 0.5, 1.0},	//MAT_LESS_BRIGHT_WHITE=30;
	{0.2, 0.2, 0.2, 1.0} //MAT_WARM_WHITE=31;
};

const float shine[50]=
{
	27.8974,	//MAT_BRASS=0;
	25.6,	//MAT_BRONZE=1;
	76.8,	//MAT_POLISHED_BRONZE=2;
	76.8,	//MAT_CHROME=3;
	12.8,	//MAT_CUPPER=4;
	51.2,	//MAT_POLISHED_CUPPER=5;
	51.2,	//MAT_GOLD=6;
	83.2,	//MAT_POLISHED_GOLD=7;
	9.84615,	//MAT_TIN=8;
	51.2,	//MAT_SILVER=9;
	89.6,	//MAT_POLISHED_SILVER=10;
	76.8,	//MAT_EMERALD=11;
	12.8,	//MAT_JADE=12;
	38.4,	//MAT_OBSIDIAN=13;
	11.264,	//MAT_PERL=14;
	76.8,	//MAT_RUBY=15;
	12.8,	//MAT_TURQUOISE=16;
	32.0,	//MAT_BLACK_PLASTIC=17;
	32.0,	//MAT_CYAN_PLASTIC=18;
	32.0,	//MAT_GREEN_PLASTIC=19;
	32.0,	//MAT_RED_PLASTIC=20;
	32.0,	//MAT_WHITE_PLASTIC=21;
	32.0,	//MAT_YELLOW_PLASTIC=22;
	10.0,	//MAT_BLACK_RUBBER=23;
	10.0,	//MAT_CYAN_RUBBER=24;
	10.0,	//MAT_GREEN_RUBBER=25;
	10.0,	//MAT_RED_RUBBER=26;
	10.0,	//MAT_WHITE_RUBBER=27;
	10.0,	//MAT_YELLOW_RUBBER=28;
	0.4,	//MAT_BRIGHT_WHITE=29;
	0.35,	//MAT_LESS_BRIGHT_WHITE=30;
	0.35	 //MAT_WARM_WHITE=31;
};



#endif