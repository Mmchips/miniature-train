//Copyright of Chips
#include "Vector2D.hpp"
#include "math.h"

Vector2D::Vector2D(float x, float y)
{
	//S�tter in X-, Y- och Z-v�rdena i vektorns array
	arr[0] = x;
	arr[1] = y;
	arr[2] = 1;
}

Vector2D::Vector2D()
{
	//Om inga komponenter angetts s� s�tts X, Y och Z till noll
	arr[0] = 0;
	arr[1] = 0;
	arr[2] = 1;
}

Vector2D::Vector2D(const Vector2D &vector)
{
	//Kopierar ena vektorns v�rden och s�tter in dem i den andra vektorn
	arr[0] = vector.arr[0]; 
	arr[1] = vector.arr[1];
	arr[2] = vector.arr[2];
}

Vector2D::~Vector2D(void)
{//Dekonstruktor som inte g�r ett skit
}

Vector2D Vector2D::operator+(const Vector2D &vector)
{
	float newX = getX() + vector.getX(); //Adderar vektorernas X-v�rden
	float newY = getY() + vector.getY(); //Adderar vektorernas Y-v�rden

	Vector2D summa(newX, newY); //Skapar en ny vektor med de nya v�rdena
	return summa;
}

Vector2D Vector2D::operator-(const Vector2D &vector)
{
	float newX = getX() - vector.getX(); //Subtraherar vektorernas X-v�rden
	float newY = getY() - vector.getY(); //Subtraherar vektorernas Y-v�rden

	Vector2D summa(newX, newY); //Skapar en ny vektor med de nya v�rdena
	return summa;
}

Vector2D Vector2D::operator*(const Vector2D &vector)
{
	float newX = (getX()*vector.getX());
	float newY = (getY()*vector.getY());

	Vector2D summa(newX, newY);
	return summa;
}

Vector2D Vector2D::operator*(const float &i)
{
	float newX = getX()*i;
	float newY = getY()*i;

	Vector2D summa(newX, newY);
	return summa;
}

Vector2D Vector2D::operator/(const Vector2D &vector)
{
	float newX = (getX()/vector.getX());
	float newY = (getY()/vector.getY());

	Vector2D summa(newX, newY);
	return summa;
}

void Vector2D::operator=(const Vector2D &vector)
{
	//G�r samma skit som kopieringskonstruktorn
	arr[0] = vector.arr[0];
	arr[1] = vector.arr[1];
	arr[2] = vector.arr[2];
}

bool Vector2D::operator==(const Vector2D &vector)
{
	return (getX() == vector.getX() && getY() == vector.getY() && getZ() == vector.getZ()); //Returnerar true om b�de X- och Y-v�rdena st�mmer �verens
}

bool Vector2D::operator!=(const Vector2D &vector)
{
	return (getX() != vector.getX() && getY() != vector.getY() && getZ() != vector.getZ()); //Returnerar true om b�de X- och Y-v�rdena inte st�mmer �verens
}

float Vector2D::operator[](int i) const 
{
	return arr[i];
}

float& Vector2D::operator[](int i)
{
	return arr[i];
}

float Vector2D::length()
{
	float x = getX();
	float y = getY();
	float length = sqrt(x*x + y*y + 1.0f); //K�r Pythagoras sats p� vektorn f�r att f� l�ngden
	return length;
}

Vector2D Vector2D::norm()
{
	float div = 1.0f / length();
	float x = getX() * div; //Delar X-v�rdet med l�ngden av vektorn
	float y = getY() * div; //Delar Y-v�rdet med l�ngden av vektorn

	Vector2D summa(x, y); //Skapar en ny vektor med de nya v�rdena
	return summa;
}

float Vector2D::getX() const
{
	return arr[0]; //Returnerar X-v�rdet
}

float Vector2D::getY() const
{
	return arr[1]; //Returnerar Y-v�rdet
}

float Vector2D::getZ() const
{
	return arr[2]; //Returnerar Z-v�rdet
}

void Vector2D::setX(float x)
{
	arr[0] = x; //S�tter X-v�rdet till det som matades in
}

void Vector2D::setY(float y)
{
	arr[1] = y; //S�tter Y-v�rdet till det som matades in
}