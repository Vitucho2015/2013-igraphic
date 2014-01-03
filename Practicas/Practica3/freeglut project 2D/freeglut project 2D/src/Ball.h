//Carlos Giraldo
//Raquel Peces
#pragma once
#include "DrawablePolygon.h"
class Ball : public DrawablePolygon
{
private:
	PV2D* vector;
	
public:
	Ball(void);
	~Ball(void);
	Ball(PV2D *c, GLdouble r);

	void forward(GLdouble t);
	void bounce(PV2D* n);
	void render(void){ 
		cout << "hago un render de mi pelotita" << endl;

	}
	PV2D* getVector(void);
	void initBall();
};

