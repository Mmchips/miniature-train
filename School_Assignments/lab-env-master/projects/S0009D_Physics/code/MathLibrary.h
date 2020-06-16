#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>
#include <vector>


class Vector4D
{
public:
    inline Vector4D();
	inline Vector4D(float x, float y, float z);
    inline Vector4D(float x, float y, float z, float w);
    inline Vector4D(const Vector4D &vector);
    inline ~Vector4D();

    inline Vector4D operator+(const Vector4D &vector);
    inline Vector4D operator-(const Vector4D &vector);
    inline Vector4D operator*(const float &i);
    inline Vector4D operator*(const Vector4D &vector);
    inline Vector4D operator/(const float &i);
    inline void operator=(const Vector4D &vector);
    inline bool operator==(const Vector4D &vector);
    inline float& operator[](int i);

    inline float dot(const Vector4D &vector);
    inline Vector4D cross(const Vector4D &vector);
    inline float length();
    inline float length4D();
    inline Vector4D normalize();
    inline Vector4D normalize4D();
    static inline Vector4D lerp(Vector4D &start, Vector4D &end, double percent);
    static inline Vector4D slerp(Vector4D &start, Vector4D &end, double percent);

    inline float getX() const;
    inline float getY() const;
    inline float getZ() const;
    inline float getW() const;

    inline void setX(float x);
    inline void setY(float y);
    inline void setZ(float z);
    inline void setW(float w);

    static inline Vector4D Min(Vector4D &v1, Vector4D &v2);
    static inline Vector4D Max(Vector4D &v1, Vector4D &v2);
    static inline float Min(float &f1, float &f2);
    static inline float Max(float &f1, float &f2);

private:
	/**
	*Array som h�ller 4 floats i en vektor
	*/
	float arr[4];
};

/**
 * -----------------------------------------------------------------------------------------------------------------------------------------------------
 */

class Matrix4D //Klass f�r matriser
{
public:
    inline Matrix4D();
    inline Matrix4D(float a, float b, float c, float d, float e, float f, float g, float h, float i);
    inline Matrix4D(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p);
    inline ~Matrix4D();

    inline Matrix4D operator*(const Matrix4D &matrix);
    inline Vector4D operator*(const Vector4D &vector);
    inline Matrix4D operator*(const float &w);
    inline Matrix4D operator+(const Matrix4D &matrix);
    inline void operator=(const Matrix4D &matrix);
    inline float* operator[](int i);

    inline void gramSchmidtOrto();

    static inline Matrix4D rotateX(float v);
    static inline Matrix4D rotateY(float v);
    static inline Matrix4D rotateZ(float v);
    static inline Matrix4D rotateVec(const Vector4D &vector, float v);
    static inline Matrix4D ProjectionMat(const float &fov, const float &near, const float &far);
    static inline Matrix4D ViewMat(Vector4D eye, Vector4D target, Vector4D up);

    inline void transpose();
    inline Matrix4D inverse();
    inline float* TransformFrom2DTo1D();
    static inline Matrix4D QuatToMat(Vector4D q);
    inline float get(int i, int j) const;
    inline void set(int i, int j, float x);
    inline Vector4D getPosition();
    inline void setPosition(Vector4D vec);
    inline void setScale(Vector4D vec);

private:

    /**
    *4x4 array som h�ller matrisens data
    */
    float mat[4][4];
};

/**
 * -----------------------------------------------------------------------------------------------------------------------------------------------------
 */

class Plane //Klass för plan
{
public:
    inline Plane();
    inline Plane(Vector4D, Vector4D);
    inline ~Plane();

    inline Vector4D getNormal();
    inline Vector4D getPoint();

private:
    Vector4D normal;
    Vector4D point;
};

/**
 * -----------------------------------------------------------------------------------------------------------------------------------------------------
 */

struct AABB
{
    Vector4D min = Vector4D(INFINITY, INFINITY, INFINITY);
    Vector4D max = Vector4D(-INFINITY, -INFINITY, -INFINITY);
    Vector4D obb[8];

    AABB(Vector4D min, Vector4D max)
    {
        this->min = min;
        this->max = max;
    }
    AABB()
    {
    }
};

/**
 * -----------------------------------------------------------------------------------------------------------------------------------------------------
 */

class Ray
{
public:
    inline Ray();
    inline Ray(Vector4D, Vector4D);
    inline ~Ray();

    inline bool intersect(Plane plane, Vector4D &outVec);
    inline bool pointInPlane(Vector4D, Vector4D, Vector4D, Vector4D);
    inline bool intersectAABB(AABB box, Vector4D &outVec);

private:
    Vector4D direction;
    Vector4D startPoint;
};

/**
 * ----------------------------------------------------VECTORS------------------------------------------------------------------------------------------
 */

/**
*Default konstruktor, ifall inga v�rden matas in s� blir vektorn (0,0,0,1)
*/
Vector4D::Vector4D()
{
    arr[0] = 0.0f;
    arr[1] = 0.0f;
    arr[2] = 0.0f;
    arr[3] = 1.0f;
}

/**
*Konstruktor som k�rs varje g�ng en vektor skapas. Vektorn f�r de v�rden som matas in, (x,y,z,1).
*/
Vector4D::Vector4D(float x, float y, float z)
{
    arr[0] = x;
    arr[1] = y;
    arr[2] = z;
    arr[3] = 1.0f;
}

Vector4D::Vector4D(float x, float y, float z, float w)
{
    arr[0] = x;
    arr[1] = y;
    arr[2] = z;
    arr[3] = w;
}

