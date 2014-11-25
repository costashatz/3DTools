#include <iostream>
#include <3DTools/Helper.hpp>
#include <3DTools/Matrix3D.hpp>
using namespace std;
using namespace Tools3D;

/**
* Simple Example using Vector3D and Matrix3D classes
**/

int main()
{
	//Vector Addition
    Vector3Df a = Vector3Df(10,7,1.5);
    Vector3Df b = Vector3Df(-2,1,2.1);
    Vector3Df c = a+b;
    cout<<"("<<a.X()<<" "<<a.Y()<<" "<<a.Z()<<") + ("<<b.X()<<" "<<b.Y()<<" "<<b.Z()<<") = ("<<c.X()<<" "<<c.Y()<<" "<<c.Z()<<")\n";
	//Translation
    Matrix3Df mat = Matrix3Df();
	mat.Identity();
    mat.Translate(2,3,0);
	float** data;
	data = mat.getData(); //get the matrix data
	cout<<"Matrix -- Column Major (so far...maybe row major in next push)\n";
    for(int i=0;i<4;i++)
	{
        for(int j=0;j<4;j++)
		{
			cout<<data[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<"--------------------\n";
	c = a*mat;
    cout<<"("<<a.X()<<" "<<a.Y()<<" "<<a.Z()<<") Traslated by ("<<2<<" "<<3<<" "<<0<<") = ("<<c.X()<<" "<<c.Y()<<" "<<c.Z()<<")\n";
	//Rotation
    a = Vector3Df(1,2,1);
	mat.Identity();
    mat.RotateX(HalfPi);
	c = a*mat;
    cout<<"("<<a.X()<<" "<<a.Y()<<" "<<a.Z()<<") rotated by pi/2 radians around x-axis to ("<<c.X()<<" "<<c.Y()<<" "<<c.Z()<<")\n";
	mat.Identity();
    mat.RotateDegreesX(90);
	c = a*mat;
    cout<<"("<<a.X()<<" "<<a.Y()<<" "<<a.Z()<<") rotated by 90 degrees around x-axis to ("<<c.X()<<" "<<c.Y()<<" "<<c.Z()<<")\n";
	return(0);
}
