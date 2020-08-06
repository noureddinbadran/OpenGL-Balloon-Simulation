#include <windows.h>		// Header File For Windows
#include <gl.h>
#include <glu.h>
#include <glut.h>			// Header File For The GLut32 Library
#include <fstream>
#include <GLAUX.h>
#include <math.h>
#include <heightMap.h>
#include <texture.h>
#include <camera.h>
#include <glutfont.h>
#include <sstream>
#include "Constants.h"
#include <iostream>
#include <string>
#include <cctype>
double y3=0;
double y2=0;
double y4=0;


using namespace std;

HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application
bool	keys[256];			// Array Used For The Keyboard Routine
bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen=TRUE; 	// Fullscreen Flag Set To Fullscreen Mode By Default

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
//******************************************
// ============= Members Definition =========

//==========================================
Camera _camera1,_camera2,_camera3,_camera4;
int top,down,Left,Right,back,front,loon,loon_bottom,Space_Box,Out,earth;
float speed=0.01f;  //”—⁄… Õ—ﬂ… «·ﬂ«„Ì—«
float y_target=0;
float x_target=0;
float z_target=0;
double earth_angle_x=0;
double earth_angle_y=0;
double earth_angle_z=0;

float y_loon=0; //«— ›«⁄ «·„‰ÿ«œ
float z_loon=0;
//float k=0; //ﬂ„Ì… «·ÂÌ·ÌÊ„
//float g=9.8f; // ”«—⁄ «·Ã«“»Ì… «·√—÷Ì…
float tt=0;//·ÕŸ… «·»œ¡
float a=0;// ”«—⁄ «·„‰ÿ«œ
float v=0;//”—⁄… «·„‰ÿ«œ
float rr=5;//‰’› ﬁÿ— ﬂ—… «·„‰ÿ«œ
float x_loon=200;
float yy=17; //«·«— ›«⁄ «·›«’· »Ì‰ —√” «·„‰ÿ«œ Ê ﬁ«⁄œ Â
bool play=false; //„ ÕÊ· »Ê·Ì«‰Ì ÌÕœœ »œ√  ‘€Ì· «·’Ê 
int index=0; //œ·Ì· „’›Ê›… «·«— ›«⁄
float temp=0;//ŒÿÊ… «·’⁄Êœ ··√⁄·Ï
bool movement=false;//„ ÕÊ· · ÕœÌœ Õ—ﬂ… «·ﬂ«„Ì—« ≈„« ⁄·Ï «· ÷«—Ì” √Ê „⁄ «·„‰ÿ«œ
bool seening=false;  //Â–« «·„ ÕÊ· · ÕœÌœ ≈„« «·œÊ—«‰ „⁄ «·„‰ÿ«œ √Ê „—«ﬁ» Â »œÊ‰ «·œÊ—«‰ „⁄Â
int port=0; //· ÕœÌœ ‰«›–… «·—ƒÌ«
int vision=1;//· ÕœÌœ ⁄œœ ‰Ê«›– «·—∆Ì«
bool in_Space=true;//· ÕœÌœ ›Ì„« ≈–« ﬂ‰  ›Ì «·›÷«¡ √Ê ·« „‰ √Ã· ≈–« ﬂ‰« ›Ì «·›÷«¡ Ê √—œ‰« «·⁄Êœ… ··√—÷ ‰⁄Êœ ·‰ﬁÿ… «·√’·
bool go_with_him=false;//·√Œ– ﬁ—«— «··Õ«ﬁ »«·„‰ÿ«œ √Ê ·« ›Ì Õ«· «·‰«›–… «·Ê«Õœ…
//“«ÊÌ… œÊ—«‰ «·„‰ÿ«œ ÕÊ· «·√—÷
float loon_angle=0;


//„ ÕÊ·«  Œ«’… »«·Õ—ﬂ… «·œ«∆—Ì… ··„‰ÿ«œ
double x_teta(0),y_teta(0);
double x_max=0,y_max=0;




GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,4.0f,100000.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}
GLUquadric *quadric ;

int terraintexture ;
GLubyte * HeightData ;
int TerrainSize = 512;
float step = 1/512.0;
float scaleY = 0.2f;
float scaleX = 1;
float scaleZ = 1;
GLfloat initTerrainPositionX;
GLfloat initTerrainPositionY;
GLfloat initTerrainPositionZ;


inline GLubyte GetValue( int i , int j  ) {return (int)(HeightData[i*TerrainSize + j]);}
char * convert_to_char(string add , float t,int & length) ;
void DrawMyText();
void SetupProjection(int width,int height);
long m_windowWidth=1366;
long m_windowHeight=768;


//classes

class cylindricalCoordinates
{
public:
	//Data Members
	double p;
	double oz;
	double angle;

	//Methods
	cylindricalCoordinates()
	{
		p=0;
		oz=0;
		angle=0;
	}

	cylindricalCoordinates(double x,double y,double z)
	{
		p=sqrt(pow(x,2)+pow(y,2));
		oz=z;
		angle=atan(y/x);
	}
};

class Vector3D
{
public:
	//Data Members
	double x;
	double y;
	double z;
	
	//Methods
	
	Vector3D()
	{
		x=0;
	    y=0;
	    z=0;
	}