/**
*Kopieringskonstruktor
*/
Vector4D::Vector4D(const Vector4D &vector)
{
    arr[0] = vector.arr[0];
    arr[1] = vector.arr[1];
    arr[2] = vector.arr[2];
    arr[3] = vector.arr[3];
}

/**
*Dekonstruktor som inte g�r n�tt
*/
Vector4D::~Vector4D()
{
}

/**
*�verlagrar +operatorn s� man kan addera vektorer med varandra
*/
Vector4D Vector4D::operator+(const Vector4D &vector)
{
    float newX = arr[0] + vector.arr[0];
    float newY = arr[1] + vector.arr[1];
    float newZ = arr[2] + vector.arr[2];

    return Vector4D(newX, newY, newZ);
}

/**
*�verlagrar -operatorn s� man kan subtrahera vektorer med varandra
*/
Vector4D Vector4D::operator-(const Vector4D &vector)
{
    float newX = arr[0] - vector.arr[0];
    float newY = arr[1] - vector.arr[1];
    float newZ = arr[2] - vector.arr[2];

    return Vector4D(newX, newY, newZ);
}

/**
*�verlagrar *operatorn s� man kan multiplicera vektorer med en skal�r
*/
Vector4D Vector4D::operator*(const float &i)
{
    float newX = arr[0] * i;
    float newY = arr[1] * i;
    float newZ = arr[2] * i;

    return Vector4D(newX, newY, newZ);
}

/**
*�verlagrar *operatorn s� man kan multiplicera vektorer med varandra
*/
Vector4D Vector4D::operator*(const Vector4D &vector)
{
    float newX = ((arr[1]*vector.arr[2]) - (arr[2]*vector.arr[1]));
    float newY = ((arr[2]*vector.arr[0]) - (arr[0]*vector.arr[2]));
    float newZ = ((arr[0]*vector.arr[1]) - (arr[1]*vector.arr[0]));

    return Vector4D(newX, newY, newZ);
}

Vector4D Vector4D::operator/(const float &i)
{
    float temp = 1 / i;

    float newX = arr[0] * temp;
    float newY = arr[1] * temp;
    float newZ = arr[2] * temp;

    return Vector4D(newX, newY, newZ);
}

void Vector4D::operator=(const Vector4D &vector)
{
    arr[0] = vector.arr[0];
    arr[1] = vector.arr[1];
    arr[2] = vector.arr[2];
    arr[3] = vector.arr[3];
}

bool Vector4D::operator==(const Vector4D &vector)
{
    return(arr[0] == vector.arr[0] && arr[1] == vector.arr[1] && arr[2] == vector.arr[2] && arr[3] == vector.arr[3]);
}

/**
*�verlagring av []operatorn f�r att enkelt f� ut data ur en vektor
*/
float& Vector4D::operator[](int i)
{
    return arr[i];
}

/**
*Funktion f�r att f� fram skal�rprodukten av tv� vektorer
*/
float Vector4D::dot(const Vector4D &vector)
{
    return arr[0]*vector.arr[0] + arr[1]*vector.arr[1] + arr[2]*vector.arr[2];
}

Vector4D Vector4D::cross(const Vector4D &vector)
{
    float newX = ((arr[1] * vector.arr[2]) - (arr[2] * vector.arr[1]));
    float newY = ((arr[2] * vector.arr[0]) - (arr[0] * vector.arr[2]));
    float newZ = ((arr[0] * vector.arr[1]) - (arr[1] * vector.arr[0]));

    return Vector4D(newX, newY, newZ);
}

/**
*Funktion f�r att f� fram l�ngden av en vektor
*/
float Vector4D::length()
{
    return sqrtf((arr[0]*arr[0]) + (arr[1]*arr[1]) + (arr[2]*arr[2]));
}

float Vector4D::length4D()
{
    return sqrtf((arr[0]*arr[0]) + (arr[1]*arr[1]) + (arr[2]*arr[2]) + (arr[3]*arr[3]));
}

/**
*Funktion f�r att normalisera en vektor
*/
Vector4D Vector4D::normalize()
{
    float len = 1.0f/length();
    float x = arr[0]*len;
    float y = arr[1]*len;
    float z = arr[2]*len;

    return Vector4D(x, y, z);
}

Vector4D Vector4D::normalize4D()
{
    float len = 1.0f/length4D();
    float x = arr[0]*len;
    float y = arr[1]*len;
    float z = arr[2]*len;
    float w = arr[3]*len;

    return Vector4D(x, y, z, w);
}

/**
 *Linear interpolation
 */
Vector4D Vector4D::lerp(Vector4D &start, Vector4D &end, double percent)
{
    return (start + (end - start)*percent);
}

/**
 * Spherical linear interpolation
 */
