#include <windows.h>		// Header File For Windows
#include <GL.h>			// Header File For The OpenGL32 Library
#include <glu.h>			// Header File For The GLu32 Library
#include <glut.h>// Header File For The GLut32 Library
#include <fstream>
#include <math.h>
#include "texture.h"
#include "camera.h"
#include "Model_3DS.h"
#include <sstream>
#include <iostream>
#include <stdarg.h>	
#include "heightMap.h"
#include "Constants.h"
#include "math3d.h"
#include "convert_2_double.h"
//#include "glutFont.h"



//include lib file


#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glut32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"GLAUX.LIB")

#pragma comment(lib,"glut.lib")
#pragma comment(lib,"winmm.LIB")



using namespace std;

HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen=TRUE; 	// Fullscreen Flag Set To Fullscreen Mode By Default
Camera MyCamera;
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc














Camera _camera1,_camera2,_camera3,_camera4;
int top,down,Left,Right,back,front,loon,loon_bottom,Space_Box,Out,earth;
float speed=1.f;  //سرعة حركة الكاميرا
float y_target=0;
float x_target=0;
float z_target=0;
double earth_angle_x=0;
double earth_angle_y=0;
double earth_angle_z=0;

float y_loon=0; //ارتفاع المنطاد
float z_loon=0;
float tt=0;//لحظة البدء
float a=0;//تسارع المنطاد
float v=0;//سرعة المنطاد
float rr=5;//نصف قطر كرة المنطاد
float x_loon=200;
float yy=10; //الارتفاع الفاصل بين رأس المنطاد و قاعدته
bool play=false; //متحول بولياني يحدد بدأ تشغيل الصوت
int index=0; //دليل مصفوفة الارتفاع
float temp=0;//خطوة الصعود للأعلى
bool movement=false;//متحول لتحديد حركة الكاميرا إما على التضاريس أو مع المنطاد
bool seening=false;  //هذا المتحول لتحديد إما الدوران مع المنطاد أو مراقبته بدون الدوران معه
int port=0; //لتحديد نافذة الرؤيا
int vision=1;//لتحديد عدد نوافذ الرئيا
bool in_Space=true;//لتحديد فيما إذا كنت في الفضاء أو لا من أجل إذا كنا في الفضاء و أردنا العودة للأرض نعود لنقطة الأصل
bool go_with_him=false;//لأخذ قرار اللحاق بالمنطاد أو لا في حال النافذة الواحدة
//زاوية دوران المنطاد حول الأرض
float loon_angle=0;
bool Horizontal_Movment=false;//هذا المتحول لحركة الكميرا مع المنطاد حركة افقية مع الإرتفاع بحيث تستشعر بمقاومة الهواء
//متحولات اختيار الكوكب
bool Earth=true;
bool Moon;
bool no_terren=false;//هذا المتحول لرسم التضاريس أو لعدم رسمها

//الكوكب المختار
string planet_selected;



double y3=0;
double y2=0;
double y4=0;



//متحولات خاصة بالحركة الدائرية للمنطاد
double angle_rotation(-0.22),z_teta(0);
double x_max=0,z_max=0;
double seed;

void NbCursorOptions(bool hide_cursor, bool center, int mouse_x = 0, int mouse_y = 0);
//متحولات التقاط حركة الماوس
int mouseX, mouseY;

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
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,4.0f,10000000.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}





GLUquadric *quadric ;

int terraintexture ;
int terraintexture_moon;
int terraintexture_Earth;
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
extern "C"  char * convert_to_char(string add , float t,int & length,string unity) ;
extern "C"  void DrawMyText();
void SetupProjection(int width,int height);
long m_windowWidth=1366;
long m_windowHeight=768;

















bool ok=true;

//double fa[11]={14.43766926,12.88225992,11.43757098,10.09815978,8.86239472,7.72196588,6.67404568,5.7117002,4.83074288,4.02562314,3.31132672};

//تابع التهيئة العام في الأوبن جل

//تحميل موديل المنطاد
Model_3DS *loon_body;
Model_3DS *loon_base;

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations


	//التهيئة الخاصة بالتضاريس
	terraintexture = LoadTexture("Data\\images\\texture.bmp"); 
	terraintexture_moon = LoadTexture("Data\\images\\moon.bmp");
	terraintexture_Earth = LoadTexture("Data\\images\\earth.bmp");
    HeightData = new GLubyte(TerrainSize*TerrainSize);
    HeightData = LoadHeightMap("Data\\images\\terrain height.bmp");



		//تهيئة مؤشر التيكستشر المساعد في الأشكال ثلاثية الأبعاد
    quadric = gluNewQuadric();
   
	
	//تهيئة الكاميرات الأربع
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
	A[0]=(1.0/10)*A[0];
	  _camera3.RotateY(-71.25);
	_camera4 = Camera();
	_camera4.Position.y = (float)(GetValue(
		(int)((_camera4.Position.x + initTerrainPositionX) * scaleX),
		(int)((_camera4.Position.z + initTerrainPositionZ) * scaleZ)		
		))
		*scaleY
		+15;
	  _camera4.RotateY(-71.25);
	

	//مرحلة تحميل الصور إلى الذاكرة
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
	//PlaySound(TEXT("Data/Sound/1.wav"),NULL,SND_FILENAME | SND_ALIAS | SND_ASYNC);
    gluQuadricTexture(quadric, GL_TRUE);

     
	//وضع بذرة في متحول الحركة الدائرية العشوائية
	srand(seed);




	loon_body = new Model_3DS();
	loon_body->Load("Data//Models3d//body.3ds");
	GLTexture loon_body_texture;
	loon_body_texture.LoadBMP("Data//Models3d//tank.bmp");
	loon_body->Materials[0].tex=loon_body_texture;	

	loon_base = new Model_3DS();
	loon_base->Load("Data//Models3d//Base.3ds");
	GLTexture loon_base_texture;
	loon_base_texture.LoadBMP("Data//Models3d//sdv.bmp");
	loon_base->Materials[0].tex=loon_base_texture;


	//صوت البداية
	  PlaySound(TEXT("Data/Sound/1.wav"),NULL,SND_FILENAME | SND_ASYNC | SND_ALIAS | SND_LOOP);

	return true;

}