	Vector3D(double x,double y,double z)
	{
		this->x=x;
		this->y=y;
		this->z=z;
	}
	void setVec(double x,double y,double z)
	{
		(*this).x=x;
		(*this).y=y;
		(*this).z=z;
	}
	cylindricalCoordinates transletCylindricalCoordinate()
	{
		
	}
	double stringth()
	{
		return(sqrt(pow(x,2)+pow(y,2)+pow(z,2)));
	}
	void transletCartezihCoordinate(cylindricalCoordinates v)
	{
		x=v.p*cos(v.angle);
        y=v.p*sin(v.angle);
	    z=v.oz;
	}
	void mult_vec_cons(double m)
	{
		x=x*m;
	    y=y*m;
	    z=z*m;
	}
	void sum_vec(Vector3D va,Vector3D vg,Vector3D vr)
	{
		x=va.x+vg.x+vr.x;
	    y=va.y+vg.y+vr.y;
	    z=va.z+vg.z+vr.z;
	}

	void a(Vector3D va,Vector3D vg,Vector3D vr)//va ﬁÊ… √—Œ„Ìœ”  //vg ﬁÊ… «·Ã«–»Ì… «·√—÷Ì…  //vr ﬁÊ… „ﬁ«Ê„… «·ÂÊ«¡
	{
		(*this).sum_vec(va,vg,vr);
		(*this).mult_vec_cons(1/massBallon);
	    //vt.x=(va.x+vg.x+vr.x)/totalMass;//ﬁÊ… √—Œ„Ìœ” +ﬁÊ… «·Ã«–»Ì… «·√—÷Ì…+ﬁÊ… „ﬁ«Ê„… «·ÂÊ«¡
	    //vt.y=(va.y+vg.y+vr.y)/totalMass;//ﬁÊ… √—Œ„Ìœ” +ﬁÊ… «·Ã«–»Ì… «·√—÷Ì…+ﬁÊ… „ﬁ«Ê„… «·ÂÊ«¡
	    //vt.z=(va.z+vg.z+vr.z)/totalMass;//ﬁÊ… √—Œ„Ìœ” +ﬁÊ… «·Ã«–»Ì… «·√—÷Ì…+ﬁÊ… „ﬁ«Ê„… «·ÂÊ«¡
	}	
	void v(Vector3D va,Vector3D vg,Vector3D vr,Vector3D last_speed,Vector3D wind)
	{
		last_speed.a(va,vg,vr);
		y4=last_speed.y;
		if  (fabs(last_speed.y)>0.1)
		{
			(*this).a(va,vg,vr); 
			(*this).mult_vec_cons(t);
			(*this).sum_vec((*this),last_speed,wind);
			last_speed.setVec(this->x,this->y,this->z);
			//y3=1;
		}
		//else
			//y3=0;
			/*{
			this->setVec(last_speed.x,last_speed.y,last_speed.z);
			y3=this->y;
		 }*/

	    //x=force.x*t+speedBalloon.x+wind.x;
	    //y=force.y*t+speedBalloon.y+wind.y;
	    //z=force.z*t+speedBalloon.z+wind.z;
	}
};

Vector3D wind;
Vector3D wind1[2];

class Forces
{
public:
	//Data Members
	Vector3D archimedes;
	Vector3D airResistance;
	Vector3D forceOfGravity;

	//Methods
	void update(double valumBallon,double densityBallon,Vector3D wind,double densityAir,Vector3D speed,Vector3D position)
	{
		archimedes.x=0;
	    archimedes.y=(valumBallon*densityBallon*g);
	    archimedes.z=0;

     	forceOfGravity.x=0;
		forceOfGravity.y=-1*(massBallon*g);
	    forceOfGravity.z=0;

		if (position.y>0)
		{
			airResistance.x=0.5*Cd[0]*densityAir*A*speed.x;	 
			/*if (speed.y<0)
			   airResistance.y=0.5*Cd[0]*densityAir*A*pow(speed.y,2);
			else
				if (speed.y>0)
					airResistance.y=-(0.5*Cd[0]*densityAir*A*pow(speed.y,2));*/
			airResistance.y=-0.1;
			airResistance.z=0.5*Cd[0]*densityAir*A*speed.z;
			
			y3=position.y;
			y2=speed.y;
		}
			
	}
};

class Atmosphere
{
public:

	//Methods
	double getTempreture(Vector3D speed) 
	{
		int h=speed.y;
		if(h<20000)
		  return ( (tempreture[h/1000]+tempreture[h/1000+1])/2 );
		else
			return tempreture[20];
	}
	
	double getPressureAir(Vector3D speed)
	{
		return p0*exp(-(g*molarMass*speed.y)/(R*t0)); 
	}

	 double getDensityAir(Vector3D speed)
	{
		//int h=speed.y;
		double t=(getPressureAir(speed)*molarMass)/(R*getTempreture(speed));
		return t;
	}

};

Vector3D speed1(0,0,0);
Vector3D speed2(0,0,0);

class Balloon:public Atmosphere
{
public:
	double pressureBallon;
	double densityHelium;
	double massHe;
	double valumeB;
	Vector3D position;
	Forces f;

	Balloon()
	{
		pressureBallon=0;
		densityHelium=0;
		valumeB=0;
		massHe=0;

		
		position.setVec(0,0,0);
	}


	void set()
	{
		pressureBallon=getPressureAir(position);
		valumeB= (((massHe*1000)/molarMassgaz)*R*getTempreture(position))/pressureBallon ;
		if (valumeB!=0)
		    densityHelium=massHe/valumeB;
		else
			if (valumeB==0)
				densityHelium=0;
		f.update( valumeB, densityHelium, wind, getDensityAir(position),speed1,position);
		speed1.v(f.archimedes,f.forceOfGravity,f.airResistance,speed2,wind);
		if((speed1.y+position.y)>0)
			position.setVec(speed1.x+position.x,speed1.y+position.y,speed1.z+position.z);
		else
			position.setVec(0,0,0);
		if (y3!=0)
			wind1[0]=position;

		//y3=speed1.y;



	}