Vector4D Vector4D::slerp(Vector4D &start, Vector4D &end, double percent)
{
    start.normalize4D();
    end.normalize4D();

    float dot = start.dot(end);

    const double DOT_THRESHOLD = 0.999995;
    if(fabs(dot) > DOT_THRESHOLD)
    {
        float x = start[0] + percent * (end[0] - start[0]);
        float y = start[1] + percent * (end[1] - start[1]);
        float z = start[2] + percent * (end[2] - start[2]);
        float w = start[3] + percent * (end[3] - start[3]);

        Vector4D result(x, y, z, w);

        result.normalize4D();
        return result;
    }

    if (dot < 0.0f)
    {
        end[0] = -end[0];
        end[1] = -end[1];
        end[2] = -end[2];
        end[3] = -end[3];
        dot = -dot;
    }

    if (dot > 1.0f)
    {
        dot = 1.0f;
    }
    else if(dot < -1.0f)
    {
        dot = -1.0f;
    }

    double theta_0 = acos(dot);
    double theta = theta_0 * percent;

    float x = end[0] - start[0] * percent;
    float y = end[1] - start[1] * percent;
    float z = end[2] - start[2] * percent;
    float w = end[3] - start[3] * percent;

    Vector4D temp(x, y, z, w);
    temp.normalize4D();

    float x1 = start[0]*cos(theta) + temp[0] * sin(theta);
    float y1 = start[1]*cos(theta) + temp[1] * sin(theta);
    float z1 = start[2]*cos(theta) + temp[2] * sin(theta);
    float w1 = start[3]*cos(theta) + temp[3] * sin(theta);

    return Vector4D(x1, y1, z1, w1);
}

/**
*Funktion som returnerar x-v�rdet i en vektor
*/
float Vector4D::getX() const
{
    return arr[0];
}

/**
*Funktion som returnerar y-v�rdet i en vektor
*/
float Vector4D::getY() const
{
    return arr[1];
}

/**
*Funktion som returnerar z-v�rdet i en vektor
*/
float Vector4D::getZ() const
{
    return arr[2];
}

/**
*Funktion som returnerar w-v�rdet i en vektor
*/
float Vector4D::getW() const
{
    return arr[3];
}

/**
*Funktion som s�tter x-v�rdet i en vektor
*/
void Vector4D::setX(float x)
{
    arr[0] = x;
}

/**
*Funktion som s�tter y-v�rdet i en vektor
*/
void Vector4D::setY(float y)
{
    arr[1] = y;
}

/**
*Funktion som s�tter z-v�rdet i en vektor
*/
void Vector4D::setZ(float z)
{
    arr[2] = z;
}

/**
*Funktion som s�tter w-v�rdet i en vektor
*/
void Vector4D::setW(float w)
{
    arr[3] = w;
}

Vector4D Vector4D::Min(Vector4D &v1, Vector4D &v2)
{
    float minX, minY, minZ;
    if(v1[0] < v2[0])
        minX = v1[0];
    else
        minX = v2[0];
    if(v1[1] < v2[1])
        minY = v1[1];
    else
        minY = v2[1];
    if(v1[2] < v2[2])
        minZ = v1[2];
    else
        minZ = v2[2];
    return Vector4D(minX, minY, minZ);
}

Vector4D Vector4D::Max(Vector4D &v1, Vector4D &v2)
{
    float maxX, maxY, maxZ;
    if(v1[0] > v2[0])
        maxX = v1[0];
    else
        maxX = v2[0];
    if(v1[1] > v2[1])
        maxY = v1[1];
    else
        maxY = v2[1];
    if(v1[2] > v2[2])
        maxZ = v1[2];
    else
        maxZ = v2[2];
    return Vector4D(maxX, maxY, maxZ);
}

float Vector4D::Min(float &f1, float &f2)
{
    if(f1 < f2)
        return f1;
    else
        return f2;
}

float Vector4D::Max(float &f1, float &f2)
{
    if(f1 > f2)
        return f1;
    else
        return f2;
}

/**
 * ----------------------------------------------------MATRIX-------------------------------------------------------------------------------------------
 */

/**
*Default konstruktor som k�rs ifall ingen data matas in och ger en identitetsmatris
*/
Matrix4D::Matrix4D()
{
    mat[0][0] = 1.0f;
    mat[0][1] = 0.0f;
    mat[0][2] = 0.0f;
    mat[0][3] = 0.0f;
    mat[1][0] = 0.0f;
    mat[1][1] = 1.0f;
    mat[1][2] = 0.0f;
    mat[1][3] = 0.0f;
    mat[2][0] = 0.0f;
    mat[2][1] = 0.0f;
    mat[2][2] = 1.0f;
    mat[2][3] = 0.0f;
    mat[3][0] = 0.0f;
    mat[3][1] = 0.0f;
    mat[3][2] = 0.0f;
    mat[3][3] = 1.0f;
}

/**
*Konstruktor som k�rs ifall data f�r en 3x3 matris matas in. Resten av matrisen fylls ut av homogena koordinater
*/
Matrix4D::Matrix4D(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
    mat[0][0] = a;
    mat[0][1] = b;
    mat[0][2] = c;
    mat[0][3] = 0.0f;
    mat[1][0] = d;
    mat[1][1] = e;
    mat[1][2] = f;
    mat[1][3] = 0.0f;
    mat[2][0] = g;
    mat[2][1] = h;
    mat[2][2] = i;
    mat[2][3] = 0.0f;
    mat[3][0] = 0.0f;
    mat[3][1] = 0.0f;
    mat[3][2] = 0.0f;
    mat[3][3] = 1.0f;
}

/**
*Konstruktor som k�rs ifall data f�r en 4x4 matris matas in
*/
Matrix4D::Matrix4D(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p)
{
    mat[0][0] = a;
    mat[0][1] = b;
    mat[0][2] = c;
    mat[0][3] = d;
    mat[1][0] = e;
    mat[1][1] = f;
    mat[1][2] = g;
    mat[1][3] = h;
    mat[2][0] = i;
    mat[2][1] = j;
    mat[2][2] = k;
    mat[2][3] = l;
    mat[3][0] = m;
    mat[3][1] = n;
    mat[3][2] = o;
    mat[3][3] = p;
}