//classes



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

	double stringth()
	{
		return(sqrt(pow(x,2)+pow(y,2)+pow(z,2)));
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

	void a(Vector3D va,Vector3D vg,Vector3D vr)//va قوة أرخميدس  //vg قوة الجاذبية الأرضية  //vr قوة مقاومة الهواء
	{
		(*this).sum_vec(va,vg,vr);
		(*this).mult_vec_cons(1/massBallon);
	}	
	void v(Vector3D va,Vector3D vg,Vector3D vr,Vector3D last_speed,Vector3D wind)
	{
		last_speed.a(va,vg,vr);
		y4=last_speed.y;
		
			(*this).a(va,vg,vr); 
			(*this).mult_vec_cons(t);
			(*this).sum_vec((*this),last_speed,wind);
			last_speed.setVec(this->x,this->y,this->z);
		
	}
};

Vector3D wind;
Vector3D wind1[2];

//تابع لحساب السطح الظاهري في كل عملية تحديث
double Calculate_Apearing_Surface();


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
		//حساب قوة آرخميدس
		archimedes.x=0;
	    archimedes.y=(valumBallon*densityBallon*g);
	    archimedes.z=0;

		//حساب قوة الجذب المؤثرة على المنطاد
     	forceOfGravity.x=0;
		forceOfGravity.y=-1*(massBallon*g);
	    forceOfGravity.z=0;


		//حساب مقاومة الهواء
		if (position.y>0)
		{
		//	airResistance.x=-1*0.5*Cd[0]*densityAir*Calculate_Apearing_Surface()*pow(speed.x,2);	 
		//	airResistance.y=-1*0.5*Cd[0]*densityAir*Calculate_Apearing_Surface()*pow(speed.y,2);
		//	airResistance.z=-1*0.5*Cd[0]*densityAir*Calculate_Apearing_Surface()*pow(speed.z,2);

			airResistance.x=-1*0.5*Cd[0]*densityAir*A[0]*pow(speed.x,2);	 
			airResistance.y=-1*0.5*Cd[0]*densityAir*A[0]*pow(speed.y,2);
			airResistance.z=-1*0.5*Cd[0]*densityAir*A[0]*pow(speed.z,2);



			
			//y3=position.y;
			

			y2=speed.y;
		}
	
	}
};

class Atmosphere
{
public:

	//Methods
	double getTempreture(Vector3D Local_Position) 
	{
		int h=Local_Position.y;
		if(h<20000)
		  return ( (tempreture[h/1000]+tempreture[h/1000+1])/2 );
		else
			return tempreture[20];
	}
	
	double getPressureAir(Vector3D Local_Position)
	{
		return p0*exp(-(g*molarMass*Local_Position.y)/(R*t0)); 
	}

	 double getDensityAir(Vector3D Local_Position)
	{
		double t=(getPressureAir(Local_Position)*molarMass)/(R*getTempreture(Local_Position));
		return t;
	}
 
};

Vector3D speed1(0,0,0);
Vector3D speed2(0,0,0);





class coor_spherical
{
public:
	double tetax;
	double tetaz;
	double r;
	coor_spherical()
	{
		tetax=0; tetaz=0; r=0;
	}
	coor_spherical(double ttetax,double ttetaz,double tr)
	{
		tetax = ttetax;
		tetaz = ttetaz;
		r = tr;

	}

	void convertcartaz2sphircal(double x,double y,double z )
	{
		r = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
		tetaz = acos(z/r);
		tetax = atan(y/x);
	}
	Vector3D convert2cartazi()
	{
		Vector3D temp;
		temp.x = r*sin(tetaz)*cos(tetax);
		temp.y = r*sin(tetaz)*sin(tetax);
		temp.z = r*cos(tetaz);
		return temp;

	}


};




float x_loon_print,y_loon_print,z_loon_print;//متحولات البالون الجاهزة للطباعة

double random_teta;//زاوية الحركة الدائرية العشوائية في طبقة التروبوسفير
double random_radius;//نصف قطر دائرة الحركة الدائرية العشوائي في طبقة التروبوسفير


double height_loon;
bool finish=true;


class Balloon:public Atmosphere
{
public:
	double pressureBallon;
	double densityHelium;
	double massHe;
	double volumeB;
	Vector3D position;
	Forces f;

