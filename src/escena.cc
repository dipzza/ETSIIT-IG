#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....


//**************************************************************************
// constructor de la e15scena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
	Front_plane      	= 50.0;
	Back_plane       	= 2000.0;
	vel_altura			= 0.02;
	vel_giro			= 0.02;
	vel_inclinacion		= 0.02;
	vel_luz				= 0.02;
    gradoLibertad       = 0;
	fastRotation 		= false;
	showCube			= false;
	showTetrahedron		= false;
	showPly				= false;
	showTapas			= true;
	mLine				= false;
	mPoint				= false;
	mSolid				= true;
	mChess				= false;
	mLight				= true;
	mFlat				= false;
	light_0				= true;
	light_1				= true;
	light_2				= false;
	light_3				= false;
	light_4				= false;
	light_5				= false;
	light_6				= false;
	light_7				= false;
	diferido			= true;
	varAlfa				= true;
    animation			= false;
	animation_increase 	= true;
	camaraActiva 		= 0;
	mov_camara			= false;
	obj_selected		= false;
	seleccionado 		= -1;

    ejes.changeAxisSize( 5000 );

    // crear los objetos de la escena
	cubo = new Cubo(50);
	tetraedro = new Tetraedro();
	ply = new ObjPLY("./plys/mesa.ply");
	papelera_ext = new Cilindro(20, 30, 65, 25, false, true);
	papelera_int = new Cilindro(20, 30, 65, 25, false, true, true);
	esfera = new Esfera(25, 30, 30);
	cono = new Cono(10, 30, 80, 30);
	peon = new ObjRevolucion("./plys/peon.ply", 50);
	luz_dir = new LuzDireccional(0, {0.1, 0.1, 0.1, 1}, BLANCO, BLANCO, {-0.1, -1});
	luz_pos = new LuzPosicional(1, {400, 40, -375}, NEGRO, AZUL, BLANCO);
	silla = new Silla(5);
	cuadro = new Cuadro(80);
	suelo = new Cuadro(1000);
	pared = new Cuadro(1000);
	
	// asignar materiales
	papelera_ext->setMaterial(MAT_SILVER);
	papelera_int->setMaterial(MAT_SILVER);
	esfera->setMaterial(MAT_RUBY);
	cono->setMaterial(MAT_TURQUOISE);
	peon->setMaterial(MAT_CHROME);
	ply->setMaterial(MAT_BRASS);

	cuadro->setMaterial(MAT_WARM_WHITE);
	suelo->setMaterial(MAT_WARM_WHITE);
	pared->setMaterial(MAT_WARM_WHITE);
	
	cubo->setMaterial(MAT_TURQUOISE);
	tetraedro->setMaterial(MAT_TURQUOISE);
	
	// asignar textura
	cuadro->setTextura("./textures/reno.jpg");
	suelo->setTextura("./textures/suelo.jpg");
	pared->setTextura("./textures/stonewall.jpg");
}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable(GL_DEPTH_TEST);	// se habilita el z-bufer
	glEnable(GL_CULL_FACE);
	glEnable(GL_NORMALIZE);
	
	glPointSize(4);
	glLineWidth(1.5);
	
	Width  = UI_window_width/10;
	Height = UI_window_height/10;
	
	// Camaras
	camaras.push_back(Camara(PERSPECTIVA, {0, 150, 350}, {0, 1, 0}, Width, Height, Front_plane, Back_plane));
	
	camaras.push_back(Camara(ORTOGONAL, {-200, 200, 400}, {0, 1, 0}, Width*6, Height*6, 25, Back_plane));
	
	camaras.push_back(Camara(PERSPECTIVA, {0, 120, -400}, {0, -1, 0}, Width, Height, Front_plane, Back_plane));

	change_projection();
	glViewport( 0, 0, UI_window_width, UI_window_height);
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	
	change_observer();
    ejes.draw();
	
	int modo_dibujado = diferido ? 1 : 0;
	
	if (mLight)
	{
		glEnable(GL_LIGHTING);
		
		if (mFlat)
			glShadeModel(GL_FLAT);
		else
			glShadeModel(GL_SMOOTH);
	}
	
	if (mLine)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		dibujar_objetos(modo_dibujado, LINE);
	}
	if (mPoint)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		dibujar_objetos(modo_dibujado, POINT);
	}
	if (mSolid)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		dibujar_objetos(modo_dibujado, SOLID);
	}
	if (mChess)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		dibujar_objetos(2, SOLID);
	}
	
	if (mLight)
		glDisable(GL_LIGHTING);
}