/**
*Dekonstruktor som inte g�r n�got
*/
Matrix4D::~Matrix4D()
{
}

/**
*�verlagring av *operatorn f�r att kunna multiplicera matriser med varandra
*/
Matrix4D Matrix4D::operator*(const Matrix4D &matrix)
{
    float a = (mat[0][0]*matrix.mat[0][0]) + (mat[0][1]*matrix.mat[1][0]) + (mat[0][2]*matrix.mat[2][0]) + (mat[0][3]*matrix.mat[3][0]);
    float b = (mat[0][0]*matrix.mat[0][1]) + (mat[0][1]*matrix.mat[1][1]) + (mat[0][2]*matrix.mat[2][1]) + (mat[0][3]*matrix.mat[3][1]);
    float c = (mat[0][0]*matrix.mat[0][2]) + (mat[0][1]*matrix.mat[1][2]) + (mat[0][2]*matrix.mat[2][2]) + (mat[0][3]*matrix.mat[3][2]);
    float d = (mat[0][0]*matrix.mat[0][3]) + (mat[0][1]*matrix.mat[1][3]) + (mat[0][2]*matrix.mat[2][3]) + (mat[0][3]*matrix.mat[3][3]);

    float e = (mat[1][0]*matrix.mat[0][0]) + (mat[1][1]*matrix.mat[1][0]) + (mat[1][2]*matrix.mat[2][0]) + (mat[1][3]*matrix.mat[3][0]);
    float f = (mat[1][0]*matrix.mat[0][1]) + (mat[1][1]*matrix.mat[1][1]) + (mat[1][2]*matrix.mat[2][1]) + (mat[1][3]*matrix.mat[3][1]);
    float g = (mat[1][0]*matrix.mat[0][2]) + (mat[1][1]*matrix.mat[1][2]) + (mat[1][2]*matrix.mat[2][2]) + (mat[1][3]*matrix.mat[3][2]);
    float h = (mat[1][0]*matrix.mat[0][3]) + (mat[1][1]*matrix.mat[1][3]) + (mat[1][2]*matrix.mat[2][3]) + (mat[1][3]*matrix.mat[3][3]);

    float i = (mat[2][0]*matrix.mat[0][0]) + (mat[2][1]*matrix.mat[1][0]) + (mat[2][2]*matrix.mat[2][0]) + (mat[2][3]*matrix.mat[3][0]);
    float j = (mat[2][0]*matrix.mat[0][1]) + (mat[2][1]*matrix.mat[1][1]) + (mat[2][2]*matrix.mat[2][1]) + (mat[2][3]*matrix.mat[3][1]);
    float k = (mat[2][0]*matrix.mat[0][2]) + (mat[2][1]*matrix.mat[1][2]) + (mat[2][2]*matrix.mat[2][2]) + (mat[2][3]*matrix.mat[3][2]);
    float l = (mat[2][0]*matrix.mat[0][3]) + (mat[2][1]*matrix.mat[1][3]) + (mat[2][2]*matrix.mat[2][3]) + (mat[2][3]*matrix.mat[3][3]);

    float m = (mat[3][0]*matrix.mat[0][0]) + (mat[3][1]*matrix.mat[1][3]) + (mat[3][2]*matrix.mat[2][0]) + (mat[3][3]*matrix.mat[3][0]);
    float n = (mat[3][0]*matrix.mat[0][1]) + (mat[3][1]*matrix.mat[1][3]) + (mat[3][2]*matrix.mat[2][1]) + (mat[3][3]*matrix.mat[3][1]);
    float o = (mat[3][0]*matrix.mat[0][2]) + (mat[3][1]*matrix.mat[1][3]) + (mat[3][2]*matrix.mat[2][2]) + (mat[3][3]*matrix.mat[3][2]);
    float p = (mat[3][0]*matrix.mat[0][3]) + (mat[3][1]*matrix.mat[1][3]) + (mat[3][2]*matrix.mat[2][3]) + (mat[3][3]*matrix.mat[3][3]);

    return Matrix4D(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p);
}

/**
*�verlagring av *operatorn f�r att kunna multiplicera en matris med en vektor
*/
Vector4D Matrix4D::operator*(const Vector4D &vector)
{
    float x = (mat[0][0]*vector.getX() + mat[0][1]*vector.getY() + mat[0][2]*vector.getZ() + mat[0][3]*vector.getW());
    float y = (mat[1][0]*vector.getX() + mat[1][1]*vector.getY() + mat[1][2]*vector.getZ() + mat[1][3]*vector.getW());
    float z = (mat[2][0]*vector.getX() + mat[2][1]*vector.getY() + mat[2][2]*vector.getZ() + mat[2][3]*vector.getW());
    float w = (mat[3][0]*vector.getX() + mat[3][1]*vector.getY() + mat[3][2]*vector.getZ() + mat[3][3]*vector.getW());


    return Vector4D(x, y, z);

}

