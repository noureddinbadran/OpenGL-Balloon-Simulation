#include"Vector3D.h"
#include"math.h"
//#include"cylindricalCoordinates.h"
//#include"Constants.h"
Vector3D::Vector3D()
{
	    x=0;
	    y=0;
	    z=0;
}
Vector3D::Vector3D(double x, double y, double z)
{
        this->x=x;
		this->y=y;
		this->z=z;
}
double y4=0;
double massBallon0 = 50;
double time = 0.5;

void Vector3D::setVec(double x,double y,double z)
{
	    (*this).x=x;
		(*this).y=y;
		(*this).z=z;

}


double Vector3D::stringth()
{
	return(sqrt(pow(x,2)+pow(y,2)+pow(z,2)));
}

//void Vector3D::transletCartezihCoordinate(cylindricalCoordinates v)
//{
//	x=v.p*cos(v.angle);
//    y=v.p*sin(v.angle);
//	z=v.oz;
//}

void Vector3D::mult_vec_cons(double m)
{
		x=x*m;
	    y=y*m;
	    z=z*m;
}

void Vector3D::sum_vec(Vector3D va, Vector3D vg, Vector3D vr)
{
		x=va.x+vg.x+vr.x;
	    y=va.y+vg.y+vr.y;
	    z=va.z+vg.z+vr.z;
}

void Vector3D::a(Vector3D va, Vector3D vg, Vector3D vr)
{
		(*this).sum_vec(va,vg,vr);
		(*this).mult_vec_cons(1/massBallon0);
	    //vt.x=(va.x+vg.x+vr.x)/totalMass;//ÞæÉ ÃÑÎãíÏÓ +ÞæÉ ÇáÌÇÐÈíÉ ÇáÃÑÖíÉ+ÞæÉ ãÞÇæãÉ ÇáåæÇÁ
	    //vt.y=(va.y+vg.y+vr.y)/totalMass;//ÞæÉ ÃÑÎãíÏÓ +ÞæÉ ÇáÌÇÐÈíÉ ÇáÃÑÖíÉ+ÞæÉ ãÞÇæãÉ ÇáåæÇÁ
	    //vt.z=(va.z+vg.z+vr.z)/totalMass;//ÞæÉ ÃÑÎãíÏÓ +ÞæÉ ÇáÌÇÐÈíÉ ÇáÃÑÖíÉ+ÞæÉ ãÞÇæãÉ ÇáåæÇÁ
}
//double y4=0;

void Vector3D::v(Vector3D va, Vector3D vg, Vector3D vr, Vector3D last_speed, Vector3D wind)
{
		last_speed.a(va,vg,vr);
		y4=last_speed.y;
		if  (fabs(last_speed.y)>0.1)
		{
			(*this).a(va,vg,vr); 
			(*this).mult_vec_cons(time);
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