#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>

class Vector4D //Klass f�r vektorer
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
    inline void operator=(const Vector4D &vector);
    inline float& operator[](int i);

    inline float dot(const Vector4D &vector);
    inline float length();
    inline float length4D();
    inline Vector4D normalize();
    inline Vector4D normalize4D();
    static inline Vector4D lerp(Vector4D &startVec, Vector4D &endVec, float percent);
    static inline Vector4D slerp(Vector4D &startVec, Vector4D &endVec, float percent);

    inline float getX() const;
    inline float getY() const;
    inline float getZ() const;
    inline float getW() const;

    inline void setX(float x);
    inline void setY(float y);
    inline void setZ(float z);
    inline void setW(float w);

private:
	/**
	*Array som h�ller 4 floats i en vektor
	*/
	float arr[4];
};
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
    float newW = arr[3] - vector.arr[3];

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
    float newW = arr[3] * i;

    return Vector4D(newX, newY, newZ, newW);
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

void Vector4D::operator=(const Vector4D &vector)
{
    arr[0] = vector.arr[0];
    arr[1] = vector.arr[1];
    arr[2] = vector.arr[2];
    arr[3] = vector.arr[3];
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
    return arr[0]*vector.arr[0] + arr[1]*vector.arr[1] + arr[2]*vector.arr[2] + arr[3]*vector.arr[3];
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
Vector4D Vector4D::lerp(Vector4D &startVec, Vector4D &endVec, float percent)
{
    float x = (1.0f - percent) * startVec[0] + percent * endVec[0];
    float y = (1.0f - percent) * startVec[1] + percent * endVec[1];
    float z = (1.0f - percent) * startVec[2] + percent * endVec[2];

    return Vector4D(x, y, z, 1);
    //return (startVec + (endVec - startVec)*percent);
}

/**
 * Spherical linear interpolation
 */
Vector4D Vector4D::slerp(Vector4D &startVec, Vector4D &endVec, float percent)
{
    startVec.normalize4D();
    endVec.normalize4D();

    float dot = startVec.dot(endVec);

    const float DOT_THRESHOLD = 0.99999999999995f;
    if(fabs(dot) > DOT_THRESHOLD)
    {
        float x = startVec[0] + percent * (endVec[0] - startVec[0]);
        float y = startVec[1] + percent * (endVec[1] - startVec[1]);
        float z = startVec[2] + percent * (endVec[2] - startVec[2]);
        float w = startVec[3] + percent * (endVec[3] - startVec[3]);

        Vector4D result(x, y, z, w);

        result.normalize4D();
        return result;
    }

    if (dot < 0.0f)
    {
        endVec[0] = -endVec[0];
        endVec[1] = -endVec[1];
        endVec[2] = -endVec[2];
        endVec[3] = -endVec[3];
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

    float theta_0 = acos(dot);
    float theta = theta_0 * percent;

    float x = endVec[0] - startVec[0] * percent;
    float y = endVec[1] - startVec[1] * percent;
    float z = endVec[2] - startVec[2] * percent;
    float w = endVec[3] - startVec[3] * percent;

    Vector4D temp(x, y, z, w);
    temp.normalize4D();

    float cosTheta = cosf(theta);
    float sinTheta = sinf(theta);

    float x1 = startVec[0] * cosTheta + temp[0] * sinTheta;
    float y1 = startVec[1] * cosTheta + temp[1] * sinTheta;
    float z1 = startVec[2] * cosTheta + temp[2] * sinTheta;
    float w1 = startVec[3] * cosTheta + temp[3] * sinTheta;

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

class Matrix4D //Klass f�r matriser
{
public:
    inline Matrix4D();
    inline Matrix4D(float a, float b, float c, float d, float e, float f, float g, float h, float i);
    inline Matrix4D(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p);
    inline Matrix4D(const Matrix4D &matrix);
    inline ~Matrix4D();

    inline Matrix4D operator*(const Matrix4D &matrix);
    inline Vector4D operator*(Vector4D &vector);
    inline Matrix4D operator*(const float &w);
    inline Matrix4D operator+(const Matrix4D &matrix);
    inline void operator=(const Matrix4D &matrix);
    inline float* operator[](int i);

    static inline Matrix4D rotateX(float v);
    static inline Matrix4D rotateY(float v);
    static inline Matrix4D rotateZ(float v);
    static inline Matrix4D rotateVec(const Vector4D &vector, float v);

    inline void transpose();
    inline Matrix4D inverse();
    inline float* TransformFrom2DTo1D();
    inline void TransformFrom2DTo1D(float arr[16]);
    static inline Matrix4D QuatToMat(Vector4D q);
    inline float get(int i, int j) const;
    inline void set(int i, int j, float x);
    inline void setPosition(Vector4D &vector);

private:

	/**
	*4x4 array som h�ller matrisens data
	*/
	float mat[4][4];
};

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

Matrix4D::Matrix4D(const Matrix4D &matrix)
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

Matrix4D::~Matrix4D()
{
}

/**
*�verlagring av *operatorn f�r att kunna multiplicera matriser med varandra
*/
Matrix4D Matrix4D::operator*(const Matrix4D &matrix)
{
    Matrix4D newMat;

    float temp;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                temp += mat[j][k] * matrix.mat[k][i];
            }
            newMat[j][i] = temp;
            temp = 0;
        }
    }
    return newMat;
}