void Escena::dibujar_objetos(const int modo_dibujado, const int modo_visualizacion)
{
	if (light_0)
			luz_dir->activar();
		else
			luz_dir->desactivar();
		
		if (light_1)
			luz_pos->activar();
		else
			luz_pos->desactivar();
		
	glPushMatrix();
		glTranslatef(0, 0, -100);
		silla->draw(modo_dibujado, modo_visualizacion);
	glPopMatrix();
	glPushMatrix();
		glPushMatrix();
			glTranslatef(0, 0, 75);
			glScalef(0.37, 0.37, 0.37);
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			ply->draw(modo_dibujado, modo_visualizacion);
		glPopMatrix();
		glPushMatrix();
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			suelo->draw(modo_dibujado, modo_visualizacion);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 250, -500);
			glScalef(1, 0.5, 1);
			pared->draw(modo_dibujado, modo_visualizacion);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(500, 250, 0);
			glRotatef(-90.0, 0.0, 1.0, 0.0);
			glScalef(1, 0.5, 1);
			pared->draw(modo_dibujado, modo_visualizacion);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-500, 250, 0);
			glRotatef(90.0, 0.0, 1.0, 0.0);
			glScalef(1, 0.5, 1);
			pared->draw(modo_dibujado, modo_visualizacion);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-6, 67, 68);
			glRotatef(180.0, 0.0, 1.0, 0.0);
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			cuadro->draw(modo_dibujado, modo_visualizacion);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(75, 1, 0);
			papelera_ext->draw(modo_dibujado, modo_visualizacion);
			papelera_int->draw(modo_dibujado, modo_visualizacion);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-130, 0, -75);
			esfera->draw(modo_dibujado, modo_visualizacion);
		glPopMatrix();
		glPushMatrix();
			glTranslatef(425, 0, -400);
			cono->draw(modo_dibujado, modo_visualizacion);
		glPopMatrix();
		glTranslatef(55, 81, 85);
		glScalef(10, 10, 10);
		peon->draw(modo_dibujado, modo_visualizacion);
	glPopMatrix();
}