/**
*�verlagring av *operatorn f�r att kunna multiplicera en matris med en skal�r
*/
Matrix4D Matrix4D::operator*(const float &w)
{
    float a = mat[0][0]*w;
    float b = mat[0][1]*w;
    float c = mat[0][2]*w;
    float d = mat[0][3]*w;

    float e = mat[1][0]*w;
    float f = mat[1][1]*w;
    float g = mat[1][2]*w;
    float h = mat[1][3]*w;

    float i = mat[2][0]*w;
    float j = mat[2][1]*w;
    float k = mat[2][2]*w;
    float l = mat[2][3]*w;

    float m = mat[3][0]*w;
    float n = mat[3][1]*w;
    float o = mat[3][2]*w;
    float p = mat[3][3]*w;

    return Matrix4D(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
}

Matrix4D Matrix4D::operator+(const Matrix4D &matrix)
{
    float a = mat[0][0] + matrix.mat[0][0];
    float b = mat[0][1] + matrix.mat[0][1];
    float c = mat[0][2] + matrix.mat[0][2];

    float e = mat[1][0] + matrix.mat[1][0];
    float f = mat[1][1] + matrix.mat[1][1];
    float g = mat[1][2] + matrix.mat[1][2];

    float i = mat[2][0] + matrix.mat[2][0];
    float j = mat[2][1] + matrix.mat[2][1];
    float k = mat[2][2] + matrix.mat[2][2];


    return Matrix4D(a,b,c,e,f,g,i,j,k);
}

void Matrix4D::operator=(const Matrix4D &matrix)
{
    mat[0][0] = matrix.mat[0][0];
    mat[0][1] = matrix.mat[0][1];
    mat[0][2] = matrix.mat[0][2];
    mat[0][3] = matrix.mat[0][3];

    mat[1][0] = matrix.mat[1][0];
    mat[1][1] = matrix.mat[1][1];
    mat[1][2] = matrix.mat[1][2];
    mat[1][3] = matrix.mat[1][3];

    mat[2][0] = matrix.mat[2][0];
    mat[2][1] = matrix.mat[2][1];
    mat[2][2] = matrix.mat[2][2];
    mat[2][3] = matrix.mat[2][3];

    mat[3][0] = matrix.mat[3][0];
    mat[3][1] = matrix.mat[3][1];
    mat[3][2] = matrix.mat[3][2];
    mat[3][3] = matrix.mat[3][3];
}

void Matrix4D::gramSchmidtOrto()
{
    Vector4D x1Axis(mat[0][0],mat[0][1], mat[0][2], 0);
    Vector4D y1Axis(mat[1][0],mat[1][1], mat[1][2], 0);
    Vector4D z1Axis(mat[2][0],mat[2][1], mat[2][2], 0);

    Vector4D u1, u2, u3;

    u1 = x1Axis.normalize();
    u2 = (y1Axis-(u1*(y1Axis.dot(u1)))).normalize();
    u3 = (z1Axis-(u1*(z1Axis.dot(u1)))).normalize();
    u3 = u3-(u2*(u3.dot(u2)));
    u3 = u3.normalize();
    u1[3] = 0;
    u2[3] = 0;
    u3[3] = 0;


    mat[0][0] = u1[0];
    mat[0][1] = u1[1];
    mat[0][2] = u1[2];
    mat[0][3] = 0;

    mat[1][0] = u2[0];
    mat[1][1] = u2[1];
    mat[1][2] = u2[2];
    mat[1][3] = 0;

    mat[2][0] = u3[0];
    mat[2][1] = u3[1];
    mat[2][2] = u3[2];
    mat[2][3] = 0;

    mat[3][0] = 0;
    mat[3][1] = 0;
    mat[3][2] = 0;
    mat[3][3] = 1;
}

/**
*�verlagring av []operatorn f�r att enkelt h�mta ut data fr�n matrisen
*/
float* Matrix4D::operator[](int i)
{
    return mat[i];
}

/**
*Funktion f�r att rotera runt X-axeln
*/
Matrix4D Matrix4D::rotateX(float v)
{
    float r = v * (M_PI / 180); //Omvandling fr�n grader till radianer
    float cv = cosf(r);
    float sv = sinf(r);

    return Matrix4D(1, 0, 0, 0, cv, -sv, 0, sv, cv);
}

/**
*Funktion f�r att rotera runt Y-axeln
*/
Matrix4D Matrix4D::rotateY(float v)
{
    float r = v * (M_PI / 180); //Omvandling fr�n grader till radianer
    float cv = cosf(r);
    float sv = sinf(r);

    return Matrix4D(cv, 0, sv, 0, 1, 0, -sv, 0, cv);
}

/**
*Funktion f�r att rotera runt Z-axeln
*/
Matrix4D Matrix4D::rotateZ(float v)
{
    float r = v * (M_PI / 180); //Omvandling fr�n grader till radianer
    float cv = cosf(r);
    float sv = sinf(r);

    return Matrix4D(cv, -sv, 0, sv, cv, 0, 0, 0, 1);
}

/**
*Funktion f�r att rotera runt en vektor
*/
Matrix4D Matrix4D::rotateVec(const Vector4D &vector, float v)
{
    float r = v * (M_PI / 180); //Omvandling fr�n grader till radianer
    float cv = cosf(r);
    float sv = sinf(r);

    float a = ((vector.getX()*vector.getX()) + (1 - (vector.getX()*vector.getX())) * cv);
    float b = ((vector.getX()*vector.getY()) * (1 - cv) - vector.getX()*sv);
    float c = ((vector.getX()*vector.getZ()) * (1 - cv) + vector.getY()*sv);

    float d = ((vector.getX()*vector.getY()) * (1 - cv) + vector.getZ()*sv);
    float e = ((vector.getY()*vector.getY()) + (1 - (vector.getY()*vector.getY())) * cv);
    float f = ((vector.getX()*vector.getZ()) * (1 - cv) - vector.getX()*sv);

    float g = ((vector.getX()*vector.getZ()) * (1 - cv) - vector.getY()*sv);
    float h = ((vector.getY()*vector.getZ()) * (1 - cv) + vector.getX()*sv);
    float i = ((vector.getZ()*vector.getZ()) + (1 - (vector.getZ()*vector.getZ())) * cv);

    return Matrix4D(a, b, c, d, e, f, g, h, i);
}

Matrix4D Matrix4D::ProjectionMat(const float &fov, const float &near, const float &far)
{
    Matrix4D proj;

    float scale = 1 / (tan((fov / 2) * (M_PI / 180)));
    proj[0][0] = scale;
    proj[1][1] = scale;
    proj[2][2] = -(far / (far - near));
    proj[2][3] = -(far * near) / (far - near);
    proj[3][2] = -1;
    proj[3][3] = 0;

    //proj.transpose();

    return proj;
}

Matrix4D Matrix4D::ViewMat(Vector4D eye, Vector4D target, Vector4D up)
{
    Vector4D zAxis = (eye - target).normalize();
    Vector4D xAxis = (up.cross(zAxis)).normalize();
    Vector4D yAxis = (zAxis.cross(xAxis));

    Matrix4D view;
    view[0][0] = xAxis[0];
    view[0][1] = yAxis[0];
    view[0][2] = zAxis[0];
    view[0][3] = -(eye.dot(xAxis));

    view[1][0] = xAxis[1];
    view[1][1] = yAxis[1];
    view[1][2] = zAxis[1];
    view[1][3] = -(eye.dot(yAxis));

    view[2][0] = xAxis[2];
    view[2][1] = yAxis[2];
    view[2][2] = zAxis[2];
    view[2][3] = -(eye.dot(zAxis));

    view[3][0] = 0;
    view[3][1] = 0;
    view[3][2] = 0;
    view[3][3] = 1;

    //view.transpose();

    return view;
}

/**
*Funktion f�r att g�ra transponat av en matris
*/
void Matrix4D::transpose()
{
    float arr[4][4]; //Tempor�r array f�r mellanlagring

    for (int i = 0; i < 4; i++) //For-loopar f�r att transponera matrisen samt flytta �ver den till den tempor�ra arrayen
    {
        for (int j = 0; j < 4; j++)
        {
            arr[i][j] = mat[j][i];

        }
    }

    for (int i = 0; i < 4; i++) //For-loopar f�r att flytta tillbaks den nu transponerade matrisen till det ursprungliga objektet
    {
        for (int j = 0; j < 4; j++)
        {
            mat[i][j] = arr[i][j];
        }
    }
}

/**
*Funktion f�r att ta fram inversen av en matris
*/
Matrix4D Matrix4D::inverse()
{
    //Utr�kning av matrisens determinant
    float det   = mat[0][0]*mat[1][1]*mat[2][2]*mat[3][3] + mat[0][0]*mat[1][2]*mat[2][3]*mat[3][1] + mat[0][0]*mat[1][3]*mat[2][1]*mat[3][2] + mat[0][1]*mat[1][0]*mat[2][3]*mat[3][2]
                + mat[0][1]*mat[1][2]*mat[2][0]*mat[3][3] + mat[0][1]*mat[1][3]*mat[2][2]*mat[3][0] + mat[0][2]*mat[1][0]*mat[2][1]*mat[3][3] + mat[0][2]*mat[1][1]*mat[2][3]*mat[3][0]
                + mat[0][2]*mat[1][3]*mat[2][0]*mat[3][1] + mat[0][3]*mat[1][0]*mat[2][2]*mat[3][1] + mat[0][3]*mat[1][1]*mat[2][0]*mat[3][2] + mat[0][3]*mat[1][2]*mat[2][1]*mat[3][0]

                - mat[0][0]*mat[1][1]*mat[2][3]*mat[3][2] - mat[0][0]*mat[1][2]*mat[2][1]*mat[3][3] - mat[0][0]*mat[1][3]*mat[2][2]*mat[3][1] - mat[0][1]*mat[1][0]*mat[2][2]*mat[3][3]
                - mat[0][1]*mat[1][2]*mat[2][3]*mat[3][0] - mat[0][1]*mat[1][3]*mat[2][0]*mat[3][2] - mat[0][2]*mat[1][0]*mat[2][3]*mat[3][1] - mat[0][2]*mat[1][1]*mat[2][0]*mat[3][3]
                - mat[0][2]*mat[1][3]*mat[2][1]*mat[3][0] - mat[0][3]*mat[1][0]*mat[2][1]*mat[3][2] - mat[0][3]*mat[1][1]*mat[2][2]*mat[3][0] - mat[0][3]*mat[1][2]*mat[2][0]*mat[3][1];

    if(det == 0) //Ifall determinanten �r noll s� finns det ingen invers
    {
        return *this; //Nuvarande objekted returneras
    }

    else //Om determinanten inte �r noll s� r�knas matrisens nya koordinater ut
    {

        float a = (mat[1][1]*mat[2][2]*mat[3][3] + mat[1][2]*mat[2][3]*mat[3][1] + mat[1][3]*mat[2][1]*mat[3][2] - mat[1][1]*mat[2][3]*mat[3][2] - mat[1][2]*mat[2][1]*mat[3][3] - mat[1][3]*mat[2][2]*mat[3][1]);
        float b = (mat[0][1]*mat[2][3]*mat[3][2] + mat[0][2]*mat[2][1]*mat[3][3] + mat[0][3]*mat[2][2]*mat[3][1] - mat[0][1]*mat[2][2]*mat[3][3] - mat[0][2]*mat[2][3]*mat[3][1] - mat[0][3]*mat[2][1]*mat[3][2]);
        float c = (mat[0][1]*mat[1][2]*mat[3][3] + mat[0][2]*mat[1][3]*mat[3][1] + mat[0][3]*mat[1][1]*mat[3][2] - mat[0][1]*mat[1][3]*mat[3][2] - mat[0][2]*mat[1][1]*mat[3][3] - mat[0][3]*mat[1][2]*mat[3][1]);
        float d = (mat[0][1]*mat[1][3]*mat[2][2] + mat[0][2]*mat[1][1]*mat[2][3] + mat[0][3]*mat[1][2]*mat[2][1] - mat[0][1]*mat[1][2]*mat[2][3] - mat[0][2]*mat[1][3]*mat[2][1] - mat[0][3]*mat[1][1]*mat[2][2]);

        float e = (mat[1][0]*mat[2][3]*mat[3][2] + mat[1][2]*mat[2][0]*mat[3][3] + mat[1][3]*mat[2][2]*mat[3][0] - mat[1][0]*mat[2][2]*mat[3][3] - mat[1][2]*mat[2][3]*mat[3][0] - mat[1][3]*mat[2][0]*mat[3][2]);
        float f = (mat[0][0]*mat[2][2]*mat[3][3] + mat[0][2]*mat[2][3]*mat[3][0] + mat[0][3]*mat[2][0]*mat[3][2] - mat[0][0]*mat[2][3]*mat[3][2] - mat[0][2]*mat[2][0]*mat[3][3] - mat[0][3]*mat[2][2]*mat[3][0]);
        float g = (mat[0][0]*mat[1][3]*mat[3][2] + mat[0][2]*mat[1][0]*mat[3][3] + mat[0][3]*mat[1][2]*mat[3][0] - mat[0][0]*mat[1][2]*mat[3][3] - mat[0][2]*mat[1][3]*mat[3][0] - mat[0][3]*mat[1][0]*mat[3][2]);
        float h = (mat[0][0]*mat[1][2]*mat[2][3] + mat[0][2]*mat[1][3]*mat[2][0] + mat[0][3]*mat[1][0]*mat[2][2] - mat[0][0]*mat[1][3]*mat[2][2] - mat[0][2]*mat[1][0]*mat[2][3] - mat[0][3]*mat[1][2]*mat[2][0]);

        float i = (mat[1][0]*mat[2][1]*mat[3][3] + mat[1][1]*mat[2][3]*mat[3][0] + mat[1][3]*mat[2][0]*mat[3][1] - mat[1][0]*mat[2][3]*mat[3][1] - mat[1][1]*mat[2][0]*mat[3][3] - mat[1][3]*mat[2][1]*mat[3][0]);
        float j = (mat[0][0]*mat[2][3]*mat[3][1] + mat[0][1]*mat[2][0]*mat[3][3] + mat[0][3]*mat[2][1]*mat[3][0] - mat[0][0]*mat[2][1]*mat[3][3] - mat[0][1]*mat[2][3]*mat[3][0] - mat[0][3]*mat[2][0]*mat[3][1]);
        float k = (mat[0][0]*mat[1][1]*mat[3][3] + mat[0][1]*mat[1][3]*mat[3][0] + mat[0][3]*mat[1][0]*mat[3][1] - mat[0][0]*mat[1][3]*mat[3][1] - mat[0][1]*mat[1][0]*mat[3][3] - mat[0][3]*mat[1][1]*mat[3][0]);
        float l = (mat[0][0]*mat[1][3]*mat[2][1] + mat[0][1]*mat[1][0]*mat[2][3] + mat[0][3]*mat[1][1]*mat[2][0] - mat[0][0]*mat[1][1]*mat[2][3] - mat[0][1]*mat[1][3]*mat[2][0] - mat[0][3]*mat[1][0]*mat[2][1]);

        float m = (mat[1][0]*mat[2][2]*mat[3][1] + mat[1][1]*mat[2][0]*mat[3][2] + mat[1][2]*mat[2][1]*mat[3][0] - mat[1][0]*mat[2][1]*mat[3][2] - mat[1][1]*mat[2][2]*mat[3][0] - mat[1][2]*mat[2][0]*mat[3][1]);
        float n = (mat[0][0]*mat[2][1]*mat[3][2] + mat[0][1]*mat[2][2]*mat[3][1] + mat[0][2]*mat[2][0]*mat[3][1] - mat[0][0]*mat[2][2]*mat[3][1] - mat[0][1]*mat[2][0]*mat[3][2] - mat[0][2]*mat[2][1]*mat[3][0]);
        float o = (mat[0][0]*mat[1][3]*mat[3][1] + mat[0][1]*mat[1][0]*mat[3][2] + mat[0][2]*mat[1][1]*mat[3][0] - mat[0][0]*mat[1][1]*mat[3][2] - mat[0][1]*mat[1][2]*mat[3][0] - mat[0][2]*mat[1][0]*mat[3][1]);
        float p = (mat[0][0]*mat[1][1]*mat[2][2] + mat[0][1]*mat[1][2]*mat[2][0] + mat[0][2]*mat[1][0]*mat[2][1] - mat[0][0]*mat[1][2]*mat[2][1] - mat[0][1]*mat[1][0]*mat[2][2] - mat[0][2]*mat[1][1]*mat[2][0]);

        Matrix4D temp(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);

        det = 1/det;

        temp = temp*det; //Multiplicerar matrisen med determinanten

        return temp;
    }

}

float* Matrix4D::TransformFrom2DTo1D()
{
    float arr[16];

    arr[0]  = mat[0][0];
    arr[1]  = mat[0][1];
    arr[2]  = mat[0][2];
    arr[3]  = mat[0][3];

    arr[4]  = mat[1][0];
    arr[5]  = mat[1][1];
    arr[6]  = mat[1][2];
    arr[7]  = mat[1][3];

    arr[8]  = mat[2][0];
    arr[9]  = mat[2][1];
    arr[10] = mat[2][2];
    arr[11] = mat[2][3];

    arr[12] = mat[3][0];
    arr[13] = mat[3][1];
    arr[14] = mat[3][2];
    arr[15] = mat[3][3];

    return arr;
}

Matrix4D Matrix4D::QuatToMat(Vector4D q)
{
    float x = q[0]; float y = q[1]; float z = q[2]; float w = q[3];
    Matrix4D ret;
    ret[0][0] = 1 - 2 * y * y - 2 * z * z; ret[1][0] = 2 * x * y + 2 * w * z;     ret[2][0] = 2 * x * z - 2 * w * y;     ret[3][0] = 0;
    ret[0][1] = 2 * x * y - 2 * w * z;     ret[1][1] = 1 - 2 * x * x - 2 * z * z; ret[2][1] = 2 * y * z + 2 * w * x;     ret[3][1] = 0;
    ret[0][2] = 2 * x * z + 2 * w * y;     ret[1][2] = 2 * y * z - 2 * w * x;     ret[2][2] = 1 - 2 * x * x - 2 * y * y; ret[3][2] = 0;
    ret[0][3] = 0;                            ret[1][3] = 0;                           ret[2][3] = 0;                          ret[3][3] = 1;
    return ret;
}

/**
*Getter funktion som g�r samma sak som []operatorn
*/
float Matrix4D::get(int i, int j) const
{
    return mat[i][j];
}

/**
*Setter funktion som s�tter in data i matrisen p� specifierade koordinater
*/
void Matrix4D::set(int i, int j, float x)
{
    mat[i][j] = x;
}

/**
 * Returns the position as a vector from a matrix
 */
Vector4D Matrix4D::getPosition()
{
    return Vector4D(mat[0][3], mat[1][3], mat[2][3]);
}

/**
 * Sets the position in a matrix from a vector
 */
void Matrix4D::setPosition(Vector4D vec)
{
    mat[0][3] = vec[0];
    mat[1][3] = vec[1];
    mat[2][3] = vec[2];
}

void Matrix4D::setScale(Vector4D vec)
{
    mat[0][0] = vec[0];
    mat[1][1] = vec[1];
    mat[2][2] = vec[2];
}

/**
 * ----------------------------------------------------PLANE--------------------------------------------------------------------------------------------
 */

Plane::Plane()
{

}

Plane::Plane(Vector4D normal, Vector4D point)
{
    this->normal = normal;
    this->point = point;
}

Plane::~Plane()
{
}

Vector4D Plane::getNormal()
{
    return normal;
}

Vector4D Plane::getPoint()
{
    return point;
}

/**
 * ----------------------------------------------------RAY---------------------------------------------------------------------------------------------
 */

Ray::Ray()
{
    direction = Vector4D(0.0f, 0.0f, 0.0f);
    startPoint = Vector4D(0.0f, 0.0f, 0.0f);
}

Ray::Ray(Vector4D dir, Vector4D point)
{
    direction = dir;
    startPoint = point;
}

Ray::~Ray()
{

}

bool Ray::intersect(Plane plane, Vector4D &outVec)
{
    if (direction.dot(plane.getNormal()) == 0)
    {
        return false;
    }

    float dist = (plane.getPoint() - this->startPoint).dot(plane.getNormal())/(this->direction.dot(plane.getNormal()));

    outVec = (this->direction * dist) + this->startPoint;
    return true;
}

bool Ray::pointInPlane(Vector4D intersect, Vector4D v0, Vector4D v1, Vector4D v2)
{
    Vector4D c0 = intersect - v0;
    Vector4D dS21 = v1 - v0;
    Vector4D dS31 = v2 - v0;

    Vector4D dS21norm = dS21.normalize();
    Vector4D dS31norm = dS31.normalize();
    float u = dS21norm.dot(c0);
    float v = dS31norm.dot(c0);

    bool b = u >= 0.0f && u <= dS21.length();
    bool o = v >= 0.0f && v <= dS31.length();

    return (b && o);
}

bool Ray::intersectAABB(AABB box, Vector4D &outVec)
{
    float minX = (box.min[0] - startPoint[0]) / direction[0];
    float minY = (box.min[1] - startPoint[1]) / direction[1];
    float minZ = (box.min[2] - startPoint[2]) / direction[2];

    float maxX = (box.max[0] - startPoint[0]) / direction[0];
    float maxY = (box.max[1] - startPoint[1]) / direction[1];
    float maxZ = (box.max[2] - startPoint[2]) / direction[2];

    Vector4D tMin = Vector4D(minX, minY, minZ);
    Vector4D tMax = Vector4D(maxX, maxY, maxZ);

    Vector4D t1 = Vector4D::Min(tMin, tMax);
    Vector4D t2 = Vector4D::Max(tMin, tMax);

    float temp = Vector4D::Max(t1[0], t1[1]);
    float tNear = Vector4D::Max(temp, t1[2]);
    temp = Vector4D::Min(t2[0], t2[1]);
    float tFar = Vector4D::Min(temp, t2[2]);

    if(tNear > 0 && tNear < tFar)
    {

        outVec = this->direction*tNear + this->startPoint;
        return true;
    }
    else
    {
        return false;
    }
}