// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"
#include "material.h"
#include "textura.h"

// Constantes definidas para modos de visualizacion
const int
	SOLID = 0,
	LINE = 1,
	POINT = 2;

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

class Malla3D
{
	private:
		Material *m = nullptr;
		Textura *textura = nullptr;

	public:
		Malla3D();

		// dibuja el objeto en modo inmediato
		void draw_ModoInmediato(const int modo_visualizacion);
		
		// dibuja el objeto en modo diferido (usando VBOs)
		void draw_ModoDiferido(const int modo_visualizacion);
		
		// dibuja el objeto en modo inmediato ajedrez
		void draw_ModoAjedrez();
		
		// dibuja en modo inmediato seleccion
		void draw_selection();

		// función que redibuja el objeto
		// está función llama a 'draw_ModoInmediato' (modo inmediato)
		// a 'draw_ModoDiferido' (modo diferido, VBOs)
		// o a 'draw_ModoAjedrez (modo inmediato, cada mitad de las caras de un color diferente)
		void draw(const int modo_dibujado, const int modo_visualizacion) ;
		
		GLuint CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram);
		
		void setMaterial(const int mat);
		
		void setTextura(const std::string &archivo);


	protected:

		void calcular_normales() ; // calcula tabla de normales de vértices

		std::vector<Tupla3f> v ;   // una terna de 3 floats por cada vértice
		std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo
		std::vector<Tupla2f> ct; // tabla de coordenadas de textura
		
		std::vector<Tupla4f> color_solid ; // una terna de 4 floats por cada color
		std::vector<Tupla4f> color_line ; // una terna de 4 floats por cada color
		std::vector<Tupla4f> color_point ; // una terna de 4 floats por cada color
		
		std::vector<Tupla3f> nv ; // una terna de 3 floats por cada normal de vértice
		
		GLuint id_vbo_ver, id_vbo_tri, id_vbo_nor, id_vbo_col_solid, id_vbo_col_line, id_vbo_col_point; // Identificadores de VBOs
		
		int num_triangulos;
} ;

#endif
