#pragma once

#include "Obstacle.h"
#include "DrawablePolygon.h"

class Triangle : public Obstacle, public DrawablePolygon
{
private:

public:
	Triangle(void);
	~Triangle(void);
	Triangle(vector<PV2D*> *v);
	Triangle(PV2D* p1, PV2D* p2, PV2D* p3);
	Triangle(PV2D* p, GLdouble r);
	
	void render(void);
	void collide(Ball *ball);
	void doNormals(void);
	void doVertex(void);
};

