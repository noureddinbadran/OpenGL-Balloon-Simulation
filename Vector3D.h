//#include"cylindricalCoordinates.h"
class Vector3D
{
public:
	//Data Members
	double x;
	double y;
	double z;
	
	//Methods
	
	Vector3D();
	Vector3D(double x,double y,double z);
	void setVec(double x,double y,double z);
	//cylindricalCoordinates transletCylindricalCoordinate();
	double stringth();
	//void transletCartezihCoordinate(cylindricalCoordinates v);
	void mult_vec_cons(double m);
	void sum_vec(Vector3D va,Vector3D vg,Vector3D vr);
	void a(Vector3D va,Vector3D vg,Vector3D vr);//va ﬁÊ… √—Œ„Ìœ”  //vg ﬁÊ… «·Ã«–»Ì… «·√—÷Ì…  //vr ﬁÊ… „ﬁ«Ê„… «·ÂÊ«¡
	void v(Vector3D va,Vector3D vg,Vector3D vr,Vector3D last_speed,Vector3D wind);
	
};