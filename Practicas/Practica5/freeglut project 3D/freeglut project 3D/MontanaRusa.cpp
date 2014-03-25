#include "MontanaRusa.h"


//---------------------------------------------------------------------------

MontanaRusa::MontanaRusa(GLfloat R,GLfloat r,GLfloat d,int NP,int NQ,GLfloat tam) : Malla(NP*NQ,NP*NQ,NP*NQ)
{
    this->R=R;
    this->r=r;
    this->d=d;
    this->NP=NP;
    this->NQ=NQ;
    this->tam=tam;
    this->nVueltas=calculaVueltas();
    car= new Car(tam*0.9,tam*0.9,tam*0.9);
    acumCoche=0;
}
MontanaRusa::~MontanaRusa()
{
    delete car;
}
//--------------------------------------------------------------------------

GLfloat MontanaRusa::fDerivateX(GLfloat t)
{
	return -3*sin(t);
}

GLfloat MontanaRusa::fDerivateY(GLfloat t)
{
        return -3*sin(1.5*t);
}

GLfloat MontanaRusa::fDerivateZ(GLfloat t)
{
        return 3*cos(t);
}
//-----------------------------------------
GLfloat MontanaRusa::sDerivateX(GLfloat t)
{
	return -3*cos(t);
}

GLfloat MontanaRusa::sDerivateY(GLfloat t)
{
        return -4.5*cos(1.5*t);
}
GLfloat MontanaRusa::sDerivateZ(GLfloat t)
{
        return -3*sin(t);
}

//-------------------------------------------------------------------------
GLfloat MontanaRusa::functionX(GLfloat t)
{
	return 3*cos(t);
}

GLfloat MontanaRusa::functionY(GLfloat t)
{
	return 2*cos(t*1.5);
}

GLfloat MontanaRusa::functionZ(GLfloat t)
{
	return 3*sin(t);
}

//-------------------------------------------------------------------------

PV3D* MontanaRusa::function(GLfloat t)
{
        GLfloat x= functionX(t);
		GLfloat y= functionY(t);
        GLfloat z= functionZ(t);
        return new PV3D(x,y,z);
}
PV3D* MontanaRusa::fDerivate(GLfloat t)
{
        GLfloat x= fDerivateX(t);
		GLfloat y= fDerivateY(t);
        GLfloat z= fDerivateZ(t);
        return new PV3D(x,y,z);
}
PV3D* MontanaRusa::sDerivate(GLfloat t)
{
        GLfloat x= sDerivateX(t);
		GLfloat y= sDerivateY(t);
        GLfloat z= sDerivateZ(t);
		return new PV3D(x,y,z);
}

void MontanaRusa::build(){
     
	GLfloat intervaloToma = 4*M_PI/NQ;
	
	//construimos un objeto con el lapiz

	Poligon *poli = new Poligon(new PV3D(),NP,tam);  // un pol�gono del tama�o y con los lados que queremos
    vector<PV3D*>* puntos= poli->getVertex();  
        
    for(int i=0;i<NQ;i++)
    {
            GLfloat toma=intervaloToma*i;
            
            PV3D* fderivate = fDerivate(toma);
			PV3D* sderivate = sDerivate(toma);

			PV3D* Tt=fDerivate(toma); Tt->normalize();
            PV3D* Bt=fderivate->crossProduct(sderivate); Bt->normalize();
            PV3D* Nt=Bt->crossProduct(Tt);
            PV3D* Ct=function(toma);

            for(int j=0;j<NP;j++)
            {
                   
                int numvertice=NP*i+j;
                PV3D* clon=puntos->at(j)->clone();
                PV3D* punto=clon->matrixProduct(Nt,Bt,Tt,Ct);
				vertex->at(numvertice)=punto;
                delete clon;  
            }

            //deletes de los objetos ya no necesarios
            delete sderivate;	delete fderivate;	delete Tt;
			delete Bt;			delete Nt;			delete Ct;

    } //fin del for para cada toma


    //construimos las caras

    for(int i=0;i<NQ;i++)
    {
            //construir las caras
            for(int j=0;j<NP;j++)
            {
                int numFace= NP*(i)+j ;
                faces->at(numFace)= new Cara(4);
                vector<VerticeNormal*>* arrayParcial= new vector<VerticeNormal*>(4);

                int baseVertex=numFace;
                int a= (baseVertex) % (NP*NQ);
                int b= (sucesor(baseVertex))% (NP*NQ);
                int c=  (sucesor(baseVertex)+NP)% (NP*NQ);
                int d=  (baseVertex+NP)% (NP*NQ);


                arrayParcial->at(0)=new VerticeNormal(a,numFace);
                arrayParcial->at(1)=new VerticeNormal(b,numFace);
                arrayParcial->at(2)=new VerticeNormal(c,numFace);
                arrayParcial->at(3)=new VerticeNormal(d,numFace);
                    

                faces->at(numFace)->setIndicesVN(arrayParcial); 
            }


    }

    //construir las primeras caras(desde toma 0 a toma NQ


    for(int i=0;i<this->numFaces;i++)
    {
            normals->at(i)= this->doVectorNormalNewell(faces->at(i));
    }



    delete poli;
	
}//fin funcion construye

