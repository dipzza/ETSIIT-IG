#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// Clase Malla3D
//
// *****************************************************************************

Malla3D::Malla3D()
{
	id_vbo_ver = 0;
	id_vbo_tri = 0;
	id_vbo_nor = 0;
	id_vbo_col_solid = 0;
	id_vbo_col_line = 0;
	id_vbo_col_point = 0;
}
// Visualización en modo inmediato con 'glDrawElements'

GLuint Malla3D::CrearVBO(GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram)
{
	GLuint id_vbo;						// resultado: identificador de VBO
	glGenBuffers( 1, & id_vbo );		// crear nuevo VBO, obtener identificador (nunca 0)
	glBindBuffer( tipo_vbo, id_vbo );	// activar el VBO usando su identificador
	
	// esta instrucción hace la transferencia de datos desde RAM hacia GPU
	glBufferData( tipo_vbo, tamanio_bytes, puntero_ram, GL_STATIC_DRAW );
	
	glBindBuffer( tipo_vbo, 0 );		// desactivación del VBO (activar 0)
	return id_vbo;						// devolver el identificador resultado
}


void Malla3D::draw_ModoInmediato(const int modo_visualizacion)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, v.data());
	
	// Si hay iluminación utilizamos las normales y el material, si no los vectores de colores
	if (glIsEnabled(GL_LIGHTING) && m != nullptr)
	{
		glNormalPointer(GL_FLOAT, 0, nv.data());
		m->aplicar();
	}
	else
	{
		if (modo_visualizacion == SOLID)
			glColorPointer(4, GL_FLOAT, 0, color_solid.data());
		else if (modo_visualizacion == LINE)
			glColorPointer(4, GL_FLOAT, 0, color_line.data());
		else if (modo_visualizacion == POINT)
			glColorPointer(4, GL_FLOAT, 0, color_point.data());
	}
	
	glDrawElements(GL_TRIANGLES, num_triangulos * 3, GL_UNSIGNED_INT, f.data());
}

void Malla3D::draw_selection()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	
	glVertexPointer(3, GL_FLOAT, 0, v.data());
	
	glDrawElements(GL_TRIANGLES, num_triangulos * 3, GL_UNSIGNED_INT, f.data());
}

void Malla3D::draw_ModoAjedrez()
{
	std::vector<Tupla3i> f1, f2;
	
	for (int i=0; i < num_triangulos - 1; i+=2)
	{
		f1.push_back(f[i]);
		f2.push_back(f[i+1]);
	}
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, v.data());
	
	color_solid = std::vector<Tupla4f> (v.size(), ROJO);
	glColorPointer(4, GL_FLOAT, 0, color_solid.data());
	glDrawElements(GL_TRIANGLES, f1.size() * 3, GL_UNSIGNED_INT, f1.data());
	
	color_solid = std::vector<Tupla4f> (v.size(), AMARILLO);
	glColorPointer(4, GL_FLOAT, 0, color_solid.data());
	glDrawElements(GL_TRIANGLES, f2.size() * 3, GL_UNSIGNED_INT, f2.data());
}
// -----------------------------------------------------------------------------
// Visualización en modo diferido con 'glDrawElements' (usando VBOs)

