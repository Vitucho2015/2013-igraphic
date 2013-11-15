#include "Scene.h"

Scene::Scene(void)
{
	
	// Scene visible area size
	xLeft= 0.0, xRight= 500.0, yBot= 0.0, yTop= 500.0;

	// Scene variables
	xTriangle= 0.0, yTriangle= 0.0;
	triangleWidth= 100.0, triangleHeight= 50.0;

	// Scene colors
	red=1.0, blue=0.0, green=0.0;


}


Scene::~Scene(void)
{
	cout << "se borra la escena" << endl;
}


void Scene::render()
{
	glBegin(GL_QUADS);
		glVertex2d( xTriangle, yTriangle );
		glVertex2d( xTriangle + triangleWidth, yTriangle );
		glVertex2d( xTriangle + triangleWidth, yTriangle + triangleHeight );
		glVertex2d( xTriangle, yTriangle + triangleHeight );
    glEnd();

	blue = 0.0;
	glColor3f(red,blue,green);

	glBegin ( GL_TRIANGLES ) ;
		glVertex2d( xTriangle, yTriangle );
		glVertex2d( xTriangle + triangleWidth, yTriangle );
		glVertex2d( xTriangle + triangleWidth, yTriangle + triangleHeight );
	glEnd () ; 
}

void Scene::step(void){
	//ball->step();
}


void Scene::cam_right(void)
{
	xRight += 10.0;
	xLeft += 10.0;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xLeft, xRight, yBot, yTop);
}


void Scene::cam_left(void)
{
	xRight -= 10.0;
	xLeft -= 10.0;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xLeft, xRight, yBot, yTop);
}


void Scene::cam_up(void)
{
	yTop += 10.0;
	yBot += 10.0;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xLeft, xRight, yBot, yTop);
}


void Scene::cam_down(void)
{
	yTop -= 10.0;
	yBot -= 10.0;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xLeft, xRight, yBot, yTop);
}


void Scene::cam_in(void)
{
	GLdouble ratio = (xRight-xLeft)/(yTop-yBot);
	GLdouble x_des = 3;
	GLdouble y_des = x_des/ratio;

	if((yTop-yBot<10)||(xRight-xLeft<20)){}
	else{
		yTop -= y_des;
		yBot += y_des;
		xRight -= x_des;
		xLeft += x_des;
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(xLeft, xRight, yBot, yTop);
	}
}


void Scene::cam_out(void)
{
	GLdouble ratio = (xRight-xLeft)/(yTop-yBot);
	GLdouble x_des = 3;
	GLdouble y_des = x_des/ratio;
	
	yTop += y_des;
	yBot -= y_des;
	xRight += x_des;
	xLeft -= x_des;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xLeft, xRight, yBot, yTop);
}

bool Scene::reset(void)
{
	// TODO 
	return false;
}
