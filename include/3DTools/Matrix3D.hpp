#ifndef MATRIX_3D_HPP
#define MATRIX_3D_HPP

/**
* Includes
**/
#include <cstring>
#include <3DTools/Vector3D.hpp>

namespace Tools3D {

/**
* Simple 3D Matrix Class (4x4 Matrix)
**/
template<class T>
class Matrix3D
{
protected:
    T data[4][4]; //Matrix Data
public:
    /**
    * Default Constructor
    * Initializes matrix to Identity
    **/
    Matrix3D(){ Identity();}

    /**
    * Copy Constructor
    * @param other - Matrix3D to copy from
    **/
    Matrix3D(const Matrix3D& other)
    {
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                data[i][j] = other.data[i][j];
    }

    /**
    * Constructor
    * @param table - 2-dimensional table to copy data from
    **/
    Matrix4D(T** table)
    {
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                data[i][j] = table[i][j];
    }

    /**
    * Make matrix Identity
    **/
    void Identity()
    {
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                if(i==j)
                    data[i][j] = 1;
                else
                    data[i][j] = 0;
            }
        }
    }

    /**
    * Get Matrix Data
    * @return T - the data
    **/
    T** getData()
    {
        T** data;
        data = new T*[4];
        for(int i=0;i<4;i++)
        {
            data[i] = new T[4];
            memcpy(data[i],this->data[i],4*sizeof(T));
        }
        return data;
    }

    /**
    * Translate this Matrix
    * @param dx - translation offset in x-axis
    * @param dy - translation offset in y-axis
    * @param dz - translation offset in z-axis
    **/
    void Translate(const T& dx, const T& dy, const T& dz)
    {
        Matrix3D temp = Matrix3D();
        temp.data[3][0] = dx;
        temp.data[3][1] = dy;
        (*this)*=temp;
    }

    /**
    * Scale this Matrix
    * @param dx - scale offset in x-axis
    * @param dy - scale offset in y-axis
    * @param dz - scale offset in z-axis
    **/
    void Scale(const T& dx, const T& dy, const T& dz)
    {
        Matrix3D temp = Matrix3D();
        temp.data[0][0] = dx;
        temp.data[1][1] = dy;
        temp.data[2][2] = dz;
        (*this)*=temp;
    }

    /**
    * Rotate this Matrix around x-axis
    * @param angle - angle in radians
    **/
    void RotateX(T angle)
    {
        double c = cos(angle);
        double s = sin(angle);
        Matrix3D temp = Matrix3D();
        temp.data[1][1] = c;
        temp.data[1][2] = s;
        temp.data[2][1] = -s;
        temp.data[2][2] = c;
        (*this)*=temp;
    }

    /**
    * Rotate this Matrix around x-axis
    * @param angle - angle in degrees
    **/
    void RotateDegreesX(T angle)
    {
        T a = DegreesToRadians(angle);
        RotateX(a);
    }

    /**
    * Rotate this Matrix around y-axis
    * @param angle - angle in radians
    **/
    void RotateY(T angle)
    {
        double c = cos(angle);
        double s = sin(angle);
        Matrix3D temp = Matrix3D();
        temp.data[0][0] = c;
        temp.data[2][0] = s;
        temp.data[0][2] = -s;
        temp.data[2][2] = c;
        (*this)*=temp;
    }

    /**
    * Rotate this Matrix around y-axis
    * @param angle - angle in degrees
    **/
    void RotateDegreesY(T angle)
    {
        T a = DegreesToRadians(angle);
        RotateY(a);
    }

    /**
    * Rotate this Matrix around z-axis
    * @param angle - angle in radians
    **/
    void RotateZ(T angle)
    {
        double c = cos(angle);
        double s = sin(angle);
        Matrix3D temp = Matrix3D();
        temp.data[0][0] = c;
        temp.data[0][1] = s;
        temp.data[1][0] = -s;
        temp.data[1][1] = c;
        (*this)*=temp;
    }

    /**
    * Rotate this Matrix around z-axis
    * @param angle - angle in degrees
    **/
    void RotateDegreesZ(T angle)
    {
        T a = DegreesToRadians(angle);
        RotateZ(a);
    }

    /**
    * Get Transpose of the Matrix
    * @return Matrix2D - the transposed matrix
    **/
    Matrix3D Transpose()
    {
        Matrix3D temp = Matrix3D();
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
                temp.data[j][i] = data[i][j];
        }
        return temp;
    }

    /**
    * Get the Determinant of the Matrix
    * @return T - the value of the Determinant
    **/
    T Det()const
    {
        return (data[0][0]*data[1][1]*data[2][2]*data[3][3]+data[0][0]*data[1][3]*data[2][1]*data[3][2]+data[0][0]*data[1][2]*data[2][3]*data[3][1]-data[0][0]*data[1][3]*data[2][2]*data[3][1]-data[0][0]*data[1][1]*data[2][3]*data[3][2]-data[0][0]*data[1][2]*data[2][1]*data[3][3]
        		-data[0][1]*data[1][0]*data[2][2]*data[3][3]-data[0][1]*data[1][2]*data[2][3]*data[3][0]-data[0][1]*data[1][3]*data[2][0]*data[3][2]+data[0][1]*data[1][3]*data[2][2]*data[3][0]
        		+data[0][1]*data[1][0]*data[2][3]*data[3][2]+data[0][1]*data[1][2]*data[2][0]*data[3][3]+data[0][2]*data[1][0]*data[2][1]*data[3][0]+data[0][2]*data[1][3]*data[2][0]*data[3][1]
        		-data[0][2]*data[1][3]*data[2][1]*data[3][0]-data[0][2]*data[1][0]*data[2][3]*data[3][1]-data[0][2]*data[1][0]*data[2][3]*data[3][1]-data[0][2]*data[1][1]*data[2][0]*data[3][3]-data[0][3]*data[1][0]*data[2][1]*data[3][2]-data[0][3]*data[1][1]*data[2][2]*data[3][0]
        		-data[0][3]*data[1][2]*data[2][0]+data[0][3]*data[1][2]*data[2][1]*data[3][0]+data[0][3]*data[1][0]*data[2][2]*data[3][1]+data[0][3]*data[1][1]*data[2][0]*data[3][2]);
    }

    /**
    * Get Inverse of the Matrix
    * @return Matrix2D - the inversed matrix
    **/
    Matrix3D Inverse()
    {
        T det = Det();
        Matrix3D temp = Matrix3D();
        if(det > std::numeric_limits<T>::epsilon())
        {
            temp.data[0][0] = data[1][2]*data[2][3]*data[3][1] - data[1][3]*data[2][2]*data[3][1] + data[1][3]*data[2][1]*data[3][2] - data[1][1]*data[2][3]*data[3][2] - data[1][2]*data[2][1]*data[3][3] + data[1][1]*data[2][2]*data[3][3];
            temp.data[0][1] = data[0][3]*data[2][2]*data[3][1] - data[0][2]*data[2][3]*data[3][1] - data[0][3]*data[2][1]*data[3][2] + data[0][1]*data[2][3]*data[3][2] + data[0][2]*data[2][1]*data[3][3] - data[0][1]*data[2][2]*data[3][3];
            temp.data[0][2] = data[0][2]*data[1][3]*data[3][1] - data[0][3]*data[1][2]*data[3][1] + data[0][3]*data[1][1]*data[3][2] - data[0][1]*data[1][3]*data[3][2] - data[0][2]*data[1][1]*data[3][3] + data[0][1]*data[1][2]*data[3][3];
            temp.data[0][3] = data[0][3]*data[1][2]*data[2][1] - data[0][2]*data[1][3]*data[2][1] - data[0][3]*data[1][1]*data[2][2] + data[0][1]*data[1][3]*data[2][2] + data[0][2]*data[1][1]*data[2][3] - data[0][1]*data[1][2]*data[2][3];
            temp.data[1][0] = data[1][3]*data[2][2]*data[3][0] - data[1][2]*data[2][3]*data[3][0] - data[1][3]*data[2][0]*data[3][2] + data[1][0]*data[2][3]*data[3][2] + data[1][2]*data[2][0]*data[3][3] - data[1][0]*data[2][2]*data[3][3];
            temp.data[1][1] = data[0][2]*data[2][3]*data[3][0] - data[0][3]*data[2][2]*data[3][0] + data[0][3]*data[2][0]*data[3][2] - data[0][0]*data[2][3]*data[3][2] - data[0][2]*data[2][0]*data[3][3] + data[0][0]*data[2][2]*data[3][3];
            temp.data[1][2] = data[0][3]*data[1][2]*data[3][0] - data[0][2]*data[1][3]*data[3][0] - data[0][3]*data[1][0]*data[3][2] + data[0][0]*data[1][3]*data[3][2] + data[0][2]*data[1][0]*data[3][3] - data[0][0]*data[1][2]*data[3][3];
            temp.data[1][3] = data[0][2]*data[1][3]*data[2][0] - data[0][3]*data[1][2]*data[2][0] + data[0][3]*data[1][0]*data[2][2] - data[0][0]*data[1][3]*data[2][2] - data[0][2]*data[1][0]*data[2][3] + data[0][0]*data[1][2]*data[2][3];
            temp.data[2][0] = data[1][1]*data[2][3]*data[3][0] - data[1][3]*data[2][1]*data[3][0] + data[1][3]*data[2][0]*data[3][1] - data[1][0]*data[2][3]*data[3][1] - data[1][1]*data[2][0]*data[3][3] + data[1][0]*data[2][1]*data[3][3];
            temp.data[2][1] = data[0][3]*data[2][1]*data[3][0] - data[0][1]*data[2][3]*data[3][0] - data[0][3]*data[2][0]*data[3][1] + data[0][0]*data[2][3]*data[3][1] + data[0][1]*data[2][0]*data[3][3] - data[0][0]*data[2][1]*data[3][3];
            temp.data[2][2] = data[0][1]*data[1][3]*data[3][0] - data[0][3]*data[1][1]*data[3][0] + data[0][3]*data[1][0]*data[3][1] - data[0][0]*data[1][3]*data[3][1] - data[0][1]*data[1][0]*data[3][3] + data[0][0]*data[1][1]*data[3][3];
            temp.data[2][3] = data[0][3]*data[1][1]*data[2][0] - data[0][1]*data[1][3]*data[2][0] - data[0][3]*data[1][0]*data[2][1] + data[0][0]*data[1][3]*data[2][1] + data[0][1]*data[1][0]*data[2][3] - data[0][0]*data[1][1]*data[2][3];
            temp.data[3][0] = data[1][2]*data[2][1]*data[3][0] - data[1][1]*data[2][2]*data[3][0] - data[1][2]*data[2][0]*data[3][1] + data[1][0]*data[2][2]*data[3][1] + data[1][1]*data[2][0]*data[3][2] - data[1][0]*data[2][1]*data[3][2];
            temp.data[3][1] = data[0][1]*data[2][2]*data[3][0] - data[0][2]*data[2][1]*data[3][0] + data[0][2]*data[2][0]*data[3][1] - data[0][0]*data[2][2]*data[3][1] - data[0][1]*data[2][0]*data[3][2] + data[0][0]*data[2][1]*data[3][2];
            temp.data[3][2] = data[0][2]*data[1][1]*data[3][0] - data[0][1]*data[1][2]*data[3][0] - data[0][2]*data[1][0]*data[3][1] + data[0][0]*data[1][2]*data[3][1] + data[0][1]*data[1][0]*data[3][2] - data[0][0]*data[1][1]*data[3][2];
            temp.data[3][3] = data[0][1]*data[1][2]*data[2][0] - data[0][2]*data[1][1]*data[2][0] + data[0][2]*data[1][0]*data[2][1] - data[0][0]*data[1][2]*data[2][1] - data[0][1]*data[1][0]*data[2][2] + data[0][0]*data[1][1]*data[2][2];
            temp /= det;
        }
        return temp;
    }

    /**
    * Overload basic operators
    * mathematic operators (*,/)
    **/
    const Matrix3D& operator*=(const T& other)
    {
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
                data[i][j] *= other;
        }
        return *this;
    }

    const Matrix3D& operator/=(const T& other)
    {
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
                data[i][j] /= other;
        }
        return *this;
    }

    const Matrix3D& operator*=(const Matrix3D& other)
    {
        Matrix3D temp = Matrix3D();
        temp.data[0][0] = data[0][0]*other.data[0][0]+data[0][1]*other.data[1][0]+data[0][2]*other.data[2][0]+data[0][3]*other.data[3][0];
        temp.data[0][1] = data[0][0]*other.data[0][1]+data[0][1]*other.data[1][1]+data[0][2]*other.data[2][1]+data[0][3]*other.data[3][1];
        temp.data[0][2] = data[0][0]*other.data[0][2]+data[0][1]*other.data[1][2]+data[0][2]*other.data[2][2]+data[0][3]*other.data[3][2];
        temp.data[0][3] = data[0][0]*other.data[0][3]+data[0][1]*other.data[1][3]+data[0][2]*other.data[2][3]+data[0][3]*other.data[3][3];

        temp.data[1][0] = data[1][0]*other.data[0][0]+data[1][1]*other.data[1][0]+data[1][2]*other.data[2][0]+data[1][3]*other.data[3][0];
        temp.data[1][1] = data[1][0]*other.data[0][1]+data[1][1]*other.data[1][1]+data[1][2]*other.data[2][1]+data[1][3]*other.data[3][1];
        temp.data[1][2] = data[1][0]*other.data[0][2]+data[1][1]*other.data[1][2]+data[1][2]*other.data[2][2]+data[1][3]*other.data[3][2];
        temp.data[1][3] = data[1][0]*other.data[0][3]+data[1][1]*other.data[1][3]+data[1][2]*other.data[2][3]+data[1][3]*other.data[3][3];

        temp.data[2][0] = data[2][0]*other.data[0][0]+data[2][1]*other.data[1][0]+data[2][2]*other.data[2][0]+data[2][3]*other.data[3][0];
        temp.data[2][1] = data[2][0]*other.data[0][1]+data[2][1]*other.data[1][1]+data[2][2]*other.data[2][1]+data[2][3]*other.data[3][1];
        temp.data[2][2] = data[2][0]*other.data[0][2]+data[2][1]*other.data[1][2]+data[2][2]*other.data[2][2]+data[2][3]*other.data[3][2];
        temp.data[2][3] = data[2][0]*other.data[0][3]+data[2][1]*other.data[1][3]+data[2][2]*other.data[2][3]+data[2][3]*other.data[3][3];

        temp.data[3][0] = data[3][0]*other.data[0][0]+data[3][1]*other.data[1][0]+data[3][2]*other.data[2][0]+data[3][3]*other.data[3][0];
        temp.data[3][1] = data[3][0]*other.data[0][1]+data[3][1]*other.data[1][1]+data[3][2]*other.data[2][1]+data[3][3]*other.data[3][1];
        temp.data[3][2] = data[3][0]*other.data[0][2]+data[3][1]*other.data[1][2]+data[3][2]*other.data[2][2]+data[3][3]*other.data[3][2];
        temp.data[3][3] = data[3][0]*other.data[0][3]+data[3][1]*other.data[1][3]+data[3][2]*other.data[2][3]+data[3][3]*other.data[3][3];

        (*this) = temp;
        return *this;
    }

    /**
    * Overloading () operator
    * Access Matrix Matlab-like
    * @params i - row index to return
    * @params j - column index to return
    * @return T - value of i,j-th element
    **/
    T& operator()(unsigned int i, unsigned int j)
    {
        return data[i][j];
    }

    template<class U>
    friend Vector3D<U> operator*(Vector3D<U>& vec, const Matrix3D<U>& mat);
    friend const Vector3D<T>& Vector3D<T>::operator *=(const Matrix3D& other);
};