void Escena::dibujar_seleccion()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	glDisable(GL_DITHER);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	
	glPushMatrix();
		glTranslatef(0, 0, -100);
		glColor3ub(0, 0, 1);// silla, mesa, suelo, pared, paredDer, paredIz, cuadro, papelera, esfera, cono, peon
		silla->draw_selection();
	glPopMatrix();
	glPushMatrix();
		glPushMatrix();
			glTranslatef(0, 0, 75);
			glScalef(0.37, 0.37, 0.37);
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			glColor3ub(0, 0, 2);
			ply->draw_selection();
		glPopMatrix();
		glPushMatrix();
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			glColor3ub(0, 0, 3);
			suelo->draw_selection();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(0, 250, -500);
			glScalef(1, 0.5, 1);
			glColor3ub(0, 0, 4);
			pared->draw_selection();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(500, 250, 0);
			glRotatef(-90.0, 0.0, 1.0, 0.0);
			glScalef(1, 0.5, 1);
			glColor3ub(0, 0, 5);
			pared->draw_selection();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-500, 250, 0);
			glRotatef(90.0, 0.0, 1.0, 0.0);
			glScalef(1, 0.5, 1);
			glColor3ub(0, 0, 6);
			pared->draw_selection();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-6, 67, 68);
			glRotatef(180.0, 0.0, 1.0, 0.0);
			glRotatef(-90.0, 1.0, 0.0, 0.0);
			glColor3ub(0, 0, 7);
			cuadro->draw_selection();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(75, 1, 0);
			glColor3ub(0, 0, 8);
			papelera_ext->draw_selection();
			papelera_int->draw_selection();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(-130, 0, -75);
			glColor3ub(0, 0, 9);
			esfera->draw_selection();
		glPopMatrix();
		glPushMatrix();
			glTranslatef(425, 0, -400);
			glColor3ub(0, 0, 10);
			cono->draw_selection();
		glPopMatrix();
		glTranslatef(55, 81, 85);
		glScalef(10, 10, 10);
		glColor3ub(0, 0, 11);
		peon->draw_selection();
	glPopMatrix();
	
	glEnable(GL_DITHER);
}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
	using namespace std ;
	cout << "Tecla pulsada: '" << tecla << "'" << endl;
	bool salir=false;

	if (toupper(tecla) == 'Q')
	{
		if (modoMenu!=NADA)
		{
			modoMenu=NADA;
			cout << "Modo: 'Seleccion de modo'" << endl;
		}
		else {
			salir=true ;
		}
	}
	else
	{
		if (modoMenu==NADA)
		{
			switch (toupper(tecla))
			{
				case 'O' :
					// ESTAMOS EN MODO SELECCION DE OBJETO
					modoMenu=SELOBJETO;
					cout << "Modo: 'Seleccion de objeto'" << endl;
					break ;
				case 'V' :
					// ESTAMOS EN MODO SELECCION DE MODO DE VISUALIZACION
					modoMenu=SELVISUALIZACION;
					cout << "Modo: 'Seleccion de modo de visualizacion'" << endl;
					break ;
				case 'D' :
					// ESTAMOS EN MODO SELECCION DE DIBUJADO
					modoMenu=SELDIBUJADO;
					cout << "Modo: 'Seleccion de modo de dibujado'" << endl;
					break ;
				case 'M' :
					animation = false;
					cout << "Modo: 'Seleccion de grados de libertad'" << endl;
					modoMenu = SELMOVJERARQUICO;
					break;
				case 'A' :
					animation = !animation;
					if (animation)
					{
						cout << "Modo: 'Seleccion de velocidad de animación'" << endl;
						modoMenu = SELANIMACION;
					}
					break;
				case 'C' :
					cout << "Modo: 'Seleccion de camara'" << endl;
					modoMenu = SELCAMARA;
				case 'R' :
					fastRotation = !fastRotation;
					break;
				default :
					cout << "Opción no válida" << endl;
			}
		}
		else if (modoMenu == SELOBJETO)
		{
			switch (toupper(tecla))
			{
				case 'C' :
					showCube = !showCube;
					break;
				case 'T' :
					showTetrahedron = !showTetrahedron;
					break;
				case 'P' :
					showPly = !showPly;
					break;
				case 'F' :
					showTapas = !showTapas;
					papelera_ext->mostrarTapas(showTapas);
					esfera->mostrarTapas(showTapas);
					cono->mostrarTapas(showTapas);
					peon->mostrarTapas(showTapas);
					break;
				default :
					cout << "Opción no válida" << endl;
			}
		}
		else if (modoMenu == SELVISUALIZACION)
		{
			switch (toupper(tecla))
			{
				case 'P' :
					mPoint = !mPoint;
					break;
				case 'L' :
					mLine = !mLine;
					break;
				case 'S' :
					mSolid = !mSolid;
					break;
				case 'A' :
					mChess = !mChess;
					break;
				case 'I' :
					mLight = !mLight;
					if (mLight)
					{
						cout << "Modo: 'Seleccion de Iluminación'" << endl;
						modoMenu = SELVISUALIZACIONLUZ;
					}
					break;
				case 'F' :
					mFlat = !mFlat;
					break;
				default :
					cout << "Opción no válida" << endl;
			}
		}
		else if (modoMenu == SELDIBUJADO)
		{
			switch (toupper(tecla))
			{
				case '1' :
					diferido = false;
					break;
				case '2' :
					diferido = true;
					break;
				default :
					cout << "Opción no válida" << endl;
			}
		}
		else if (modoMenu == SELVISUALIZACIONLUZ)
		{
			switch (toupper(tecla))
			{
				case 'I' :
					mLight = false;
					modoMenu = SELVISUALIZACION;
					break;
				case 'F' :
					mFlat = !mFlat;
					break;
				case '0' :
					light_0 = !light_0;
					break;
				case '1' :
					light_1 = !light_1;
					break;
				case '2' :
					light_2 = !light_2;
					break;
				case '3' :
					light_3 = !light_3;
					break;
				case '4' :
					light_4 = !light_4;
					break;
				case '5' :
					light_5 = !light_5;
					break;
				case '6' :
					light_6 = !light_6;
					break;
				case '7' :
					light_7 = !light_7;
					break;
				case 'A' :
					varAlfa = true;
					break;
				case 'B' :
					varAlfa = false;
					break;
				case '>' :
					if (varAlfa)
						luz_dir->variarAnguloAlpha(0.1);
					else
						luz_dir->variarAnguloBeta(0.1);
					break;
				case '<' :
					if (varAlfa)
						luz_dir->variarAnguloAlpha(-0.1);
					else
						luz_dir->variarAnguloBeta(-0.1);
					break;
				default :
					cout << "Opción no válida" << endl;
			}
		}
		else if (modoMenu == SELMOVJERARQUICO)
		{
			switch (toupper(tecla))
			{
				case '0' :
					gradoLibertad = 0;
					break;
				case '1' :
					gradoLibertad = 1;
					break;
				case '2' :
					gradoLibertad = 2;
					break;
				case '+' :
					if (gradoLibertad == 0)
						silla->modificaAltura(0.02);
					else if (gradoLibertad == 1)
						silla->modificaGiro(0.02);
					else if (gradoLibertad == 2)
						silla->modificaInclinacion(0.02);
					break;
				case '-' :
					if (gradoLibertad == 0)
						silla->modificaAltura(-0.02);
					else if (gradoLibertad == 1)
						silla->modificaGiro(-0.02);
					else if (gradoLibertad == 2)
						silla->modificaInclinacion(-0.02);
				default :
					cout << "Opción no válida" << endl;
			}
		}
		else if (modoMenu == SELANIMACION)
		{
			switch (toupper(tecla))
			{
				case '0' :
					sel_vel_anim = 0;
					break;
				case '1' :
					sel_vel_anim = 1;
					break;
				case '2' :
					sel_vel_anim = 2;
					break;
				case '3' :
					sel_vel_anim = 3;
					break;
				case '4' :
					sel_vel_anim = 4;
					break;
				case '+' :
					if (sel_vel_anim == 0)
					{
						if (vel_altura < 0.20)
							vel_altura += 0.005;
						
						if (vel_giro < 0.20)
							vel_giro += 0.005;
						
						if (vel_inclinacion < 0.20)
							vel_inclinacion += 0.005;
						
						if (vel_luz < 0.20)
							vel_luz += 0.005;
					}
					else if (sel_vel_anim == 1)
					{
						if (vel_altura < 0.20)
							vel_altura += 0.005;
					}
					else if (sel_vel_anim == 2)
					{
						if (vel_giro < 0.20)
							vel_giro += 0.005;
					}
					else if (sel_vel_anim == 3)
					{
						if (vel_inclinacion < 0.20)
							vel_inclinacion += 0.005;
					}
					else if (sel_vel_anim == 4)
					{
						if (vel_luz < 0.20)
							vel_luz += 0.005;
					}
					break;
				case '-' :
					if (sel_vel_anim == 0)
					{
						if (vel_altura >= 0.005)
							vel_altura -= 0.005;
						
						if (vel_giro >= 0.005)
							vel_giro -= 0.005;
						
						if (vel_inclinacion >= 0.005)
							vel_inclinacion -= 0.005;
						
						if (vel_luz >= 0.005)
							vel_luz -= 0.005;
					}
					else if (sel_vel_anim == 1)
					{
						if (vel_altura >= 0.005)
							vel_altura -= 0.005;
					}
					else if (sel_vel_anim == 2)
					{
						if (vel_giro >= 0.005)
							vel_giro -= 0.005;
					}
					else if (sel_vel_anim == 3)
					{
						if (vel_inclinacion >= 0.005)
							vel_inclinacion -= 0.005;
					}
					else if (sel_vel_anim == 4)
					{
						if (vel_luz >= 0.005)
							vel_luz -= 0.005;
					}
					break;
				default :
					cout << "Opción no válida" << endl;
			}
		}
		else if (modoMenu == SELCAMARA)
		{
			float mult = 4;
			
			switch(tecla)
			{
				case '0' :
					camaraActiva = 0;
					obj_selected = false;
					change_projection();
					break;
				case '1' :
					camaraActiva = 1;
					obj_selected = false;
					change_projection();
					break;
				case '2' :
					camaraActiva = 2;
					obj_selected = false;
					change_projection();
					break;
				case 'w' :
					camaras[camaraActiva].mover(0, 0, mult, !obj_selected);
					break;
				case 'a' :
					if (!obj_selected)
						camaras[camaraActiva].mover(-mult, 0, 0, !obj_selected);
					break;
				case 's' :
					camaras[camaraActiva].mover(0, 0, -mult, !obj_selected);
					break;
				case 'd' :
					if (!obj_selected)
						camaras[camaraActiva].mover(mult, 0, 0, !obj_selected);
					break;
				case 'W' :
					camaras[camaraActiva].mover(0, 0, mult * 3, !obj_selected);
					break;
				case 'A' :
					if (!obj_selected)
						camaras[camaraActiva].mover(-mult * 3, 0, 0, !obj_selected);
					break;
				case 'S' :
						camaras[camaraActiva].mover(0, 0, -mult * 3, !obj_selected);
					break;
				case 'D' :
					if (!obj_selected)
						camaras[camaraActiva].mover(mult * 3, 0, 0, !obj_selected);
					break;
				case ' ' :
					if (!obj_selected)
						if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
							camaras[camaraActiva].mover(0, -mult, 0, !obj_selected);
						else
							camaras[camaraActiva].mover(0, mult, 0, !obj_selected);
					break;
				default :
					cout << "Opción no válida" << endl;
			}
		}
		else
			cout << "Opción no válida" << endl;
   }
   
   return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
	float mult = M_PI / 180;
	if (glutGetModifiers() == GLUT_ACTIVE_SHIFT)
		mult *= 3;
	
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         camaras[camaraActiva].girar_alrededor(0, -mult);
         break;
	   case GLUT_KEY_RIGHT:
         camaras[camaraActiva].girar_alrededor(0, mult);
         break;
	   case GLUT_KEY_UP:
         camaras[camaraActiva].girar_alrededor(-mult, 0);
         break;
	   case GLUT_KEY_DOWN:
         camaras[camaraActiva].girar_alrededor(mult, 0);
         break;
	   case GLUT_KEY_PAGE_UP:
         camaras[camaraActiva].zoom(0.1);
		 change_projection();
         break;
	   case GLUT_KEY_PAGE_DOWN:
         camaras[camaraActiva].zoom(-0.1);
		 change_projection();
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion que se invoca cuando se actúa sobre un botón del ratón
//**************************************************************************

