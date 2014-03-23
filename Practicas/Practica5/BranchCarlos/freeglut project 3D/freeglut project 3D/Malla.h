#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>
//#include <GL/glut.h>

#include "PV3D.h"
#include "Cara.h"

class Malla{
protected:
	int numVertices; 
	PV3D** vertice;
	int numNormales;  //=numCaras, frecuentemente
	PV3D** normal;
	int numCaras;
	Cara** cara;
public:
	Malla(void);
	~Malla(void);
	void dibuja(void);
	void dibujaCamino();
};