	Balloon()
	{
		pressureBallon=0;
		densityHelium=0;
		volumeB=0;
		massHe=0;

		
		position.setVec(0,0,0);
	}


	void set()
	{
		//الحصول على الضغط الجوي عند ارتفاع معين للمنطاد
		pressureBallon=getPressureAir(position);

		//حساب حجم المنطاد
		volumeB= (((massHe*1000)/molarMassgaz)*R*getTempreture(position))/pressureBallon ;

		//حساب كثافة الهيليوم داخل المنطاد
		if (volumeB!=0)
		    densityHelium=massHe/volumeB;
		else
			if (volumeB==0)
				densityHelium=0;

		//تحديث معلومات القوى
		f.update( volumeB, densityHelium, wind, getDensityAir(position),speed1,position);

		//حساب سرعة المنطاد للمنطاد
		speed1.v(f.archimedes,f.forceOfGravity,f.airResistance,speed2,wind);


		//حساب الموضع الجديد للمنطاد
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
		           PlaySound(TEXT("Data/Sound/2.wav"),NULL,SND_FILENAME | SND_ASYNC | SND_ALIAS);
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
		
		//استدعاء الإجرائية المسؤولة عن القوى و الحركة بشكل عام
	
		set();
	}




void DrawLoon()
{    
	random_teta=(double)(rand()%60);
	random_radius=(double)(rand()%2);

	 glPushMatrix();
	     //glRotated(loon_angle,1,0,0);	 
		 if(y_loon>100){
			 coor_spherical tempp;

			 
			 if(y_loon<16000)
			 {
				 //الحركة الدائرية العشوائية في طبقة التروبوسفير

				  //إسناد القيم من أجل الطباعة
				 x_loon_print=-5+x_loon+random_radius*cos(random_teta);
				 y_loon_print=y_loon;
				 z_loon_print=-20+z_loon +random_radius*sin(random_teta);
				 //tempp.convertcartaz2sphircal(-5+x_loon+random_radius*cos(random_teta),y_loon+yy,-20+z_loon +random_radius*sin(random_teta));
				  glTranslated(-5+x_loon+random_radius*cos(random_teta),y_loon+yy,-20+z_loon +random_radius*sin(random_teta));
                //      tempp.convertcartaz2sphircal(-5+x_loon,y_loon+yy,-20+z_loon);

		     }
			 else
			 {
				 //الحركة الدائرية المستقرة في طبقة الستراتوسفير

				 //إسناد القيم من أجل الطباعة
				 x_loon_print=-5+x_loon+(y_loon*cos(angle_rotation));
				 y_loon_print=y_loon;
				 z_loon_print=-20+z_loon+(y_loon*sin(angle_rotation));
				 //glRotated(angle_rotation,0,0,1);
				 
			/*	 if(finish)
				 {
				     height_loon=y_loon;
				     finish=false;
				 }
				 if(x_max<height_loon)
					 glTranslated(-5+x_loon+x_max,yy+y_loon,-20+z_loon);
				 else*/

					 glTranslated(-5+x_loon+(y_loon*cos(angle_rotation)),yy+y_loon,-20+z_loon+(y_loon*sin(angle_rotation)));
				 //tempp.convertcartaz2sphircal(-5+x_loon+(y_loon*cos(angle_rotation)),yy+y_loon,-20+z_loon+(y_loon*sin(angle_rotation)));
				 
			    //tempp.convertcartaz2sphircal(-5+x_loon+x_max*cos(angle_rotation),y_loon+yy,-20+z_loon +z_max*sin(z_teta));			    
		     }
			
			 Vector3D vector3d;
			 vector3d = tempp.convert2cartazi();
			/* fstream file ;*/
			 /*file.open("yaser.txt",ios::app);
			 file<<tempp.r<<"   "<<tempp.tetax<<"   "<<tempp.tetaz<<endl;;*/
			/* file.close();*/
			 //glTranslated(vector3d.x,vector3d.y,vector3d.z);
			// glTranslated(-5+x_loon+x_max*cos(angle_rotation),y_loon+yy,-20+z_loon +z_max*sin(z_teta));
			// delete vector3d;

            


		 }else{
			 coor_spherical tempp;
              
			 //إسناد القيم للطباعة
			 x_loon_print=-5+x_loon;
		     y_loon_print=y_loon;
			 z_loon_print=-20+z_loon;

			 tempp.convertcartaz2sphircal(-5+x_loon,y_loon+yy,-20+z_loon);
			 Vector3D vector3d;
			 vector3d = tempp.convert2cartazi();

			 glTranslated(vector3d.x,vector3d.y,vector3d.z);

			
		 }
	     //glEnable(GL_TEXTURE_2D);
		 //glBindTexture(GL_TEXTURE_2D,loon);

		 //من أجل زيادة حجم المنطاد مع الإرتفاع
		 if(((int)y_loon)%100 == 0 && massHe>25  && Earth)//المتحول المنطقي معناه أن انطلاق المنطاد من الأرض
		 {
			 rr+=0.1;
			 yy+=0.1;
		 }

 	       //gluSphere(quadric , rr , 32 ,32);
		glPushMatrix();
		    loon_body->scale=rr+5;
			//loon_body->pos.y=0;
			loon_body->pos.x=6;
			loon_body->pos.z=2.0;
		    loon_body->Draw();

		//رسم القاعدة
		glPushMatrix();
		glTranslated(0,-10,-0.5);
		loon_base->scale=5;
		loon_base->Draw();
		glPopMatrix();


		glPopMatrix();

	 glPopMatrix();


  //   glPushMatrix();
	 //    glBindTexture(GL_TEXTURE_2D,loon_bottom);
	 //   // glRotated(loon_angle,1,0,0);
		// if(y_loon>100){
		//	 coor_spherical tempp;

  //      	
		//	// tempp.convertcartaz2sphircal(-5+x_loon+x_max*cos(angle_rotation),y_loon+10,-20+z_loon+z_max*sin(z_teta));
		//	

		//	  //tempp.convertcartaz2sphircal(-5+x_loon+lengthteta*cos(teta),y_loon+10,-20+z_loon +lengthteta*sin(teta));

		//	 if(y_loon<16000)
		//	 {
		//		 //الحركة الدائرية العشوائية في طبقة التروبوسفير

		//		 

		//		 //tempp.convertcartaz2sphircal(-5+x_loon+random_radius*cos(random_teta),y_loon+10,-20+z_loon +random_radius*sin(random_teta));
		//		 glTranslated(-5+x_loon+random_radius*cos(random_teta),y_loon+10,-20+z_loon +random_radius*sin(random_teta));
		//		 // tempp.convertcartaz2sphircal(-5+x_loon,y_loon+10,-20+z_loon);
		//     }
		//	 else
		//	 {
		//		 //الحركة الدائرية المستقرة في طبقة الستراتوسفير
		//	     
		//		// tempp.convertcartaz2sphircal(-5+x_loon+(y_loon*cos(angle_rotation)),10+y_loon,-20+z_loon+(y_loon*sin(angle_rotation)));			    


		//		 
		//		 /*if(x_max<height_loon)
		//			 glTranslated(-5+x_loon+x_max,10+y_loon,-20+z_loon);
		//		 else*/

		//		 glTranslated(-5+x_loon+(y_loon*cos(angle_rotation)),10+y_loon,-20+z_loon+(y_loon*sin(angle_rotation)));
		//		 //tempp.convertcartaz2sphircal(-5+x_loon+x_max*cos(angle_rotation),y_loon+10,-20+z_loon +z_max*sin(z_teta));
		//     }



		//	 Vector3D vector3d;
		//	 vector3d = tempp.convert2cartazi();
		//	 //glTranslated(vector3d.x,vector3d.y,vector3d.z);


		//	 //glTranslated(-5+x_loon+x_max*cos(angle_rotation),y_loon+10,-20+z_loon+z_max*sin(z_teta));
		// }else
		//	 
		// {
		//	  coor_spherical tempp;

		//	 tempp.convertcartaz2sphircal(-5+x_loon,y_loon+10,-20+z_loon);
		//	 Vector3D vector3d;
		//	 vector3d = tempp.convert2cartazi();

		//	 glTranslated(vector3d.x,vector3d.y,vector3d.z);

		// }
	 //  //gluSphere(quadric , 2.5 , 32 ,32);
	 //glPopMatrix();

	
}



	
 /* void DrawLoon()
 {
   
	 glPushMatrix();
	     glRotated(loon_angle,1,0,0);	 
		 if(y_loon>0)
			 glTranslated(-5+x_loon+x_max*cos(angle_rotation)+5,y_loon+yy+y_max*sin(y_teta),-20+z_loon);
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
			 glTranslated(-5+x_loon+x_max*cos(angle_rotation),y_loon+10+y_max*sin(y_teta),-20+z_loon);
		 else
			 glTranslated(-5+x_loon,y_loon+10,-20+z_loon);
	   gluSphere(quadric , 2.5 , 32 ,32);
	 glPopMatrix();
   }*/


};