/**
*�verlagring av *operatorn f�r att kunna multiplicera en matris med en vektor
*/
Vector4D Matrix4D::operator*(Vector4D &vector)
{
    Vector4D newVec;

    float temp = 0;

    for (int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            temp += mat[i][j] * vector[j];
        }
        newVec[i] = temp;
        temp = 0;
    }
    return newVec;
}

/**
*�verlagring av *operatorn f�r att kunna multiplicera en matris med en skal�r
*/
Matrix4D Matrix4D::operator*(const float &w)
{
    Matrix4D newMat;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            newMat[i][j] = mat[i][j] * w;
        }
    }
    return newMat;
}

Matrix4D Matrix4D::operator+(const Matrix4D &matrix)
{
    Matrix4D newMat;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            newMat[i][j] = mat[i][j] + matrix.mat[i][j];
        }
    }
    return newMat;
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
    Matrix4D new_object;
    float detA;
    float arr[16];
    try
    {
        //Calculating the determinant of the matrix
        detA = mat[0][0] * mat[1][1] * mat[2][2] * mat[3][3] + mat[0][0] * mat[1][2] * mat[2][3] * mat[3][1] + mat[0][0] * mat[1][3] * mat[2][1] * mat[3][2]
               + mat[0][1] * mat[1][0] * mat[2][3] * mat[3][2] + mat[0][1] * mat[1][2] * mat[2][0] * mat[3][3] + mat[0][1] * mat[1][3] * mat[2][2] * mat[3][0]
               + mat[0][2] * mat[1][0] * mat[2][1] * mat[3][3] + mat[0][2] * mat[1][1] * mat[2][3] * mat[3][0] + mat[0][2] * mat[1][3] * mat[2][0] * mat[3][1]
               + mat[0][3] * mat[1][0] * mat[2][2] * mat[3][1] + mat[0][3] * mat[1][1] * mat[2][0] * mat[3][2] + mat[0][3] * mat[1][2] * mat[2][1] * mat[3][0]
               - mat[0][0] * mat[1][1] * mat[2][3] * mat[3][2] - mat[0][0] * mat[1][2] * mat[2][1] * mat[3][3] - mat[0][0] * mat[1][3] * mat[2][2] * mat[3][1]
               - mat[0][1] * mat[1][0] * mat[2][2] * mat[3][3] - mat[0][1] * mat[1][2] * mat[2][3] * mat[3][0] - mat[0][1] * mat[1][3] * mat[2][0] * mat[3][2]
               - mat[0][2] * mat[1][0] * mat[2][3] * mat[3][1] - mat[0][2] * mat[1][1] * mat[2][0] * mat[3][3] - mat[0][2] * mat[1][3] * mat[2][1] * mat[3][0]
               - mat[0][3] * mat[1][0] * mat[2][1] * mat[3][2] - mat[0][3] * mat[1][1] * mat[2][2] * mat[3][0] - mat[0][3] * mat[1][2] * mat[2][0] * mat[3][1];

        //If the determinant is equal to 0, there exist no inverse of the matrix
        if (detA != 0)
        {
            arr[0]  = mat[1][1] * mat[2][2] * mat[3][3] + mat[1][2] * mat[2][3] * mat[3][1] + mat[1][3] * mat[2][1] * mat[3][2] - mat[1][1] * mat[2][3] * mat[3][2] - mat[1][2] * mat[2][1] * mat[3][3] - mat[1][3] * mat[2][2] * mat[3][1];
            arr[1]  = mat[0][1] * mat[2][3] * mat[3][2] + mat[0][2] * mat[2][1] * mat[3][3] + mat[0][3] * mat[2][2] * mat[3][1] - mat[0][1] * mat[2][2] * mat[3][3] - mat[0][2] * mat[2][3] * mat[3][1] - mat[0][3] * mat[2][1] * mat[3][2];
            arr[2]  = mat[0][1] * mat[1][2] * mat[3][3] + mat[0][2] * mat[1][3] * mat[3][1] + mat[0][3] * mat[1][1] * mat[3][2] - mat[0][1] * mat[1][3] * mat[3][2] - mat[0][2] * mat[1][1] * mat[3][3] - mat[0][3] * mat[1][2] * mat[3][1];
            arr[3]  = mat[0][1] * mat[1][3] * mat[2][2] + mat[0][2] * mat[1][1] * mat[2][3] + mat[0][3] * mat[1][2] * mat[2][1] - mat[0][1] * mat[1][2] * mat[2][3] - mat[0][2] * mat[1][3] * mat[2][1] - mat[0][3] * mat[1][1] * mat[2][2];

            arr[4]  = mat[1][0] * mat[2][3] * mat[3][2] + mat[1][2] * mat[2][0] * mat[3][3] + mat[1][3] * mat[2][2] * mat[3][0] - mat[1][0] * mat[2][2] * mat[3][3] - mat[1][2] * mat[2][3] * mat[3][0] - mat[1][3] * mat[2][0] * mat[3][2];
            arr[5]  = mat[0][0] * mat[2][2] * mat[3][3] + mat[0][2] * mat[2][3] * mat[3][0] + mat[0][3] * mat[2][0] * mat[3][2] - mat[0][0] * mat[2][3] * mat[3][2] - mat[0][2] * mat[2][0] * mat[3][3] - mat[0][3] * mat[2][2] * mat[3][0];
            arr[6]  = mat[0][0] * mat[1][3] * mat[3][2] + mat[0][2] * mat[1][0] * mat[3][3] + mat[0][3] * mat[1][2] * mat[3][0] - mat[0][0] * mat[1][2] * mat[3][3] - mat[0][2] * mat[1][3] * mat[3][0] - mat[0][3] * mat[1][0] * mat[3][2];
            arr[7]  = mat[0][0] * mat[1][2] * mat[2][3] + mat[0][2] * mat[1][3] * mat[2][0] + mat[0][3] * mat[1][0] * mat[2][2] - mat[0][0] * mat[1][3] * mat[2][2] - mat[0][2] * mat[1][0] * mat[2][3] - mat[0][3] * mat[1][2] * mat[2][0];

            arr[8]  = mat[1][0] * mat[2][1] * mat[3][3] + mat[1][1] * mat[2][3] * mat[3][0] + mat[1][3] * mat[2][0] * mat[3][1] - mat[1][0] * mat[2][3] * mat[3][1] - mat[1][1] * mat[2][0] * mat[3][3] - mat[1][3] * mat[2][1] * mat[3][0];
            arr[9]  = mat[0][0] * mat[2][3] * mat[3][1] + mat[0][1] * mat[2][0] * mat[3][3] + mat[0][3] * mat[2][1] * mat[3][0] - mat[0][0] * mat[2][1] * mat[3][3] - mat[0][1] * mat[2][3] * mat[3][0] - mat[0][3] * mat[2][0] * mat[3][1];
            arr[10] = mat[0][0] * mat[1][1] * mat[3][3] + mat[0][1] * mat[1][3] * mat[3][0] + mat[0][3] * mat[1][0] * mat[3][1] - mat[0][0] * mat[1][3] * mat[3][1] - mat[0][1] * mat[1][0] * mat[3][3] - mat[0][3] * mat[1][1] * mat[3][0];
            arr[11] = mat[0][0] * mat[1][3] * mat[2][1] + mat[0][1] * mat[1][0] * mat[2][3] + mat[0][3] * mat[1][1] * mat[2][0] - mat[0][0] * mat[1][1] * mat[2][3] - mat[0][1] * mat[1][3] * mat[2][0] - mat[0][3] * mat[1][0] * mat[2][1];

            arr[12] = mat[1][0] * mat[2][2] * mat[3][1] + mat[1][1] * mat[2][0] * mat[3][2] + mat[1][2] * mat[2][1] * mat[3][0] - mat[1][0] * mat[2][1] * mat[3][2] - mat[1][1] * mat[2][2] * mat[3][0] - mat[1][2] * mat[2][0] * mat[3][1];
            arr[13] = mat[0][0] * mat[2][1] * mat[3][2] + mat[0][1] * mat[2][2] * mat[3][0] + mat[0][2] * mat[2][0] * mat[3][1] - mat[0][0] * mat[2][2] * mat[3][1] - mat[0][1] * mat[2][0] * mat[3][2] - mat[0][2] * mat[2][1] * mat[3][0];
            arr[14] = mat[0][0] * mat[1][2] * mat[3][1] + mat[0][1] * mat[1][0] * mat[3][2] + mat[0][2] * mat[1][1] * mat[3][0] - mat[0][0] * mat[1][1] * mat[3][2] - mat[0][1] * mat[1][2] * mat[3][0] - mat[0][2] * mat[1][0] * mat[3][1];
            arr[15] = mat[0][0] * mat[1][1] * mat[2][2] + mat[0][1] * mat[1][2] * mat[2][0] + mat[0][2] * mat[1][0] * mat[2][1] - mat[0][0] * mat[1][2] * mat[2][1] - mat[0][1] * mat[1][0] * mat[2][2] - mat[0][2] * mat[1][1] * mat[2][0];

            detA = 1.0f / detA;
            int i = 0;
            for (int r = 0; r < 4;r++)
            {
                for (int k = 0; k < 4;k++)
                {
                    new_object[r][k] = detA*arr[i];
                    i++;
                }
            }
            return new_object;

        }
        throw detA;
    }

    catch (float det)
    {
        std::cout << "There exist no inverse for the matrix";
    }
