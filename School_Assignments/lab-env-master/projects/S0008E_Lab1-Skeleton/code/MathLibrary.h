#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <math.h>

class Vector4D //Klass f�r vektorer
{
public:

	/**
	*Default konstruktor, ifall inga v�rden matas in s� blir vektorn (0,0,0,1)
	*/
	Vector4D() 
	{
		arr[0] = 0.0f;
		arr[1] = 0.0f;
		arr[2] = 0.0f;
		arr[3] = 1.0f;
	}

	/**
	*Konstruktor som k�rs varje g�ng en vektor skapas. Vektorn f�r de v�rden som matas in, (x,y,z,1).
	*/
	Vector4D(float x, float y, float z) 
	{
		arr[0] = x;
		arr[1] = y;
		arr[2] = z;
		arr[3] = 1.0f;
	}

	/**
	*Kopieringskonstruktor
	*/
	Vector4D(const Vector4D &vector) 
	{
		arr[0] = vector.arr[0];
		arr[1] = vector.arr[1];
		arr[2] = vector.arr[2];
		arr[3] = vector.arr[3];
	}

	/**
	*Dekonstruktor som inte g�r n�tt
	*/
	~Vector4D()
	{
	}

	/**
	*�verlagrar +operatorn s� man kan addera vektorer med varandra
	*/
	inline Vector4D operator+(const Vector4D &vector)
	{
		float newX = arr[0] + vector.arr[0];
		float newY = arr[1] + vector.arr[1];
		float newZ = arr[2] + vector.arr[2];

		return Vector4D(newX, newY, newZ);
	}

	/**
	*�verlagrar -operatorn s� man kan subtrahera vektorer med varandra
	*/
	inline Vector4D operator-(const Vector4D &vector)
	{
		float newX = arr[0] - vector.arr[0];
		float newY = arr[1] - vector.arr[1];
		float newZ = arr[2] - vector.arr[2];

		return Vector4D(newX, newY, newZ);
	}

	/**
	*�verlagrar *operatorn s� man kan multiplicera vektorer med en skal�r
	*/
	inline Vector4D operator*(const float &i)
	{
		float newX = arr[0] * i;
		float newY = arr[1] * i;
		float newZ = arr[2] * i;

		return Vector4D(newX, newY, newZ);
	}

	/**
	*�verlagrar *operatorn s� man kan multiplicera vektorer med varandra
	*/
	inline Vector4D operator*(const Vector4D &vector)
	{
		float newX = ((arr[1]*vector.arr[2]) - (arr[2]*vector.arr[1]));
		float newY = ((arr[2]*vector.arr[0]) - (arr[0]*vector.arr[2]));
		float newZ = ((arr[0]*vector.arr[1]) - (arr[1]*vector.arr[0]));

		return Vector4D(newX, newY, newZ);
	}

    inline void operator=(const Vector4D &vector)
    {
        arr[0] = vector.arr[0];
        arr[1] = vector.arr[1];
        arr[2] = vector.arr[2];
        arr[3] = vector.arr[3];
    }

	/**
	*Funktion f�r att f� fram skal�rprodukten av tv� vektorer
	*/
	inline float dot(const Vector4D &vector)
	{
		float sum = arr[0]*vector.arr[0] + arr[1]*vector.arr[1] + arr[2]*vector.arr[2] + getW()*vector.getW();

		return sum;
	}

	/**
	*Funktion f�r att f� fram l�ngden av en vektor
	*/
	inline float length()
	{
		float len = sqrt((arr[0]*arr[0]) + (arr[1]*arr[1]) + (arr[2]*arr[2]));

		return len;
	}

	/**
	*Funktion f�r att normalisera en vektor
	*/
	inline Vector4D norm()
	{
		float len = length();
		float newX = arr[0]/len;
		float newY = arr[1]/len;
		float newZ = arr[2]/len;
		
		return Vector4D(newX, newY, newZ);
	}

	/**
	*�verlagring av []operatorn f�r att enkelt f� ut data ur en vektor
	*/
	inline float& operator[](int i)
	{
		return arr[i];
	}

	/**
	*Funktion som returnerar x-v�rdet i en vektor
	*/
	inline float getX() const
	{
		return arr[0];
	}

	/**
	*Funktion som returnerar y-v�rdet i en vektor
	*/
	inline float getY() const
	{
		return arr[1];
	}

	/**
	*Funktion som returnerar z-v�rdet i en vektor
	*/
	inline float getZ() const
	{
		return arr[2];
	}

	/**
	*Funktion som returnerar w-v�rdet i en vektor
	*/
	inline float getW() const
	{
		return arr[3];
	}