	void getDensityHelium()
	{}

	void getpressureBallon()
	{}

	void getValume()
	{}

	void update()
	{
		if (keys[VK_UP])
			if (massHe<29.8)
			   {
				   massHe+=0.2;
				   massBallon-=0.2;
		       }
		if(keys[VK_DOWN])
		{
			if (massHe>0)
		      {
			    massHe-=0.2;
				massBallon+=0.2;
			}

			if(massHe<=0.2)
				massHe=0;
		}

		if (keys[VK_NUMPAD8])
		{
			if (massHe<25)
			   {
				   massHe+=5;
				   massBallon-=5;
		       }
		}

		

					 //if(our_loon.massHe<0.2)
		                 //our_loon.massHe=0;


		set();

	}
	
  void DrawLoon()
 {
   
	 glPushMatrix();
	     glRotated(loon_angle,1,0,0);	 
		 if(y_loon>0)
			 glTranslated(-5+x_loon+x_max*cos(x_teta)+5,y_loon+yy+y_max*sin(y_teta),-20+z_loon);
		 else
			 glTranslated(-5+x_loon,y_loon+yy,-20+z_loon);
	     glEnable(GL_TEXTURE_2D);
	     glBindTexture(GL_TEXTURE_2D,loon);
	   gluSphere(quadric , rr , 32 ,32);
	 glPopMatrix();


     glPushMatrix();
	     glBindTexture(GL_TEXTURE_2D,loon_bottom);
	     glRotated(loon_angle,1,0,0);
		 if(y_loon>0)
			 glTranslated(-5+x_loon+x_max*cos(x_teta),y_loon+10+y_max*sin(y_teta),-20+z_loon);
		 else
			 glTranslated(-5+x_loon,y_loon+10,-20+z_loon);
	   gluSphere(quadric , 2.5 , 32 ,32);
	 glPopMatrix();
   }


};

//€—÷ „‰ «·’› Balloon
Balloon our_loon;















bool ok=true;

double fa[11]={14.43766926,12.88225992,11.43757098,10.09815978,8.86239472,7.72196588,6.67404568,5.7117002,4.83074288,4.02562314,3.31132672};

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
   
	terraintexture = LoadTexture("Data\\images\\terrain texture.bmp"); 
	HeightData = new GLubyte(TerrainSize*TerrainSize);
    HeightData = LoadHeightMap("Data\\images\\terrain height.bmp");
    quadric = gluNewQuadric();
   
	
     _camera1 = Camera();
	  _camera1.RotateY(-71.25);
	_camera2 = Camera();
	  _camera2.RotateY(-71.25);
	_camera3 = Camera();
	_camera3.Position.y=(float)(GetValue(
		(int)((_camera3.Position.x + initTerrainPositionX) * scaleX),
		(int)((_camera3.Position.z + initTerrainPositionZ) * scaleZ)		
		))
		*scaleY
		+15;
	  _camera3.RotateY(-71.25);
	_camera4 = Camera();
	_camera4.Position.y = (float)(GetValue(
		(int)((_camera4.Position.x + initTerrainPositionX) * scaleX),
		(int)((_camera4.Position.z + initTerrainPositionZ) * scaleZ)		
		))
		*scaleY
		+15;
	  _camera4.RotateY(-71.25);
	

	//„—Õ·…  Õ„Ì· «·’Ê— ≈·Ï «·–«ﬂ—…
    back=LoadTexture("Data//Images//back.bmp");
    front=LoadTexture("Data//Images//front.bmp");
	Left=LoadTexture("Data//Images//left.bmp");
    Right=LoadTexture("Data//Images//right.bmp");
    top=LoadTexture("Data//Images//top.bmp");
    down=LoadTexture("Data//Images//down.bmp");	
	loon=LoadTexture("Data//Images//loon.bmp");
	loon_bottom=LoadTexture("Data//Images//loon_Bottom.bmp");
	Space_Box=LoadTexture("Data//Images//spacebox.bmp");
	earth=LoadTexture("Data//Images//earth.bmp",255);
    Out=LoadTexture("Data//Images//Out.bmp");
	PlaySound(TEXT("Data/Sound/1.wav"),NULL,SND_FILENAME | SND_ALIAS | SND_ASYNC);
    gluQuadricTexture(quadric, GL_TRUE);
	

 //  



	return TRUE;											// Initialization Went OK
}