//    //Utr�kning av matrisens determinant
//    float det   = mat[0][0]*mat[1][1]*mat[2][2]*mat[3][3] + mat[0][0]*mat[1][2]*mat[2][3]*mat[3][1] + mat[0][0]*mat[1][3]*mat[2][1]*mat[3][2] + mat[0][1]*mat[1][0]*mat[2][3]*mat[3][2]
//                + mat[0][1]*mat[1][2]*mat[2][0]*mat[3][3] + mat[0][1]*mat[1][3]*mat[2][2]*mat[3][0] + mat[0][2]*mat[1][0]*mat[2][1]*mat[3][3] + mat[0][2]*mat[1][1]*mat[2][3]*mat[3][0]
//                + mat[0][2]*mat[1][3]*mat[2][0]*mat[3][1] + mat[0][3]*mat[1][0]*mat[2][2]*mat[3][1] + mat[0][3]*mat[1][1]*mat[2][0]*mat[3][2] + mat[0][3]*mat[1][2]*mat[2][1]*mat[3][0]
//
//                - mat[0][0]*mat[1][1]*mat[2][3]*mat[3][2] - mat[0][0]*mat[1][2]*mat[2][1]*mat[3][3] - mat[0][0]*mat[1][3]*mat[2][2]*mat[3][1] - mat[0][1]*mat[1][0]*mat[2][2]*mat[3][3]
//                - mat[0][1]*mat[1][2]*mat[2][3]*mat[3][0] - mat[0][1]*mat[1][3]*mat[2][0]*mat[3][2] - mat[0][2]*mat[1][0]*mat[2][3]*mat[3][1] - mat[0][2]*mat[1][1]*mat[2][0]*mat[3][3]
//                - mat[0][2]*mat[1][3]*mat[2][1]*mat[3][0] - mat[0][3]*mat[1][0]*mat[2][1]*mat[3][2] - mat[0][3]*mat[1][1]*mat[2][2]*mat[3][0] - mat[0][3]*mat[1][2]*mat[2][0]*mat[3][1];
//
//    if(det == 0) //Ifall determinanten �r noll s� finns det ingen invers
//    {
//        return *this; //Nuvarande objekted returneras
//    }
//
//    else //Om determinanten inte �r noll s� r�knas matrisens nya koordinater ut
//    {
//        float a = (mat[1][1]*mat[2][2]*mat[3][3] + mat[1][2]*mat[2][3]*mat[3][1] + mat[1][3]*mat[2][1]*mat[3][2] - mat[1][1]*mat[2][3]*mat[3][2] - mat[1][2]*mat[2][1]*mat[3][3] - mat[1][3]*mat[2][2]*mat[3][1]);
//        float b = (mat[0][1]*mat[2][3]*mat[3][2] + mat[0][2]*mat[2][1]*mat[3][3] + mat[0][3]*mat[2][2]*mat[3][1] - mat[0][1]*mat[2][2]*mat[3][3] - mat[0][2]*mat[2][3]*mat[3][1] - mat[0][3]*mat[2][1]*mat[3][2]);
//        float c = (mat[0][1]*mat[1][2]*mat[3][3] + mat[0][2]*mat[1][3]*mat[3][1] + mat[0][3]*mat[1][1]*mat[3][2] - mat[0][1]*mat[1][3]*mat[3][2] - mat[0][2]*mat[1][1]*mat[3][3] - mat[0][3]*mat[1][2]*mat[3][1]);
//        float d = (mat[0][1]*mat[1][3]*mat[2][2] + mat[0][2]*mat[1][1]*mat[2][3] + mat[0][3]*mat[1][2]*mat[2][1] - mat[0][1]*mat[1][2]*mat[2][3] - mat[0][2]*mat[1][3]*mat[2][1] - mat[0][3]*mat[1][1]*mat[2][2]);
//
//        float e = (mat[1][0]*mat[2][3]*mat[3][2] + mat[1][2]*mat[2][0]*mat[3][3] + mat[1][3]*mat[2][2]*mat[3][0] - mat[1][0]*mat[2][2]*mat[3][3] - mat[1][2]*mat[2][3]*mat[3][0] - mat[1][3]*mat[2][0]*mat[3][2]);
//        float f = (mat[0][0]*mat[2][2]*mat[3][3] + mat[0][2]*mat[2][3]*mat[3][0] + mat[0][3]*mat[2][0]*mat[3][2] - mat[0][0]*mat[2][3]*mat[3][2] - mat[0][2]*mat[2][0]*mat[3][3] - mat[0][3]*mat[2][2]*mat[3][0]);
//        float g = (mat[0][0]*mat[1][3]*mat[3][2] + mat[0][2]*mat[1][0]*mat[3][3] + mat[0][3]*mat[1][2]*mat[3][0] - mat[0][0]*mat[1][2]*mat[3][3] - mat[0][2]*mat[1][3]*mat[3][0] - mat[0][3]*mat[1][0]*mat[3][2]);
//        float h = (mat[0][0]*mat[1][2]*mat[2][3] + mat[0][2]*mat[1][3]*mat[2][0] + mat[0][3]*mat[1][0]*mat[2][2] - mat[0][0]*mat[1][3]*mat[2][2] - mat[0][2]*mat[1][0]*mat[2][3] - mat[0][3]*mat[1][2]*mat[2][0]);
//
//        float i = (mat[1][0]*mat[2][1]*mat[3][3] + mat[1][1]*mat[2][3]*mat[3][0] + mat[1][3]*mat[2][0]*mat[3][1] - mat[1][0]*mat[2][3]*mat[3][1] - mat[1][1]*mat[2][0]*mat[3][3] - mat[1][3]*mat[2][1]*mat[3][0]);
//        float j = (mat[0][0]*mat[2][3]*mat[3][1] + mat[0][1]*mat[2][0]*mat[3][3] + mat[0][3]*mat[2][1]*mat[3][0] - mat[0][0]*mat[2][1]*mat[3][3] - mat[0][1]*mat[2][3]*mat[3][0] - mat[0][3]*mat[2][0]*mat[3][1]);
//        float k = (mat[0][0]*mat[1][1]*mat[3][3] + mat[0][1]*mat[1][3]*mat[3][0] + mat[0][3]*mat[1][0]*mat[3][1] - mat[0][0]*mat[1][3]*mat[3][1] - mat[0][1]*mat[1][0]*mat[3][3] - mat[0][3]*mat[1][1]*mat[3][0]);
//        float l = (mat[0][0]*mat[1][3]*mat[2][1] + mat[0][1]*mat[1][0]*mat[2][3] + mat[0][3]*mat[1][1]*mat[2][0] - mat[0][0]*mat[1][1]*mat[2][3] - mat[0][1]*mat[1][3]*mat[2][0] - mat[0][3]*mat[1][0]*mat[2][1]);
//
//        float m = (mat[1][0]*mat[2][2]*mat[3][1] + mat[1][1]*mat[2][0]*mat[3][2] + mat[1][2]*mat[2][1]*mat[3][0] - mat[1][0]*mat[2][1]*mat[3][2] - mat[1][1]*mat[2][2]*mat[3][0] - mat[1][2]*mat[2][0]*mat[3][1]);
//        float n = (mat[0][0]*mat[2][1]*mat[3][2] + mat[0][1]*mat[2][2]*mat[3][1] + mat[0][2]*mat[2][0]*mat[3][1] - mat[0][0]*mat[2][2]*mat[3][1] - mat[0][1]*mat[2][0]*mat[3][2] - mat[0][2]*mat[2][1]*mat[3][0]);
//        float o = (mat[0][0]*mat[1][3]*mat[3][1] + mat[0][1]*mat[1][0]*mat[3][2] + mat[0][2]*mat[1][1]*mat[3][0] - mat[0][0]*mat[1][1]*mat[3][2] - mat[0][1]*mat[1][2]*mat[3][0] - mat[0][2]*mat[1][0]*mat[3][1]);
//        float p = (mat[0][0]*mat[1][1]*mat[2][2] + mat[0][1]*mat[1][2]*mat[2][0] + mat[0][2]*mat[1][0]*mat[2][1] - mat[0][0]*mat[1][2]*mat[2][1] - mat[0][1]*mat[1][0]*mat[2][2] - mat[0][2]*mat[1][1]*mat[2][0]);
//
//        Matrix4D temp(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p);
//
//        det = 1/det;
//
//        temp = temp*det; //Multiplicerar matrisen med determinanten
//
//        return temp;
//    }
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