int MontanaRusa::sucesor(int val)
{
        int valaux=val+1;
        if(valaux%NP==0)
        {
          return valaux-NP;
        }
        return valaux;
}

GLfloat MontanaRusa::degToRad(GLfloat deg)
{
    GLfloat num=deg*2*M_PI;
    GLfloat den=360;

    return num/den;
}


GLfloat MontanaRusa::calculaVueltas()
{
     /*
     GLfloat valor=(R-r)/r;
     GLfloat porcentajeVuelta=valor*360;
     while(porcentajeVuelta<0)
     {
      porcentajeVuelta=porcentajeVuelta+360;
     }

     while(porcentajeVuelta>360)
     {
     porcentajeVuelta=porcentajeVuelta-360;
     }

     GLfloat devolver=360.0/porcentajeVuelta;
     return ceil(devolver);
     */
     return (r*6)/mcd(R*6,r*6);

}

void MontanaRusa::dibuja(bool relleno,bool dibujaNormales)
{
       // Malla::draw(relleno,dibujaNormales);

        //dibujo  del coche
        
		PV3D* primeraderivada = fDerivate(acumCoche);
        PV3D* segundaderivada = sDerivate(acumCoche);

		PV3D* Tt = fDerivate(acumCoche); Tt->normalize();
        PV3D* Bt=primeraderivada->crossProduct(segundaderivada); Bt->normalize();
        PV3D* Nt=Bt->crossProduct(Tt);
        PV3D* Ct=function(acumCoche);

      
        GLfloat m[]={   Nt->getX(),Bt->getX(),Tt->getX(),Ct->getX(),
                        Nt->getY(),Bt->getY(),Tt->getY(),Ct->getY(),
                        Nt->getZ(),Bt->getZ(),Tt->getZ(),Ct->getZ(),
                        0,0,0,1};
      // */

       /*GLfloat m[] ={   Nt->getX(),Nt->getY(),Nt->getZ(),Nt->getPv(),
                        Bt->getX(),1,Bt->getZ(),Bt->getPv(),//el 1 es para que salga hacia arriba
                        Tt->getX(),Tt->getY(),Tt->getZ(),Tt->getPv(),
                        Ct->getX(),Ct->getY(),Ct->getZ(),Ct->getPv()};*/

        glMatrixMode(GL_MODELVIEW);        
        glPushMatrix();
               
                //glMultMatrixf(m);
                dibujaCoche();
              
        glPopMatrix();

        delete Tt;
        delete Bt;
        delete segundaderivada;
        delete primeraderivada;
        delete Nt;
        delete Ct;
		
}

void MontanaRusa::dibujaCoche()
{
      car->draw(acumCoche); 
}

void MontanaRusa::addAcum(GLfloat cantidad)
{
        acumCoche=acumCoche+cantidad;

}

int MontanaRusa::mcd(int x, int y)
{
      if(y==0)
        return x;
    else
        return mcd(y, x%y);

}