//غرض من الصف Balloon
Balloon our_loon;



double aa;
double Calculate_Apearing_Surface()
{
	//حساب نصف القطر
	double r=sqrt((3*our_loon.volumeB)/8);
	//حساب المساحة الظاهرية
	//double a=6*r*pi;
	double a=pi*pow(r,2);
	aa=a;
	return a;

}









int yyy=0; //ارتفاع التضاريس

void DrawTerrain()
{
	initTerrainPositionX = TerrainSize/2.0f;
	initTerrainPositionZ = TerrainSize/2.0f;
	initTerrainPositionY = yyy;

	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	if(Earth)
	   glBindTexture(GL_TEXTURE_2D,terraintexture);
	if(Moon)
		glBindTexture(GL_TEXTURE_2D,terraintexture_moon);

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

//المتحول الخاص بتفعيل صوت الرياح
bool Wind_sound=true;

double x_earth(103),y_earth(46),z_earth(-103);

//تابع الأزرار المتعلق بالكيبورت
void key()
{
if(port==1 || vision==1)
 {

	 //لحركة الكاميرة الأولى للخلف
	if (keys['S'])
        _camera1.MoveForward(-1*speed );

	// لحركة الكاميرة الأولى للأمام
	if (keys['W'])
		_camera1.MoveForward(speed ) ;

	//دوران الكاميرا لليمين
	if (keys['D'])
		   _camera1.RotateY(-0.5*speed);

	//دوران الكاميرا لليسار
	if (keys['A'])
		_camera1.RotateY(0.5*speed);

	//لرفع الكاميرا على محور العينات بثبات موقعها
	if(keys['8'])
		_camera1.View.y+=0.05f;
    // لخفض الكاميرا على محور العينات بسبات موقعها
	if(keys['2'])
	 _camera1.View.y-=0.05f;

	//لزيادة ارتفاع الكاميرا على محور العينات
	if(keys['3'])
		_camera1.Position.y+=100;

	//لخفض ارتفاع الكاميرا على محور العينات
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

     //لتبديل التحكم من نافذة إلى أخرى
    if(keys['H'] && port<4 && vision==4)
		port+=1;

	if(keys['G'] && port>1 && vision==4)
		port-=1;
	
     //للتبديل بين وضع الريا من نافذة إلى أربع نوافذ
	  if(keys['1'])
		  vision=1;

	  //للتبديل بين وضع الريا من أربع نوافذ إلى نافذة واحدة
	  if(keys['4'])
		  vision=4;


	//لزيادة سرعة الكاميرا
	if(keys['K'])
		speed+=0.5f;

     //لإنقاص سرعة الكاميرا
	if(keys['L'])
		speed-=0.5f;

	//لزيادة الهيليوم بالمنطاد 
	if(keys[VK_UP] && our_loon.massHe<=29.8)
	{
		//PlaySound(TEXT("Data/Sound/2.wav"),NULL,SND_FILENAME | SND_ASYNC | SND_ALIAS);
		//k+=1;
		//هذه المتحولات خاصة بحجم المنطاد و ارتفاعه عن قاعدته
		rr+=0.1;
		//yy+=0.1;

		//إعادة تشغيل صوت الرياح
    if(y_loon<16000)
       Wind_sound=true;
	}

	//لإنقاص الهيليوم بالمنطاد
	if(keys[VK_DOWN])
	{
     if(our_loon.massHe>0)
	 {
        PlaySound(TEXT("Data/Sound/2.wav"),NULL,SND_FILENAME | SND_ASYNC | SND_ALIAS);

		if(rr>5)
		   rr-=0.1;
		if(yy>17)
		    yy-=0.1;
	   }

	 //إعادة تشغيل صوت الرياح
	 if(y_loon<16000)
       Wind_sound=true;
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
	{ 
		//إعادة ضبط باراميترات المنطاد
		our_loon.massHe=0;
		massBallon=50;
		our_loon.volumeB=0;
		our_loon.f.airResistance.y=0;
		our_loon.f.archimedes.y=0;
        y_loon=0;


        //إعادة ضبط شكل المنطاد
        rr=5;
		yy=10;

		     //إيقاف صوت الرياح
			 Wind_sound=false;
			 PlaySound(TEXT("Data/Sound/not.wav"),NULL,SND_FILENAME | SND_ASYNC | SND_ALIAS);

		
		
		index=0;
		x_loon=200;
		in_Space=!in_Space;
		
		play=false;
		temp=0;
        //إعادة ضبط ارتفاع التضاريس
		yyy=0;
		loon_angle=0;
		_camera2.View.y=0;
	}
    /*if(y_loon>=14315  && !play)
	{
		PlaySound(TEXT("Data/Sound/2.wav"),NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);
		play=true;
	}*/

    //لمراقبة المنطاد من ارتفاعه اللحظي
     if(keys['P'])
		 go_with_him=!go_with_him;
	//هذا الشرط لإرتفاع الكاميرا مع المنطاد و تحديد المسافة بينهما حسب سرعة حركة الكاميرا
	 if(vision==1 && movement && go_with_him)
		 _camera1.Position.y=y_loon+ 10*speed;

	//للتبديل بين الكاميرا التي على الأرض و الكاميراغ التي تراقب المنطاد
	if(vision==1 && keys['M'])
       movement=!movement;

	//لتغيير قيمة متحول الحركة الأفقية للكاميرا بتأثير المقاومة
    if(keys['Q'] && go_with_him)
         Horizontal_Movment=!Horizontal_Movment;



	//لاتخاذ قرار الدوران مع المنطاد أو الاكتفاء بمراقبته
	if(vision==1 && keys['Z'])
		seening=!seening;


   //لوضع حالة التوازن و تساوي القوى
	if(keys['B'])
	{
		our_loon.massHe=25;
		massBallon=25;
		//نصف قطر كرة البالون
		rr=17.5;
		//المسافة بين الكرتين
		yy=10;
		   
	}


	//لإلغاء أو تفعيل رسم التضاريس
  if(keys['N'])
	  no_terren=!no_terren;


	/*if(keys[VK_NUMPAD0])
		x_earth++;
	if(keys[VK_NUMPAD1])
		x_earth--;

	if(keys[VK_NUMPAD2])
		y_earth++;
	if(keys[VK_NUMPAD3])
		y_earth--;

	if(keys[VK_NUMPAD4])
		z_earth++;
	if(keys[VK_NUMPAD6])
		z_earth--;*/


  	/*if(keys[VK_NUMPAD1])
		angle_rotation+=0.0001;
	if(keys[VK_NUMPAD0])
		angle_rotation-=0.0001;*/


}

//رسم السماء
void DrawSkyBall()
{
    glPushMatrix();
	    glRotated(-1,1,0,0);
	    glRotated(0,0,1,0);
	    glRotated(93,0,0,1);
	    glEnable(GL_TEXTURE_2D);
	    glBindTexture(GL_TEXTURE_2D,top);
	  gluSphere(quadric , 50000 , 32 ,32);
	glPopMatrix();
	 
}


//رسم الأرض
void DrawEarthBall()
{
    glPushMatrix();
	    glTranslated(0,-6388,0);
	    //glRotated(90,1,0,0);
		glRotated(x_earth,1,0,0);
		glRotated(y_earth,0,1,0);
		glRotated(z_earth,0,0,1);
	    glEnable(GL_TEXTURE_2D);
		if(Earth && y_loon<400)
	        glBindTexture(GL_TEXTURE_2D,terraintexture);
		if(Earth && y_loon>400)
			glBindTexture(GL_TEXTURE_2D,terraintexture_Earth);
		if(Moon)
			glBindTexture(GL_TEXTURE_2D,terraintexture_moon);
      gluSphere(quadric , 6378 , 32 ,32);
	glPopMatrix();
 
}


//تابع لتقسيم الشاشة إلى 4 أقسام
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




void DisplayString(int x, int y, void* font, const char* str,int & length_string) {
  const char* c;

  // Position the cursor for font drawing
  glRasterPos2i(x, y);

  // Draw the font letter-by-letter
  for (c=str; length_string-->0; c++)
    glutBitmapCharacter(font, *c);
}



float statue=0;


int length;//طول سلسلة المحارف المرسلة للطباعة على الشاشة

 int just_for_print=0;//متحول فقط لإزالة و إظهار رسالة عدم الطيران في حال كان الكوكب المختار هو القمر
void DrawMyText()
{
  glColor3f(1,0,0);
  glPushMatrix( );

  glTranslatef(-15.5,6,-20);
   DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("Helium =",our_loon.massHe,length,"Kg"),length) ;

   	  glTranslatef(0,-1,0);
	  DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("X_loon = ", x_loon_print,length,"m"),length) ;

	  glTranslatef(0,-1,0);
	  DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("Y_loon = " , y_loon_print,length,"m"),length) ;
  
	  glTranslatef(0,-1,0);
	  DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("Z_loon = " , z_loon_print,length,"m"),length) ;

	  glTranslatef(0,-1,0);
	  DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("Speed = " , y2,length,"m/s"),length) ;
   
      glTranslatef(0,-1,0);
	  DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("Dinsity of air = " , our_loon.getDensityAir(our_loon.position),length,"Kg/m^3"),length);

	  glTranslatef(0,-1,0);
	  DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("Density of ballon = " , our_loon.densityHelium,length,"kg/m^3"),length);

      glTranslatef(0,-1,0);
	  DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("Volume Ballon = " , our_loon.volumeB,length,"m^3"),length);

      glTranslatef(0,-1,0);
      DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("Fa = " ,our_loon.f.archimedes.y,length,"N"),length);


	  glTranslatef(0,-1,0);
	  DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("Fg = " , our_loon.f.forceOfGravity.y,length,"N"),length);

      glTranslatef(0,-1,0);
  	  DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("Fr = " , our_loon.f.airResistance.y,length,"N"),length);



	  
   //   glTranslatef(0,-1,0);
	  //DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("x = " ,x_earth,length,"N"),length);


	  //glTranslatef(0,-1,0);
	  //DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("y = " , y_earth,length,"N"),length);

   //   glTranslatef(0,-1,0);
	  //DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("z = " , z_earth,length,"N"),length);


   if(vision==1)
   {
	  glTranslatef(0,-1,0);
	  DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("Camera Speed= " , speed,length,"..."),length);
   }
   else
	   if(vision==4)
	   {
		   glTranslatef(0,-1,0);
		   DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("Port View= " , port,length,"..."),length);
	   }



     glTranslatef(0,-1,0);
	 DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("Camera x = " , _camera1.Position.x,length,"..."),length);


	  glTranslatef(0,-1,0);
	  DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("Camera z = " , _camera1.Position.z,length,"..."),length);



	    //من أجل طباعة عبارة حسب الكوكب
	  if(Moon)	    
	  {
	    just_for_print++;
		 if(just_for_print % 2)
		 {
			glColor3f(0,0,0);
			glTranslatef(0,-1,0);
		//	DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("Planet selected hasn't atmosphere \, couldn't flying " ,-1000000,length,"?"),length);
		 }
	  }

	  if(Earth)
	  {
		  glColor3f(0,0,0);
			glTranslatef(0,-1,0);
			DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char(" Please don\'t blow all Helium due to take place explosion of loon  " ,-1000000,length,"?"),length);
	  }
	 

	  	  //glTranslatef(0,-1,0);
		  //DisplayString(0,0,GLUT_BITMAP_HELVETICA_18,convert_to_char("angle_rotation = " , angle_rotation,length,"N"),length);



   glPopMatrix();
   glColor3f(1,1,1);


}