	/**
	*Funktion som s�tter x-v�rdet i en vektor
	*/
	inline void setX(float x)
	{
		arr[0] = x;
	}

	/**
	*Funktion som s�tter y-v�rdet i en vektor
	*/
	inline void setY(float y)
	{
		arr[1] = y;
	}

	/**
	*Funktion som s�tter z-v�rdet i en vektor
	*/
	inline void setZ(float z)
	{
		arr[2] = z;
	}

private:

	/**
	*Array som h�ller 4 floats i en vektor
	*/
	float arr[4]; 

};

class Matrix4D //Klass f�r matriser
{
public:

	/**
	*Default konstruktor som k�rs ifall ingen data matas in och ger en identitetsmatris
	*/
	Matrix4D() 
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
	Matrix4D(float a, float b, float c, float d, float e, float f, float g, float h, float i) 
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
	Matrix4D(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j, float k, float l, float m, float n, float o, float p) 
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
	~Matrix4D() 
	{
	}

	/**
	*�verlagring av *operatorn f�r att kunna multiplicera matriser med varandra
	*/
	inline Matrix4D operator*(const Matrix4D &matrix)
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
	inline Vector4D operator*(const Vector4D &vector)
	{
		float x = (get(0, 0)*vector.getX() + get(0, 1)*vector.getY() + get(0, 2)*vector.getZ() + get(0, 3)*vector.getW());
		float y = (get(1, 0)*vector.getX() + get(1, 1)*vector.getY() + get(1, 2)*vector.getZ() + get(1, 3)*vector.getW());
		float z = (get(2, 0)*vector.getX() + get(2, 1)*vector.getY() + get(2, 2)*vector.getZ() + get(2, 3)*vector.getW());
		float w = (get(3, 0)*vector.getX() + get(3, 1)*vector.getY() + get(3, 2)*vector.getZ() + get(3, 3)*vector.getW());

		if (w == 1.0f) //Check f�r att se om w, den homogena koordinaten i vektorn, �r ett
		{
			return Vector4D(x, y, z);
		}

		else //Ifall w inte �r det s� delas hela vektorn med dens v�rde f�r att w ska bli ett
		{
			x = x/w;
			y = y/w;
			z = z/w;
			w = w/w;

			return Vector4D(x, y, z); 
		}
	}

	/**
	*�verlagring av *operatorn f�r att kunna multiplicera en matris med en skal�r
	*/
	inline Matrix4D operator*(const float &w)
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

    inline void operator=(const Matrix4D &matrix)
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
	*Funktion f�r att rotera runt X-axeln
	*/
	inline Matrix4D rotateX(float v)
	{
		float r = v * (M_PI / 180); //Omvandling fr�n grader till radianer
		float cv = cosf(r);
		float sv = sinf(r);

		return Matrix4D(1, 0, 0, 0, cv, -sv, 0, sv, cv);
	}

	/**
	*Funktion f�r att rotera runt Y-axeln
	*/
	inline Matrix4D rotateY(float v)
	{
		float r = v * (M_PI / 180); //Omvandling fr�n grader till radianer
		float cv = cosf(r);
		float sv = sinf(r);

		return Matrix4D(cv, 0, sv, 0, 1, 0, -sv, 0, cv);
	}

	/**
	*Funktion f�r att rotera runt Z-axeln
	*/
	inline Matrix4D rotateZ(float v)
	{
		float r = v * (M_PI / 180); //Omvandling fr�n grader till radianer
		float cv = cosf(r);
		float sv = sinf(r);

		return Matrix4D(cv, -sv, 0, sv, cv, 0, 0, 0, 1);
	}