/**
* Functions Overloading basic operators
* mathematic operators
* equality operators
* dot products
**/

template<class T>
Matrix3D<T> operator*(const Matrix3D<T>& mat1, T val)
{
    Matrix3D<T> temp = Matrix3D<T>(mat1);
    temp *= val;
    return temp;
}

template<class T>
Matrix3D<T> operator*(T val, const Matrix3D<T>& mat1)
{
    Matrix3D<T> temp = Matrix3D<T>(mat1);
    temp *= val;
    return temp;
}

template<class T>
Matrix3D<T> operator/(const Matrix3D<T>& mat1, T val)
{
    Matrix3D<T> temp = Matrix3D<T>(mat1);
    temp /= val;
    return temp;
}

template<class T>
Matrix3D<T> operator*(const Matrix3D<T>& mat1, const Matrix3D<T>& mat2)
{
    Matrix3D<T> temp = Matrix3D<T>(mat1);
    temp *= mat2;
    return temp;
}

template<class T>
Vector3D<T> operator*(Vector3D<T>& vec, const Matrix3D<T>& mat)
{
    Vector3D<T> temp = Vector3D<T>();
    temp.SetX(vec.X()*mat.data[0][0]+vec.Y()*mat.data[1][0]+vec.Z()*mat.data[2][0]+mat.data[3][0]);
    temp.SetY(vec.X()*mat.data[0][1]+vec.Y()*mat.data[1][1]+vec.Z()*mat.data[2][1]+mat.data[3][1]);
    temp.SetZ(vec.X()*mat.data[0][2]+vec.Y()*mat.data[1][2]+vec.Z()*mat.data[2][2]+mat.data[3][2]);
    return temp;
}

template<class T>
Vector3D<T> operator*(const Matrix3D<T>& m, Vector3D<T>& vec)
{
    Vector3D<T> temp = Vector3D<T>(vec);
    temp = temp*m;
    return temp;
}

template<class T>
const Vector3D<T>& Vector3D<T>::operator *=(const Matrix3D<T>& other)
{
    Vector3D<T> temp;
    temp.x = x*other.data[0][0]+y*other.data[1][0]+z*other.data[2][0]+other.data[3][0];
    temp.y = x*other.data[0][1]+y*other.data[1][1]+z*other.data[2][1]+other.data[3][1];
    temp.z = x*other.data[0][2]+y*other.data[1][2]+z*other.data[2][2]+other.data[3][2];
    (*this) = temp;
    return *this;
}

typedef Matrix3D<double> Matrix3Dd;
typedef Matrix3D<float> Matrix3Df;

}

#endif