void DrawSkyBox()
	{
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glScalef(512,512,512);
	glBindTexture(GL_TEXTURE_2D,front);
	glBegin(GL_QUADS);

	//front
	glTexCoord2f(1,0) ; 		glVertex3f(0.5,-0.5,0.5); 
	glTexCoord2f(1,1) ;			glVertex3f(0.5,0.5,0.5);
	glTexCoord2f(0,1) ;			glVertex3f(-0.5,0.5,0.5);
	glTexCoord2f(0,0) ;			glVertex3f(-0.5,-0.5,0.5);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,back);
	glBegin(GL_QUADS);
	//back
	glTexCoord2f(0,0) ;		glVertex3f(0.5,-0.5,-0.5);
	glTexCoord2f(0,1) ;		glVertex3f(0.5,0.5,-0.5);
	glTexCoord2f(1,1) ;		glVertex3f(-0.5,0.5,-0.5);
	glTexCoord2f(1,0) ;		glVertex3f(-0.5,-0.5,-0.5);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,Right);
	glBegin(GL_QUADS);
	//right
	glTexCoord2f(1,0) ;		glVertex3f(0.5,-0.5,-0.5);
	glTexCoord2f(1,1) ;		glVertex3f(0.5,0.5,-0.5);
	glTexCoord2f(0,1) ;		glVertex3f(0.5,0.5,0.5);
	glTexCoord2f(0,0) ;		glVertex3f(0.5,-0.5,0.5);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,Left);
	glBegin(GL_QUADS);
	//left
	glTexCoord2f(1,0) ;		glVertex3f(-0.5,-0.5,0.5);
	glTexCoord2f(1,1) ;		glVertex3f(-0.5,0.5,0.5);
	glTexCoord2f(0,1) ;		glVertex3f(-0.5,0.5,-0.5);
	glTexCoord2f(0,0) ;		glVertex3f(-0.5,-0.5,-0.5);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,top);
	glBegin(GL_QUADS);
	//up
	glTexCoord2f(1,0) ;		glVertex3f(0.5,0.5,0.5);
	glTexCoord2f(1,1) ;		glVertex3f(0.5,0.5,-0.5);
	glTexCoord2f(0,1) ;		glVertex3f(-0.5,0.5,-0.5);
	glTexCoord2f(0,0) ;		glVertex3f(-0.5,0.5,0.5);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,down);
	glBegin(GL_QUADS);
	//down
	glTexCoord2f(1,0) ;		glVertex3f(0.5,-0.5,-0.5);
	glTexCoord2f(1,1) ;		glVertex3f(0.5,-0.5,0.5);
	glTexCoord2f(0,1) ;		glVertex3f(-0.5,-0.5,0.5);
	glTexCoord2f(0,0) ;		glVertex3f(-0.5,-0.5,-0.5);

	glEnd();
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}
int yyy=0; //«— ›«⁄ «· ÷«—Ì”

void DrawTerrain()
{
	initTerrainPositionX = TerrainSize/2.0f;
	initTerrainPositionZ = TerrainSize/2.0f;
	initTerrainPositionY = yyy;

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,terraintexture);
	glScalef(scaleX,scaleY,scaleZ);
	glTranslatef(-initTerrainPositionX, initTerrainPositionY, -initTerrainPositionZ);
	
		for (int i = 3 ; i<TerrainSize-3 ; i++)
		{
			glBegin(GL_TRIANGLE_STRIP);
			for (int j = 3 ; j < TerrainSize -3; j++)
			{
				glTexCoord2f(j*step,i*step);
				glVertex3f(i, GetValue(i,j), j);

				glTexCoord2f((j+1)*step,i*step);
				glVertex3f(i, GetValue(i,j+1), j+1);

				glTexCoord2f(j*step,(i+1)*step);
				glVertex3f(i+1, GetValue(i+1,j), j);

				glTexCoord2f((j+1)*step,(i+1)*step);
				glVertex3f(i+1, GetValue(i+1,j+1), j+1);
			}
			glEnd();
		}
	

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}