void Escena::clickRaton(int boton, int estado, int x, int y)
{
	if (boton == GLUT_RIGHT_BUTTON)
	{
		if (estado == GLUT_DOWN)
		{
			xant = x;
			yant = y;
			mov_camara = true;
		}
		else
			mov_camara = false;
	}
	else if (boton == GLUT_LEFT_BUTTON)
	{
		if (estado == GLUT_DOWN)
		{
 			dibujar_seleccion();
			
			GLubyte pixels[3];
			glReadPixels(x, Height * 10 - y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixels);
			
			if (pixels[2] == seleccionado)
			{
				obj_selected = false;
				seleccionado = -1;
			}
			else
			{
				seleccionado = pixels[2];
				switch (pixels[2]) // silla-1, mesa-2, suelo-3, pared-4, paredDer-5, paredIz-6, cuadro-7, papelera-8, esfera-9, cono-10, peon-11
				{
					case 1 :
						obj_selected = true;
						camaras[camaraActiva].setAt({0, 40, -100});
						break;
					case 2 :
						obj_selected = true;
						camaras[camaraActiva].setAt({0, 35, 75});
						break;
					case 3 :
						obj_selected = true;
						camaras[camaraActiva].setAt({0, 0, 0});
						break;
					case 4 :
						obj_selected = true;
						camaras[camaraActiva].setAt({0, 250, -500});
						break;
					case 5 :
						obj_selected = true;
						camaras[camaraActiva].setAt({500, 250, 0});
						break;
					case 6 :
						obj_selected = true;
						camaras[camaraActiva].setAt({-500, 250, 0});
						break;
					case 7 :
						obj_selected = true;
						camaras[camaraActiva].setAt({-6, 67, 68});
						break;
					case 8 :
						obj_selected = true;
						camaras[camaraActiva].setAt({75, 32, 0});
						break;
					case 9 :
						obj_selected = true;
						camaras[camaraActiva].setAt({-130, 0, -75});
						break;
					case 10 :
						obj_selected = true;
						camaras[camaraActiva].setAt({425, 0, -400});
						break;
					case 11 :
						obj_selected = true;
						camaras[camaraActiva].setAt({55, 83, 85});
						break;
						
				}
			}
		}
	}
	else if (boton == 4)
	{
		if (estado == GLUT_DOWN)
		{
			camaras[camaraActiva].zoom(0.1);
			change_projection();
		}
	}
	else if (boton == 3)
	{
		if (estado == GLUT_DOWN)
		{
			camaras[camaraActiva].zoom(-0.1);
			change_projection();
		}
	}
}

