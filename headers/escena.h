#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "cilindro.h"
#include "cono.h"
#include "luz.h"
#include "esfera.h"
#include "silla.h"
#include "cuadro.h"
#include "camara.h"
#include <vector>

typedef enum {NADA, SELOBJETO, SELVISUALIZACION, SELDIBUJADO, SELVISUALIZACIONLUZ, SELANIMACION, SELMOVJERARQUICO, SELCAMARA} menu;
class Escena
{

   private:

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection();
	void change_observer();
	void clear_window();
	bool fastRotation, mov_camara;
	int xant, yant;
	
	// Variables de visualización
	menu modoMenu=NADA;
	bool showCube, showTetrahedron, showPly, showTapas;
	bool mLine, mPoint, mSolid, mChess, mLight, mFlat;
    bool animation, animation_increase;
	bool light_0, light_1, light_2, light_3, light_4, light_5, light_6, light_7;
	bool diferido, varAlfa;
    int gradoLibertad, sel_vel_anim, camaraActiva, seleccionado;
	bool obj_selected;
	float vel_altura, vel_giro, vel_inclinacion, vel_luz;
   
	// Objetos de la escena
	Ejes ejes;
	Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
	Tetraedro * tetraedro = nullptr ; // es importante inicializarlo a 'nullptr'
	ObjPLY * ply = nullptr;
	Cilindro * papelera_ext = nullptr;
	Cilindro * papelera_int = nullptr;
	Esfera * esfera = nullptr;
	Cono * cono = nullptr;
	ObjRevolucion * peon = nullptr;
	LuzDireccional * luz_dir =  nullptr;
	LuzPosicional * luz_pos =  nullptr;
	Silla * silla = nullptr;
	Cuadro * cuadro = nullptr;
	Cuadro * suelo = nullptr;
	Cuadro * pared = nullptr;
	std::vector<Camara> camaras;
	

   
   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;
	void dibujar_objetos(const int modo_dibujado, const int modo_visualizacion);
	void dibujar_seleccion();

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );
	void clickRaton(int boton, int estado, int x, int y);
	void ratonMovido(int x, int y);
    void animarModeloJerarquico();

};
#endif