void display();






int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();// Reset The Current Modelview Matrix
    






	//الطباعة بواجهة الكونسول
	display();

//وضع نافذة واحدة
  if(vision==1)
 {
	 glViewport(0, 0, m_windowWidth, m_windowHeight);

     //إظهار المقياسات
	DrawMyText();
	//تشغيل الكاميرا
    _camera1.Render();

	//رسم السماء
	DrawSkyBall();

   //رسم المنطاد
    our_loon.update();
	y_loon=(our_loon.position.y);
	our_loon.DrawLoon();
     


//loon teta
   if(y_loon>16000)
	{
	 angle_rotation+=0.0000559238;
	 //x_max+=0.01;
	 y_earth+=0.00001;
	 }
 

   if(y_loon>0 && y_loon<16000)
	 {
		 if(Wind_sound)
		 {
		    PlaySound(TEXT("Data/Sound/5.wav"),NULL,SND_FILENAME | SND_ASYNC | SND_ALIAS | SND_LOOP);
		    Wind_sound=false;
		 }
     }

     if(y_loon>=16000)
	{
    	 Wind_sound=false;
		 PlaySound(TEXT("Data/Sound/not.wav"),NULL,SND_FILENAME | SND_ASYNC | SND_ALIAS);
	}

	 if(y_loon<=16000)
	 {
		  //حركة الكاميرة
			 if(Horizontal_Movment && go_with_him)
			 {
				 _camera1.Position.x=-5+x_loon+random_radius*cos(random_teta);
				 _camera1.Position.z=-20+z_loon +random_radius*sin(random_teta);
			 }
	 }

	 if(y_loon>16000)
	 {
		 	 //حركة الكاميرة
			   if(Horizontal_Movment && go_with_him)
			    {
					_camera1.Position.x=-5+x_loon+(y_loon*cos(angle_rotation));
					_camera1.Position.z=10+z_loon+(y_loon*sin(angle_rotation));
			    }
	 }


		key();
   
      if(movement)
	{
		in_Space=true;
		  yyy-=1;//لكي تنزل الأرض الحالية
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
    
    //رسم الأرض
   DrawEarthBall();

   //رسم التضاريس
   if(!no_terren)
	DrawTerrain();

 }
else if(vision==4)
 {

    //تقسيم الشاشة إلى اربع أقسام
    DivisionScreen();

    //تحديث بيانات المنطاد
	our_loon.update();
	y_loon=(our_loon.position.y);
   	
	 //إظهار المقياسات
	DrawMyText();

	//استدعاء تابع الأزرار
    key();
 
 

//_________________________________________________________

glPushMatrix();

	//النافذة الأولى
  glViewport(0, m_windowHeight / 2, m_windowWidth / 2, m_windowHeight / 2);



	//تشغيل الكاميرا
    _camera1.Render();

	//رسم السماء
	DrawSkyBall();

   //رسم المنطاد
	our_loon.DrawLoon();

	_camera1.Position.y = (float)(GetValue(
		(int)((_camera1.Position.x + initTerrainPositionX) * scaleX),
		(int)((_camera1.Position.z + initTerrainPositionZ) * scaleZ)		
		))
		*scaleY
		+15;

    //رسم الأرض
   DrawEarthBall();
   //رسم التضاريس
	DrawTerrain();

 glPopMatrix();

//___________________________________________________

 glPushMatrix();
	 //النافذة الثانية
	 glViewport(m_windowWidth / 2, m_windowHeight / 2, m_windowWidth / 2, m_windowHeight / 2);

	//تشغيل الكاميرا الثانية
    _camera2.Render();

	//رسم السماء
	DrawSkyBall();

   //رسم المنطاد
	our_loon.DrawLoon();
	         
		if(y_loon!=0 && _camera2.View.y<10)
			_camera2.View.y+=0.00005f;
	
		_camera2.Position.y = (float)(GetValue(
		(int)((_camera2.Position.x + initTerrainPositionX) * scaleX),
		(int)((_camera2.Position.z + initTerrainPositionZ) * scaleZ)		
		))
		*scaleY
		+15;
		if(_camera2.View.y<10 && y_loon!=0)
			_camera2.View.y+=0.05f;

    //رسم الأرض
   DrawEarthBall();
   //رسم التضاريس
	DrawTerrain();

 glPopMatrix();

//_______________________________________________

 glPushMatrix();
	//النافذة الثالثة
	  glViewport(0, 0, m_windowWidth / 2, m_windowHeight / 2);


	//تشغيل الكاميرا الثالثة
    _camera3.Render();

	//رسم السماء
	DrawSkyBall();

   //رسم المنطاد
	our_loon.DrawLoon();
       
   //حركة الكاميرا
	if(y_loon>0)
	_camera3.Position.y=y_loon;

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


    //رسم الأرض
   DrawEarthBall();
   //رسم التضاريس
   if(!no_terren)
   	DrawTerrain();

 glPopMatrix();

//__________________________________________________

glPopMatrix();

	//النافذة الرابعة
     glViewport(m_windowWidth / 2, 0, m_windowWidth / 2, m_windowHeight / 2);
     
	//تشغيل الكاميرا الرابعة
    _camera4.Render();

	//رسم السماء
	DrawSkyBall();

   //رسم المنطاد
	our_loon.DrawLoon();
   
//حركة الكاميرا
	if(y_loon>0)
	_camera4.Position.y=y_loon;



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

    if(y_loon>16000)
	{
		   _camera4.Position.x=-5+x_loon+(y_loon*cos(angle_rotation));
           _camera4.Position.z=-20+z_loon+(y_loon*sin(angle_rotation));
	}

    //رسم الأرض
   DrawEarthBall();
   //رسم التضاريس
   if(!no_terren)
	 DrawTerrain();

  glPopMatrix();
}  //if(vision==4)






return true;
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

	fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag5555555

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
		
				case WM_MOUSEMOVE:
			{
				int oldMouseX, oldMouseY;
				 oldMouseX = mouseX;
		         oldMouseY = mouseY; 
				 mouseX = LOWORD(lParam);
		         mouseY = HIWORD(lParam);
				 				
				if ((mouseX - oldMouseX) > 0)
					_camera1.RotateY(-1*2);

				 if((mouseX - oldMouseX) < 0)
					 _camera1.RotateY(2);


				 if((mouseY - oldMouseY) > 0)
					 _camera1.View.y-=0.01;
				if((mouseY - oldMouseY) < 0)
					 _camera1.View.y+=0.015;


		 	    //NB 2016-10-09 Calling Cursor Function
			    NbCursorOptions(true,false,mouseX,mouseY);

		       return 0;
			}
		
		
	}


	return DefWindowProc(hWnd,uMsg,wParam,lParam);
	//+++++++--------33++323234562500000000
}

