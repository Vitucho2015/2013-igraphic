#pragma once
#include "drawablepolygon.h"
#include "Obstacle.h"
class Circle :	public DrawablePolygon , public Obstacle
{
private:


public:
	Circle(void);
	~Circle(void);

	
	void render(void);
	void collide(Ball *ball);
};