	/**
	*Funktion f�r att rotera runt en vektor
	*/
	inline Matrix4D rotateVec(const Vector4D &vector, float v)
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
	inline void transp()
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
	inline Matrix4D inverse()
	{
		//Utr�kning av matrisens determinant
		float det = mat[0][0]*mat[1][1]*mat[2][2]*mat[3][3] + mat[0][0]*mat[1][2]*mat[2][3]*mat[3][1] + mat[0][0]*mat[1][3]*mat[2][1]*mat[3][2] + mat[0][1]*mat[1][0]*mat[2][3]*mat[3][2]
				  + mat[0][1]*mat[1][2]*mat[2][0]*mat[3][3] + mat[0][1]*mat[1][3]*mat[2][2]*mat[3][0] + mat[0][2]*mat[1][0]*mat[2][1]*mat[3][3] + mat[0][2]*mat[1][1]*mat[2][3]*mat[3][0]
				  + mat[0][2]*mat[1][3]*mat[2][0]*mat[3][1] + mat[0][3]*mat[1][0]*mat[2][2]*mat[3][1] + mat[0][3]*mat[1][1]*mat[2][0]*mat[3][2] + mat[0][3]*mat[1][2]*mat[2][1]*mat[3][0]

				  - mat[0][0]*mat[1][1]*mat[2][3]*mat[3][2] - mat[0][0]*mat[1][2]*mat[2][1]*mat[3][3] - mat[0][0]*mat[1][3]*mat[2][2]*mat[3][1] - mat[0][1]*mat[1][0]*mat[2][2]*mat[3][3]
				  - mat[0][1]*mat[1][2]*mat[2][3]*mat[3][0] - mat[0][1]*mat[1][3]*mat[2][0]*mat[3][2] - mat[0][2]*mat[1][0]*mat[2][3]*mat[3][1] - mat[0][2]*mat[1][1]*mat[2][0]*mat[3][3]
				  - mat[0][2]*mat[1][3]*mat[2][1]*mat[3][0] - mat[0][3]*mat[1][0]*mat[2][1]*mat[3][2] - mat[0][3]*mat[1][1]*mat[2][2]*mat[3][0] - mat[0][3]*mat[1][2]*mat[2][0]*mat[3][1];

		if(det == 0) //Ifall determinanten �r noll s� finns det ingen invers
		{
			std::cout << "det = 0" << std::endl;
			return *this; //Nuvarande objekted returneras
		}

		else //Om determinanten inte �r noll s� r�knas matrisens nya koordinater ut 
		{
			std::cout << "det != 0" << std::endl;

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

	/**
	 * Converts quaternion to matrix
	 * @param quaternion in vector format
	 * @return matrix with the rotation of the quaternion
	 */
	inline Matrix4D QuatToMat(Vector4D vec)
	{
		Matrix4D newMat;

		newMat[0][0] = (float)(1 - 2*pow(vec[1], 2) - 2*pow(vec[2], 2));
		newMat[0][1] = (2*vec[0]*vec[1] + 2*vec[3]*vec[2]);
		newMat[0][2] = (2*vec[0]*vec[2] - 2*vec[3]*vec[1]);
		newMat[1][0] = (2*vec[0]*vec[1] - 2*vec[3]*vec[2]);
		newMat[1][1] = (float)(1 - 2*pow(vec[0], 2) - 2*pow(vec[2], 2));
		newMat[1][2] = (2*vec[1]*vec[2] + 2*vec[3]*vec[0]);
		newMat[2][0] = (2*vec[0]*vec[2] + 2*vec[3]*vec[1]);
		newMat[2][1] = (2*vec[1]*vec[2] - 2*vec[3]*vec[0]);
		newMat[2][2] = (float)(1 - 2*pow(vec[0], 2) - 2*pow(vec[1], 2));

		return newMat;

	}

    inline Matrix4D QuatToMat2(Vector4D q)
    {
        float x = q[0]; float y = q[1]; float z = q[2]; float w = q[3];
        Matrix4D ret;
        ret[0][0] = 1 - 2 * y * y - 2 * z * z; ret[1][0] = 2 * x * y + 2 * w * z;     ret[2][0] = 2 * x * z - 2 * w * y;     ret[3][0] = 0;
        ret[0][1] = 2 * x * y - 2 * w * z;     ret[1][1] = 1 - 2 * x * x - 2 * z * z; ret[2][1] = 2 * y * z + 2 * w * x;     ret[3][1] = 0;
        ret[0][2] = 2 * x * z + 2 * w * y;     ret[1][2] = 2 * y * z - 2 * w * x;     ret[2][2] = 1 - 2 * x * x - 2 * y * y; ret[3][2] = 0;
        ret[0][3] = 0;                            ret[1][3] = 0;                           ret[2][3] = 0;                          ret[3][3] = 1;
        return ret;
    }

    inline float* TransformFrom2DTo1D()
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

	/**
	*�verlagring av []operatorn f�r att enkelt h�mta ut data fr�n matrisen
	*/
	inline float* operator[](int i)
	{
		return mat[i];
	}

	/**
	*Getter funktion som g�r samma sak som []operatorn
	*/
	inline float get(int i, int j) const
	{
		return mat[i][j];
	}

	/**
	*Setter funktion som s�tter in data i matrisen p� specifierade koordinater
	*/
	inline void set(int i, int j, float x)
	{
		mat[i][j] = x;
	}

private:

	/**
	*4x4 array som h�ller matrisens data
	*/
	float mat[4][4]; 
};