void key()
{
if(port==1 || vision==1)
 {

	 //·Õ—ﬂ… «·ﬂ«„Ì—… «·√Ê·Ï ··Œ·›
	if (keys['S'])
        _camera1.MoveForward(-10.0*speed );

	// ·Õ—ﬂ… «·ﬂ«„Ì—… «·√Ê·Ï ··√„«„
	if (keys['W'])
		_camera1.MoveForward(10.0*speed ) ;

	//œÊ—«‰ «·ﬂ«„Ì—« ··Ì„Ì‰
	if (keys['D'])
		   _camera1.RotateY(-1*speed);

	//œÊ—«‰ «·ﬂ«„Ì—« ··Ì”«—
	if (keys['A'])
		_camera1.RotateY(speed);

	//·—›⁄ «·ﬂ«„Ì—« ⁄·Ï „ÕÊ— «·⁄Ì‰«  »À»«  „Êﬁ⁄Â«
	if(keys['8'])
		_camera1.View.y+=0.05f;
    // ·Œ›÷ «·ﬂ«„Ì—« ⁄·Ï „ÕÊ— «·⁄Ì‰«  »”»«  „Êﬁ⁄Â«
	if(keys['2'])
	 _camera1.View.y-=0.05f;

	//·“Ì«œ… «— ›«⁄ «·ﬂ«„Ì—« ⁄·Ï „ÕÊ— «·⁄Ì‰« 
	if(keys['3'])
		_camera1.Position.y+=100;

	//·Œ›÷ «— ›«⁄ «·ﬂ«„Ì—« ⁄·Ï „ÕÊ— «·⁄Ì‰« 
	if(keys['1'])
		_camera1.Position.y-=100;
 }

 if(port==2)
 {
	if (keys['S'])
        _camera2.MoveForward(-10.0*speed );

	if (keys['W'])
		_camera2.MoveForward(10.0*speed ) ;

	if (keys['D'])
 	    _camera2.RotateY(-1*speed);
 
	if (keys['A'])
		_camera2.RotateY(speed);

   	if(keys['8'])
		_camera2.View.y+=0.05f;

	if(keys['2'])
	   _camera2.View.y-=0.05f;

	if(keys['3'])
		_camera2.Position.y+=100;
	if(keys['1'])
		_camera2.Position.y-=100;
 }

 if(port==3)
 {
	if (keys['S'])
        _camera3.MoveForward(-10.0*speed );
	if (keys['W'])
		_camera3.MoveForward(10.0*speed ) ;
	
	if (keys['D'])
		   _camera3.RotateY(-1*speed);
	if (keys['A'])
		_camera3.RotateY(speed);

	if(keys['8'])
   	   _camera3.View.y+=0.05f;

	if(keys['2'])
	 _camera3.View.y-=0.05f;

	if(keys['3'])
		_camera3.Position.y+=100;
	if(keys['1'])
		_camera3.Position.y-=100;
 }

 if(port==4)
 {
	if (keys['S'])
        _camera4.MoveForward(-10.0*speed );

	if (keys['W'])
		_camera4.MoveForward(10.0*speed ) ;

	if (keys['D'])
		   _camera4.RotateY(-1*speed);

	if (keys['A'])
		_camera4.RotateY(speed);

	if(keys['8'])
		_camera4.View.y+=0.05f;
		
	if(keys['2'])
	 _camera4.View.y-=0.05f;

	if(keys['3'])
		_camera4.Position.y+=100;
	if(keys['1'])
		_camera4.Position.y-=100;
 }

     //· »œÌ· «· Õﬂ„ „‰ ‰«›–… ≈·Ï √Œ—Ï
    if(keys['H'] && port<4 && vision==4)
		port+=1;

	if(keys['G'] && port>1 && vision==4)
		port-=1;
	
     //·· »œÌ· »Ì‰ Ê÷⁄ «·—Ì« „‰ ‰«›–… ≈·Ï √—»⁄ ‰Ê«›–
	  if(keys['1'])
		  vision=1;

	  //·· »œÌ· »Ì‰ Ê÷⁄ «·—Ì« „‰ √—»⁄ ‰Ê«›– ≈·Ï ‰«›–… Ê«Õœ…
	  if(keys['4'])
		  vision=4;


	//·“Ì«œ… ”—⁄… «·ﬂ«„Ì—«
	if(keys['K'])
		speed+=0.5f;

     //·≈‰ﬁ«’ ”—⁄… «·ﬂ«„Ì—«
	if(keys['L'])
		speed-=0.5f;

	//·“Ì«œ… «·ÂÌ·ÌÊ„ »«·„‰ÿ«œ 
	if(keys[VK_UP])
	{
		PlaySound(TEXT("Data/Sound/2.wav"),NULL,SND_FILENAME | SND_ASYNC | SND_ALIAS);
		//k+=1;
		rr+=0.1;
		yy+=0.1;
       
	}

	//·≈‰ﬁ«’ «·ÂÌ·ÌÊ„ »«·„‰ÿ«œ
	if(keys[VK_DOWN])
	{
	//	no_dec=true;
     if(our_loon.massHe>0)
    PlaySound(TEXT("Data/Sound/2.wav"),NULL,SND_FILENAME | SND_ASYNC | SND_ALIAS);
/*		if(y_loon>2)
		{
			
			if(k>0)
			   k-=1;
			   
		    y_loon-=fabs(k-g);
	     }
		else
			k-=1;*/
		if(rr>5)
		   rr-=0.1;
		if(yy>17)
		    yy-=0.1;

	}
  
	if(keys['T'])
	{
		if(y_loon>2)
		  y_loon-=rr;
		tt=0;
		//k=0;
		if(rr>5)
		{
		rr--;
		yy--;
		}

	}
	if(keys['R'])
	{ index=0;
		x_loon=200;
		in_Space=!in_Space;
		y_loon=0;
		play=false;
		temp=0;
        //≈⁄«œ… ÷»ÿ «— ›«⁄ «· ÷«—Ì”
		yyy=0;
		loon_angle=0;
		_camera2.View.y=0;
	}
    if(y_loon>=14315  && !play)
	{
		PlaySound(TEXT("Data/Sound/2.wav"),NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
		play=true;
	}

    //·„—«ﬁ»… «·„‰ÿ«œ „‰ «— ›«⁄Â «··ÕŸÌ
     if(keys['P'])
		 go_with_him=!go_with_him;
	
	if(vision==1 && movement && go_with_him)
		 _camera1.Position.y=y_loon+ 10*speed;

	//·· »œÌ· »Ì‰ «·ﬂ«„Ì—« «· Ì ⁄·Ï «·√—÷ Ê «·ﬂ«„Ì—«€ «· Ì  —«ﬁ» «·„‰ÿ«œ
	if(vision==1 && keys['M'])
       movement=!movement;

	//·« Œ«– ﬁ—«— «·œÊ—«‰ „⁄ «·„‰ÿ«œ √Ê «·«ﬂ ›«¡ »„—«ﬁ» Â
	if(vision==1 && keys['Z'])
		seening=!seening;



 
}

//—”„ «·”„«¡
void DrawSkyBall()
{
    glPushMatrix();
	    glRotated(90,1,0,0);
	    glRotated(-80,0,1,0);
	    glRotated(-25,0,0,1);
	    glEnable(GL_TEXTURE_2D);
	    glBindTexture(GL_TEXTURE_2D,top);
	  gluSphere(quadric , 20000 , 32 ,32);
	glPopMatrix();
	 
}

void DrawSkyOutBall()
{
    glPushMatrix();
	    glRotated(64,1,0,0);
        glRotated(99,0,1,0);
	    glRotated(104,0,0,1);
	    glEnable(GL_TEXTURE_2D);
	    glBindTexture(GL_TEXTURE_2D,earth);
	  gluSphere(quadric , 10000 , 32 ,32);
    glPopMatrix();
	 
}

void DrawSpaceBall()
{
    glPushMatrix();
	    glRotated(-90,0,1,0);
	    glEnable(GL_TEXTURE_2D);
	    glBindTexture(GL_TEXTURE_2D,Space_Box);
	  gluSphere(quadric , 40000 , 32 ,32);
    glPopMatrix();
	 
}

//—”„ «·√—÷
void DrawEarthBall()
{
    glPushMatrix();
	    glTranslated(0,-4510,0);
	    glRotated(90,1,0,0);
	    glEnable(GL_TEXTURE_2D);
	    glBindTexture(GL_TEXTURE_2D,terraintexture);
      gluSphere(quadric , 4500 , 32 ,32);
	glPopMatrix();
 
}


void SetupProjection(int width, int height)
{
	if (height == 0)					// don't want a divide by zero
	{
		height = 1;					
	}

	glViewport(0, 0, width, height);		// reset the viewport to new dimensions
	glMatrixMode(GL_PROJECTION);			// set projection matrix current matrix
	glLoadIdentity();						// reset projection matrix

	// calculate aspect ratio of window
	gluPerspective(52.0f,(GLfloat)width/(GLfloat)height,4.0f,100000.0f);

	glMatrixMode(GL_MODELVIEW);				// set modelview matrix
	glLoadIdentity();						// reset modelview matrix

	m_windowWidth = width;
	m_windowHeight = height;
}


void DivisionScreen()
{
  glDisable(GL_DEPTH_TEST);
  glDisable(GL_TEXTURE_2D);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  gluOrtho2D(0.0, 2.0, 0.0, 2.0);
  glViewport(0, 0, m_windowWidth, m_windowHeight);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();
  glColor3f(1.0, 1.0, 0.5f);
  glBegin(GL_LINES);
    glVertex3i(2, 1,-1);
    glVertex3i(0, 1,-1);
    glVertex3i(1, 2,-1);
    glVertex3i(1, 0,-1);
  glEnd();
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
}

float statue=0;

//ÿÊ· ”·”·… «·„Õ«—› «·„—”·… ··ÿ»«⁄… ⁄·Ï «·‘«‘…
int length;
void DrawMyText()
{
  glColor3f(1,0,0);
  glPushMatrix( );

	  glTranslatef(-15.5,5.5,-20);
	  DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("1- Helium =",our_loon.massHe,length),length) ;

   	  glTranslatef(0,-1,0);
	  DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("2- X_loon = ", -5+x_loon+x_max*cos(x_teta),length),length) ;

	  glTranslatef(0,-1,0);
	  DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("3- Y_loon = " , y_loon,length),length) ;
  
	  glTranslatef(0,-1,0);
	  DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("4- Z_loon = " , z_loon,length),length) ;

      //glTranslatef(0,-1,0);
  	  //DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("5 Cameran_Speed  " , speed)) ;

	  glTranslatef(0,-1,0);
  	  DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("5- position y " , y3,length),length) ;

      //glTranslatef(0,-1,0);
	  //DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("6 y_Target = " , _camera3.View.y)) ;

	   glTranslatef(0,-1,0);
	  DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("6- speed " , y2,length),length) ;
   
      glTranslatef(0,-1,0);
	  DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("7- dinsity of air = " , our_loon.getDensityAir(our_loon.position),length),length);

	  glTranslatef(0,-1,0);
	  DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("8- density of ballon = " , our_loon.densityHelium,length),length);

      glTranslatef(0,-1,0);
	  DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("9- Valoum Ballon = " , our_loon.valumeB,length),length);


  glTranslatef(0,-1,0);
  DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("10- Fa = " ,our_loon.f.archimedes.y,length),length);

	  glTranslatef(0,-1,0);
	  DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("11- Fg = " , our_loon.f.forceOfGravity.y,length),length);


	   //glTranslatef(0,-1,0);
	   //DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("12 position = " , our_loon.position.y));

	  glTranslatef(0,-1,0);
	  DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("12- Fr =" , y4,length),length);

	  glTranslatef(0,-1,0);
	  DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("13- Wind_y =" , wind1[0].y,length),length);


 glPopMatrix();
 glColor3f(1,1,1);

}