void Matrix4D::TransformFrom2DTo1D(float arr[16])
{
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
}

Matrix4D Matrix4D::QuatToMat(Vector4D q)
{
    float x = q[0];
    float y = q[1];
    float z = q[2];
    float w = q[3];

    Matrix4D ret;
//    ret[0][0] = 1 - 2 * y * y - 2 * z * z; ret[1][0] = 2 * x * y + 2 * w * z;     ret[2][0] = 2 * x * z - 2 * w * y;     ret[3][0] = 0;
//    ret[0][1] = 2 * x * y - 2 * w * z;     ret[1][1] = 1 - 2 * x * x - 2 * z * z; ret[2][1] = 2 * y * z + 2 * w * x;     ret[3][1] = 0;
//    ret[0][2] = 2 * x * z + 2 * w * y;     ret[1][2] = 2 * y * z - 2 * w * x;     ret[2][2] = 1 - 2 * x * x - 2 * y * y; ret[3][2] = 0;
//    ret[0][3] = 0;                            ret[1][3] = 0;                           ret[2][3] = 0;                          ret[3][3] = 1;

    ret[0][0] = 1 - (2 * (y * y)) - (2 * (z*z)); //<< 1 - 2y*y - 2z*z
    ret[0][1] = 2 * (x*y) + 2 * (w*z); //<< 2x*y + 2*w*z
    ret[0][2] = 2 * (x*z) - 2 * (w*y); //<< 2*x*z - 2*w*y

    ret[1][0] = 2 * (x*y) - 2 * (w*z); //<< 2*x*y - 2*w*z
    ret[1][1] = 1 - 2 * (x*x) - 2 * (z*z); //<< 1 - 2*x*x - 2*z*z
    ret[1][2] = 2 * (y*z) + 2 * (w*x); //<< 2*y*z + 2*w*x

    ret[2][0] = 2 * (x*z) + 2 * (w*y); //<< 2*x*z + 2*w*y
    ret[2][1] = 2 * (y*z) - 2 * (w*x); //<< 2*y*z - 2*w*x
    ret[2][2] = 1 - 2 * (x*x) - 2 * (y*y); //<< 1 - 2*x*x - 2*y*y
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

void Matrix4D::setPosition(Vector4D &vector)
{
    mat[0][3] = vector[0];
    mat[1][3] = vector[1];
    mat[2][3] = vector[2];
}