//int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
//					HINSTANCE	hPrevInstance,		// Previous Instance
//					LPSTR		lpCmdLine,			// Command Line Parameters
//					int			nCmdShow)			// Window Show State




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


int main(int argc,char *argv[])
{	

	//الطباعة في واجهة الكونسول
	   system("cls");
       cout<<"y_loon="<<y_loon<<endl;
	   cout<<"Fa = " << our_loon.f.archimedes.y<<endl;
	   cout<<"Fg = " << our_loon.f.forceOfGravity.y<<endl;
	   cout<<"-------------"<<endl;

	   string args[15];
	   for(int i = 0; i < argc; i++)
	   {
          args[i]=argv[i];
	   }




	   
        massBallon=double_Parse(args[6]);

	   our_loon.massHe=double_Parse(args[1]);
	   massBallon-=double_Parse(args[1]);
       rr+=double_Parse(args[1]);
		yy+=double_Parse(args[1]);

	   speed=double_Parse(args[2]);
       g=double_Parse(args[3]);
	   molarMassgaz=double_Parse(args[4]);
	   totalMass=double_Parse(args[5]);
	   p0=double_Parse(args[7]);
	   t0=double_Parse(args[8]);
	   R=double_Parse(args[9]);
	   valumeBalloon=double_Parse(args[10]);
	   molarMass=double_Parse(args[11]);
	planet_selected=args[12];
	if(planet_selected=="Earth")
	{
		Earth=true;
		Moon=false;
	}
	if(planet_selected=="Moon")
	{
		Moon=true;
		Earth=false;
		molarMassgaz=0;
	}




	MSG		msg;									// Windows Message Structure
	BOOL	done=FALSE;								// Bool Variable To Exit Loop  nnnnnmmmmmmmmmmmm

	// Ask The User Which Screen Mode They Prefer
//	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	//{
		fullscreen=FALSE;							// Windowed Mode
	//}

	// Create Our OpenGL Window
	if (!CreateGLWindow("Graphics Project",1350,690,16,fullscreen))
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
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()the main 
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
				if (!CreateGLWindow("Emad",700,500,16,fullscreen))
				{
					return 0;						// Quit If Window Was Not Created
				}

			}
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}