void display();

int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{	
	// Clear The Screen And The Depth Buffer 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glLoadIdentity(); 
    
   
//«·ÿ»«⁄… »Ê«ÃÂ… «·ﬂÊ‰”Ê·
	display();

//Ê÷⁄ ‰«›–… Ê«Õœ…
  if(vision==1)
 {
	 glViewport(0, 0, m_windowWidth, m_windowHeight);

//loon teta
	 if(y_loon>0)
	 {
	 x_teta+=0.1;
	 y_teta+=0.1;
	 x_max+=1;
	 y_max+=0.01;
	 }

     //≈ŸÂ«— «·„ﬁÌ«”« 
	DrawMyText();
	// ‘€Ì· «·ﬂ«„Ì—«
    _camera1.Render();

	//—”„ «·”„«¡
	DrawSkyBall();

   //—”„ «·„‰ÿ«œ
our_loon.update();
	y_loon=(our_loon.position.y);
	our_loon.DrawLoon();


		key();
   
      if(movement)
	{
		in_Space=true;
		  yyy-=1;//·ﬂÌ  ‰“· «·√—÷ «·Õ«·Ì…
	}
	else
	{
		if(in_Space)
		{
		_camera1.Position.x=0;
		_camera1.Position.z=0;
		in_Space=false;
		}
		_camera1.Position.y = (float)(GetValue(
		(int)((_camera1.Position.x + initTerrainPositionX) * scaleX),
		(int)((_camera1.Position.z + initTerrainPositionZ) * scaleZ)		
		))
		*scaleY
		+15;
	   yyy=0;
	   in_Space=false;

	}
    if(y_loon>14315)
	{
		loon_angle+=1.f;;
		if(seening)
		{
		   _camera1.Position.y=14315*cos(loon_angle/20);
           _camera1.Position.z=14315*sin(loon_angle/20);
		   if(in_Space && !movement)
		   {
		      _camera1.View.x=0;
		      _camera1.View.y=0;
		      _camera1.View.z=0;
		      in_Space=false;
		   }

	    }

	}
    //—”„ «·√—÷
   DrawEarthBall();

   //—”„ «· ÷«—Ì”
	DrawTerrain();

 }
else if(vision==4)
 {

    // ﬁ”Ì„ «·‘«‘… ≈·Ï «—»⁄ √ﬁ”«„
    DivisionScreen();
   	
	 //≈ŸÂ«— «·„ﬁÌ«”« 
	DrawMyText();
    key();

//if(k>g)
 	//	{ 
            tt+=0.1f;	
			
           if(index<11)
		   {
			   if(temp<fa[index]*4)
			   {
				   temp+=0.5f;
 			       y_loon+=temp;
				   _camera3.Position.y=y_loon+10;
				   _camera4.Position.y=y_loon+10;
			   }
			   else
			   {
				   index++;
				   temp=0;   
			   }

		   }
		   else
			   statue=-1;//√Ì  Êﬁ› «·„‰ÿ«œ
	//	}


  

//_________________________________________________________

glPushMatrix();

	//«·‰«›–… «·√Ê·Ï
  glViewport(0, m_windowHeight / 2, m_windowWidth / 2, m_windowHeight / 2);



	// ‘€Ì· «·ﬂ«„Ì—«
    _camera1.Render();
	//—”„ «·›÷«¡
	DrawSpaceBall();
	//—”„ «·”„«¡
	DrawSkyBall();
	//—”„ «·ÿ»ﬁ… «·⁄·Ì« „‰ «·”„«¡
	DrawSkyOutBall();
   //—”„ «·„‰ÿ«œ
	our_loon.DrawLoon();

	_camera1.Position.y = (float)(GetValue(
		(int)((_camera1.Position.x + initTerrainPositionX) * scaleX),
		(int)((_camera1.Position.z + initTerrainPositionZ) * scaleZ)		
		))
		*scaleY
		+15;

    //—”„ «·√—÷
   DrawEarthBall();
   //—”„ «· ÷«—Ì”
	DrawTerrain();

 glPopMatrix();

//___________________________________________________

 glPushMatrix();
	 //«·‰«›–… «·À«‰Ì…
	 glViewport(m_windowWidth / 2, m_windowHeight / 2, m_windowWidth / 2, m_windowHeight / 2);

	// ‘€Ì· «·ﬂ«„Ì—« «·À«‰Ì…
    _camera2.Render();
	//—”„ «·›÷«¡
	DrawSpaceBall();
	//—”„ «·”„«¡
	DrawSkyBall();
	//—”„ «·ÿ»ﬁ… «·⁄·Ì« „‰ «·”„«¡
	DrawSkyOutBall();
   //—”„ «·„‰ÿ«œ
	our_loon.DrawLoon();
	         
		if(y_loon!=0 && _camera2.View.y<10)
			_camera2.View.y+=0.00005;
	
		_camera2.Position.y = (float)(GetValue(
		(int)((_camera2.Position.x + initTerrainPositionX) * scaleX),
		(int)((_camera2.Position.z + initTerrainPositionZ) * scaleZ)		
		))
		*scaleY
		+15;
		if(_camera2.View.y<10 && y_loon!=0)
			_camera2.View.y+=0.05;

    //—”„ «·√—÷
   DrawEarthBall();
   //—”„ «· ÷«—Ì”
	DrawTerrain();

 glPopMatrix();

//_______________________________________________

 glPushMatrix();
	//«·‰«›–… «·À«·À…
	  glViewport(0, 0, m_windowWidth / 2, m_windowHeight / 2);


	// ‘€Ì· «·ﬂ«„Ì—« «·À«·À…
    _camera3.Render();
	//—”„ «·›÷«¡
	DrawSpaceBall();
	//—”„ «·”„«¡
	DrawSkyBall();
	//—”„ «·ÿ»ﬁ… «·⁄·Ì« „‰ «·”„«¡
	DrawSkyOutBall();
   //—”„ «·„‰ÿ«œ
	our_loon.DrawLoon();

     if(in_Space)
	  {
		_camera3.Position.x=0;
		_camera3.Position.z=0;
			_camera3.Position.y = (float)(GetValue(
		(int)((_camera3.Position.x + initTerrainPositionX) * scaleX),
		(int)((_camera3.Position.z + initTerrainPositionZ) * scaleZ)		
		))
		*scaleY
		+15;
		}


    //—”„ «·√—÷
   DrawEarthBall();
   //—”„ «· ÷«—Ì”
	DrawTerrain();

 glPopMatrix();

//__________________________________________________

glPopMatrix();

	//«·‰«›–… «·—«»⁄…
     glViewport(m_windowWidth / 2, 0, m_windowWidth / 2, m_windowHeight / 2);
     
	// ‘€Ì· «·ﬂ«„Ì—« «·—«»⁄…
    _camera4.Render();
	//—”„ «·›÷«¡
	DrawSpaceBall();
	//—”„ «·”„«¡
	DrawSkyBall();
	//—”„ «·ÿ»ﬁ… «·⁄·Ì« „‰ «·”„«¡
	DrawSkyOutBall();
   //—”„ «·„‰ÿ«œ
	our_loon.DrawLoon();
   
      if(in_Space)
	  {
		_camera4.Position.x=0;
		_camera4.Position.z=0;
		_camera4.Position.y = (float)(GetValue(
		(int)((_camera4.Position.x + initTerrainPositionX) * scaleX),
		(int)((_camera4.Position.z + initTerrainPositionZ) * scaleZ)		
		))
		*scaleY
		+15;

		}

    if(y_loon>14315)
	{
		loon_angle+=1.f;;
		   _camera4.Position.y=14315*cos(loon_angle/20);
           _camera4.Position.z=14315*sin(loon_angle/20);
	}

    //—”„ «·√—÷
   DrawEarthBall();
   //—”„ «· ÷«—Ì”
	DrawTerrain();

  glPopMatrix();
}  //if(vision==4)

	return TRUE;										// Keep Going} 

} 

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/
 
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}
	
	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam){
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				active=TRUE;						// Program Is Active
			}
			else
			{
				active=FALSE;						// Program Is No Longer Active
			}

			return 0;								// Return To The Message Loop
		}

		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}

		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keys[wParam] = TRUE;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = FALSE;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