void Malla3D::draw_ModoDiferido(const int modo_visualizacion)
{
   // (la primera vez, se deben crear los VBOs y guardar sus identificadores en el objeto)
	if (id_vbo_ver == 0)
	{
		id_vbo_ver = CrearVBO( GL_ARRAY_BUFFER, v.size() * sizeof(float) * 3, v.data());
	}
	if (id_vbo_tri == 0)
	{
		id_vbo_tri = CrearVBO( GL_ELEMENT_ARRAY_BUFFER, f.size() * sizeof(int) * 3, f.data());
	}
	if (id_vbo_col_solid == 0)
	{
		id_vbo_col_solid = CrearVBO( GL_ARRAY_BUFFER, color_solid.size() * sizeof(float) * 4, color_solid.data());
	}
	if (id_vbo_col_line == 0)
	{
		id_vbo_col_line = CrearVBO( GL_ARRAY_BUFFER, color_line.size() * sizeof(float) * 4, color_line.data());
	}
	if (id_vbo_col_point == 0)
	{
		id_vbo_col_point = CrearVBO( GL_ARRAY_BUFFER, color_point.size() * sizeof(float) * 4, color_point.data());
	}
	if (id_vbo_nor == 0)
	{
		id_vbo_nor = CrearVBO( GL_ARRAY_BUFFER, nv.size() * sizeof(float) * 3, nv.data());
	}
	
	glEnableClientState(GL_VERTEX_ARRAY);
	
	glBindBuffer( GL_ARRAY_BUFFER, id_vbo_ver ); 		// activar VBO de vértices
	glVertexPointer( 3, GL_FLOAT, 0, 0 );				// especifica formato y offset (=0)
	glBindBuffer( GL_ARRAY_BUFFER, 0 );					// desactivar VBO de vértices.
	
	if (glIsEnabled(GL_LIGHTING) && m != nullptr)
	{
		glEnableClientState(GL_NORMAL_ARRAY);
		glBindBuffer( GL_ARRAY_BUFFER, id_vbo_nor );	// VBO de normales
		glNormalPointer(GL_FLOAT, 0, 0);
		glBindBuffer( GL_ARRAY_BUFFER, 0 );
		m->aplicar();
	}
	else
	{
		glEnableClientState(GL_COLOR_ARRAY);
		// Activar VBO de colores según el modo de visualizacionNARANJA
		if (modo_visualizacion == SOLID)
		{
			glBindBuffer( GL_ARRAY_BUFFER, id_vbo_col_solid );
			glColorPointer(4, GL_FLOAT, 0, 0 );				// especifica formato y offset (=0)
			glBindBuffer( GL_ARRAY_BUFFER, 0 );					// desactivar VBO de colores.
		}
		else if (modo_visualizacion == LINE)
		{
			glBindBuffer( GL_ARRAY_BUFFER, id_vbo_col_line );
			glColorPointer(4, GL_FLOAT, 0, 0 );				// especifica formato y offset (=0)
			glBindBuffer( GL_ARRAY_BUFFER, 0 );					// desactivar VBO de colores.
		}
		else if (modo_visualizacion == POINT)
		{
			glBindBuffer( GL_ARRAY_BUFFER, id_vbo_col_point );
			glColorPointer(4, GL_FLOAT, 0, 0 );				// especifica formato y offset (=0)
			glBindBuffer( GL_ARRAY_BUFFER, 0 );					// desactivar VBO de colores.
		}
	}
	
	// visualizar triángulos con glDrawElements (puntero a tabla == 0)
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_tri );// activar VBO de triángulos
	glDrawElements( GL_TRIANGLES, num_triangulos * 3, GL_UNSIGNED_INT, 0 ) ;
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );			// desactivar VBO de triángulos
}

void Malla3D::draw(const int modo_dibujado, const int modo_visualizacion)
{
	if (textura != nullptr)
	{
		glEnable(GL_TEXTURE_2D);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		textura->activar();
		glTexCoordPointer(2, GL_FLOAT, 0, ct.data());
	}
	
	if (modo_dibujado == 0)
		draw_ModoInmediato(modo_visualizacion);
	else if (modo_dibujado == 1)
		draw_ModoDiferido(modo_visualizacion);
	else if (modo_dibujado == 2)
		draw_ModoAjedrez();
	
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Malla3D::calcular_normales()
{
	std::vector<Tupla3f> nc;	// Normales de las caras
	Tupla3f arist_a, arist_b;
	
	// Calculamos las normales de la caras haciendo el producto vectorial de dos aristas de la cara
	for (int i = 0; i < f.size(); ++i)
	{
		arist_a = v[f[i][1]] - v[f[i][0]];
		arist_b = v[f[i][2]] - v[f[i][0]];
		nc.push_back(arist_a.cross(arist_b).normalized());
	}
	
	// Calculamos las normales de los vertices sumando las normales de las caras adyyacentes
	nv.resize(v.size());
	for (int i = 0; i < f.size(); ++i)
		for (int j = 0; j < 3; ++j)
			nv[f[i][j]] = nv[f[i][0]] + nc[i];
	
	// Normalizamos las normales de los vertices
	for (int i = 0; i < nv.size(); ++i)
		nv[i] = nv[i].normalized();
}

void Malla3D::setMaterial(const int MAT)
{
	if (m == nullptr)
		m = new Material(ambient[MAT], diffuse[MAT], specular[MAT], shine[MAT]);
	else
		*m = Material(ambient[MAT], diffuse[MAT], specular[MAT], shine[MAT]);
}

void Malla3D::setTextura(const std::string &archivo)
{
	if (textura == nullptr)
		textura = new Textura(archivo);
	else
		*textura = Textura(archivo);
}