char * convert_to_char(string add , float t  ,int & length,string unity)
{
	string s=add;
	stringstream out;
	out << t;
	  //من أجل طباعة العبارات العادية
	if(t!=-1000000)
	   s += out.str();
	//من أجل طباعة الواحداة
	s+=" "+unity;
	length=s.length();
	char * c = new char [s.length()] ;

	for (unsigned int i = 0 ; i < s.length() ; i++)
		c[i]=s[i];
	return c;

}


void NbCursorOptions(bool hide_cursor, bool center, int mouse_x, int mouse_y){
	/* Nour Badran 2016-10-09
	 * This Function control to Cursor options
	 * Easy to use
	 */

	if(hide_cursor)
		ShowCursor(FALSE);
	else
		ShowCursor(TRUE);


	  POINT pt;                  // cursor location  
      RECT rc;                   // client area coordinates 
      GetCursorPos(&pt); 
      // Convert screen coordinates to client coordinates. 
      ScreenToClient(hWnd, &pt);   
      // Keep the cursor in the client area. 
      GetClientRect(hWnd, &rc); 	
      ClientToScreen(hWnd, &pt); 
	  
	if(center)
	{
	  pt.x = (rc.right - rc.left) / 2;
	  pt.y = (rc.bottom - rc.left) /2;
	  SetCursorPos(pt.x, pt.y); 
	}



	if(mouse_x != 0 && mouse_y != 0){
	     if(mouse_x > (rc.right -200) || mouse_x < (rc.left +200)){
            pt.x = (rc.right - rc.left) / 2;
	        ClientToScreen(hWnd, &pt); 
            SetCursorPos(pt.x, pt.y); 
	  }
	
	if(mouse_y < (rc.top + 100) || mouse_y > (rc.bottom - 100) ){	
		pt.y = (rc.bottom - rc.left) /2;
        ClientToScreen(hWnd, &pt); 
        SetCursorPos(pt.x, pt.y); 
	  }
	}
}