//int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
//					HINSTANCE	hPrevInstance,		// Previous Instance
//					LPSTR		lpCmdLine,			// Command Line Parameters
//					int			nCmdShow)			// Window Show State
//{
//-----Main
void display()
{
	if(y_loon!=0)
	{  system("cls");
       cout<<"y_loon="<<y_loon<<endl;
	   cout<<"Fa = " << our_loon.f.archimedes.y<<endl;
	   cout<<"Fg = " << our_loon.f.forceOfGravity.y<<endl;
	   cout<<"-------------"<<endl;
	}
}
bool cheack(string s)
{
	for(unsigned int i=0 ; i<s.length() ; i++)
		if(s[i]=='.')
		   return true;

	return false;
}
double int_Parse(char c)
{
		switch (c)
	{
	    case '0' : return 0;
		  break;
		case '1' : return 1;
		  break;
		case '2' : return 2;
		  break;
		case '3' : return 3;
	  	  break;
		case '4' : return 4;
		  break;
		case '5' : return 5;
		  break;
		case '6' : return 6;
		  break;
		case '7' : return 7;
		  break;
		case '8' : return 8;
		  break;
		case '9' : return 9;
		  break;
	default:
		  //
		break;
	}

}

double fraction_count(double f_length)
{
	int count=f_length;
	switch(count)
	{
	  case 1 : return 10.0;
	  	  break;
	  case 2 : return 100.0;
		  break;
	  case 3 : return 1000.0;
		  break;
	  case 4 : return 10000.0;
		  break;
	  case 5 : return 100000.0;
		  break;
	  case 6 : return 1000000.0;
		  break;
	  case 7 : return 10000000.0;
		  break;
	  default : return 0;
		  break;
	}
	return 0;
}