//**************************************************************************
// Funcion que se invoca cuando se mueve el ratón
//**************************************************************************

void Escena::ratonMovido(int x, int y)
{
	if (mov_camara)
	{
		if (obj_selected)
			camaras[camaraActiva].girar_alrededor(2*M_PI/365 * (y - yant), 2*M_PI/365 * (x - xant));
		else
			camaras[camaraActiva].girar_primera_persona(2*M_PI/365 * (y - yant), 2*M_PI/365 * (x - xant));
		xant = x;
		yant = y;
	}
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//**************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   camaras[camaraActiva].setObservador();
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
//
//**************************************************************************
void Escena::change_projection()
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   camaras[camaraActiva].setProyeccion();
}

//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//**************************************************************************
void Escena::redimensionar( int newWidth, int newHeight )
{
	Width  = newWidth/10;
	Height = newHeight/10;
	
	camaras[0].setWidth(Width);
	camaras[0].setHeight(Height);
	
	camaras[1].setWidth(Width*6);
	camaras[1].setHeight(Height*6);
	
	camaras[2].setWidth(Width);
	camaras[2].setHeight(Height);
	
	change_projection();
	glViewport( 0, 0, newWidth, newHeight );
}

void Escena::animarModeloJerarquico()
{
	if (animation)
	{
		luz_pos->animarAzul(vel_luz);
		
		silla->modificaAltura(vel_altura);
		silla->modificaGiro(vel_giro);
		silla->modificaInclinacion(vel_inclinacion);
	}
}
