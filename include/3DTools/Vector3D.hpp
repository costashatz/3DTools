#ifndef VECTOR_3D_HPP
#define VECTOR_3D_HPP

/**
* Includes and Required Matrix2D class
**/
#include <cmath>
#include <limits>

namespace Tools3D {

template<class T>
class Matrix3D;


/**
* Simple 3D Vector Class
**/
template<class T>
class Vector3D
{
private:
    T x; // x component
    T y; // y component
    T z; // z component
public:
    /**
    * Default Constructor
    * Initializes x, y and z to zero
    **/
    Vector3D():x(0.0),y(0.0),z(0.0){}

    /**
    * Constructor
    * @param a - value to be assigned to x
    * @param b - value to be assigned to y
    * @param c - value to be assigned to z
    **/
    Vector3D(const T& a, const T& b, const T& c):x(a),y(b),z(c){}

    /**
    * Copy Constructor
    * @param other - Vector2D to copy from
    **/
    Vector3D(const Vector3D& other)
    {
        this->x = other.x;
        this->y = other.y;
        this->z = other.z;
    }

    /**
    * Get X component
    * @return T - the X value
    **/
    T X() {return x;}

    /**
    * Get Y component
    * @return T - the Y value
    **/
    T Y() {return y;}

    /**
    * Get Z component
    * @return T - the Z value
    **/
    T Z() {return z;}

    /**
    * Set X component
    * @param a - value to set
    **/
    void SetX(T a) {x=a;}

    /**
    * Set Y component
    * @param b - value to set
    **/
    void SetY(T b) {y=b;}

    /**
    * Set Z component
    * @param c - value to set
    **/
    void SetZ(T c) {z=c;}

    /**
    * Make vector zero (x=y=z=0)
    **/
    void Zero() {x=0.0;y=0.0;z=0.0;}

    /**
    * Test if vector is zero?
    * @return bool - true if vector is zero
    **/
    bool IsZero()const {return (x*x+y*y+z*z)<std::numeric_limits<T>::epsilon();}

    /**
    * Normalize vector
    **/
    void Normalize()
    {
        T length = Length();
        // Only normalize if length not zero
        if(length > std::numeric_limits<T>::epsilon())
        {
            x /= length;
            y /= length;
            z /= length;
        }
    }

    /**
    * Get Cross Product of Vectors
    * @return Vector3D - the cross product of the vectors
    **/
    Vector3D Cross(const Vector3D& other) {return Vector3D(y*other.z-z*other.y, z*other.x-x*other.z, x*other.y-y*other.x);}

    /**
    * Get Reverse Vector (-x,-y,-z)
    * @return Vector3D - the reversed vector
    **/
    Vector3D Reverse(){return Vector3D(-x,-y,-z);}

    /**
    * Get Length of Vector
    * @return T - length of the vector
    *  @see LengthSq()
    **/
    T Length()const {return sqrt(x*x+y*y+z*z);}

    /**
    * Get Length Squared of Vector (avoids sqrt function - for quick tests or fast code)
    * @return T - length squared of the vector
    *  @see Length()
    **/
    T LengthSq()const {return (x*x+y*y+z*z);}

    /**
    * Dot product with other vector
    * @param other - vector to compute dot with
    * @return - the dot product
    **/
    T Dot(const Vector3D& other)const
    {
        return (x*other.x+y*other.y+z*other.z);
    }

    /**
    * Distance to other vector
    * @param other - vector to compute distance to
    * @return T - distance to other vector
    *  @see DistanceSq()
    **/
    T Distance(const Vector3D& other)const
    {
        T xSep = other.x-x;
        T ySep = other.y-y;
        T zSep = other.z-z;
        return sqrt(xSep*xSep+ySep*ySep+zSep*zSep);
    }

    /**
    * Distance Squared to other vector (avoids sqrt function - for quick tests or fast code)
    * @param other - vector to compute distance to
    * @return T - distance squared to other vector
    * @see Distance()
    **/
    T DistanceSq(const Vector3D& other)const
    {
        T xSep = other.x-x;
        T ySep = other.y-y;
        T zSep = other.z-z;
        return xSep*xSep+ySep*ySep+zSep*zSep;
    }

    /**
    * Angle with other vector
    * @param other - vector to compute angle with
    * @return T - the angle with the vector
    **/
    T Angle(const Vector3D& other)const
    {
        T dot = Dot(other);
        return acos(dot/(Length()*other.Length()));
    }


    /**
    * Overload basic operators
    * mathematic operators (*,/,+,-)
    * equality operators (==,!=)
    **/
    const Vector3D& operator-=(const Vector3D& other)
    {
        x -= other.x;
        y -= other.y;
        z -= other.z;
        return *this;
    }
    const Vector3D& operator+=(const Vector3D& other)
    {
        x += other.x;
        y += other.y;
        z += other.z;
        return *this;
    }
    const Vector3D& operator*=(const T& other)
    {
        x *= other;
        y *= other;
        z *= other;
        return *this;
    }

    // Used for Matrix-Vector multiplications
    inline const Vector3D& operator*=(const Matrix3D<T>& other);

    const Vector3D& operator/=(const T& other)
    {
        // Divide only if other is not zero
        if(other > std::numeric_limits<T>::epsilon())
        {
            x /= other;
            y /= other;
            z /= other;
        }
        return *this;
    }

    bool operator==(const Vector3D& other)const
    {
        return (x==other.x)&&(y==other.y)&&(z==other.z);
    }
    bool operator!=(const Vector3D& other)const
    {
        return(x!=other.x)||(y!=other.y)||(z!=other.z);
    }
};

/**
* Functions Overloading basic operators
* mathematic operators
* equality operators
* dot products
**/

template<class T>
T operator*(const Vector3D<T>& vec1, const Vector3D<T>& vec2)
{
    Vector3D<T> res = vec1;
    return res.Dot(vec2);
}

template<class T>
Vector3D<T> operator*(const Vector3D<T>& vec, T val)
{
    Vector3D<T> res = vec;
    res *= val;
    return res;
}

template<class T>
Vector3D<T> operator*(T val, const Vector3D<T>& vec)
{
    Vector3D<T> res = vec;
    res *= val;
    return res;
}

template<class T>
Vector3D<T> operator+(const Vector3D<T>& vec1, const Vector3D<T>& vec2)
{
    Vector3D<T> res = vec1;
    res += vec2;
    return res;
}

template<class T>
Vector3D<T> operator-(const Vector3D<T>& vec1, const Vector3D<T>& vec2)
{
    Vector3D<T> res = vec1;
    res -= vec2;
    return res;
}

template<class T>
Vector3D<T> operator/(const Vector3D<T>& vec, T val)
{
    Vector3D<T> res = vec;
    res /= val;
    return res;
}

typedef Vector3D<double> Vector3Dd;
typedef Vector3D<float> Vector3Df;

}

#endif