double int_Parse(string s)
{
int num(0);
if(!cheack(s))//√Ì «·—ﬁ„ ·Ì” ›ÌÂ ﬁ«’·… ⁄‘—Ì…
 {
	for(unsigned int i=0 ; i< s.length() ; i++)
	{
       num=num*10+int_Parse(s[i]);
	}
  return num;
 }
else
{
	double fraction(0);
	unsigned int index=0;
	for(index ; s[index]!='.' ; index++)
	{
		num=num*10+int_Parse(s[index]);
	}
	double fraction_length=s.length()-(++index);
	for(index ; index<s.length() ; index++)
	{
		fraction=fraction*10+int_Parse(s[index]);
	}
	fraction=fraction/fraction_count(fraction_length);

  //Ã„⁄ «·‰ ÌÃ…
	double resault=num+fraction;
	return resault;
}
return 0;

}



int main(int argc,char *argv[])
{	
cout<<int_Parse("1.25")<<endl;
	//«·ÿ»«⁄… ›Ì Ê«ÃÂ… «·ﬂÊ‰”Ê·
	  //system("cls");
       cout<<"y_loon="<<y_loon<<endl;
	   cout<<"Fa = " << our_loon.f.archimedes.y<<endl;
	   cout<<"Fg = " << our_loon.f.forceOfGravity.y<<endl;
	   cout<<"-------------"<<endl;

	   string args[12];
	   for(int i = 0; i < argc; i++)
	   {
          args[i]=argv[i];
	   }

	  /* our_loon.massHe=int_Parse(args[1]);
	   speed=int_Parse(args[2]);
       g=int_Parse(args[3]);
	   molarMassgaz=int_Parse(args[4]);
	   totalMass=int_Parse(args[5]);
	   massBallon=int_Parse(args[6]);
	   p0=int_Parse(args[7]);
	   t0=int_Parse(args[8]);
	   R=int_Parse(args[9]);
	   valumeBalloon=int_Parse(args[10]);
	   molarMass=int_Parse(args[11]);*/

	MSG		msg;									// Windows Message Structure
	BOOL	done=FALSE;								// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	//if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	//{
		fullscreen=FALSE;							// Windowed Mode
	//}

	// Create Our OpenGL Window
	if (!CreateGLWindow("Project Loon",1360,700,16,fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while(!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if (active)								// Program Active?
			{
				if (keys[VK_ESCAPE])				// Was ESC Pressed?
				{
					done=TRUE;						// ESC Signalled A Quit
				}
				else								// Not Time To Quit, Update Screen
				{
					DrawGLScene();					// Draw The Scene
					SwapBuffers(hDC);				// Swap Buffers (Double Buffering)
				}
			}
			if (keys[VK_F1])						// Is F1 Being Pressed?
			{
				keys[VK_F1]=FALSE;					// If So Make Key FALSE
				KillGLWindow();						// Kill Our Current Window
				fullscreen=!fullscreen;				// Toggle Fullscreen / Windowed Mode
				// Recreate Our OpenGL Window
				if (!CreateGLWindow("OpenGL Window",1360,700,16,fullscreen))
				{
					return 0;						// Quit If Window Was Not Created
				}

			}
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam)	;						// Exit The Program
}
char * convert_to_char(string add , float t  ,int & length)
{
	string s=add;
	stringstream out;
	out << t;
	s += out.str();

	length=s.length();
	char * c = new char [s.length()] ;

	for (int i = 0 ; i < s.length() ; i++)
		c[i]=s[i];
	return c;

}