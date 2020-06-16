//Copyright of Chips
#pragma once
class Vector2D //Klass som skapar vektorer och utf�r ber�kningar p� vektorer
{
public:

	Vector2D(); //Konstruktor f�r inga komponenter
	Vector2D(float x, float y); //konstruktor f�r samtliga komponenter
	Vector2D(const Vector2D &vector); //Kopieringskonstruktor
	~Vector2D(void); //Dekonstruktor

	Vector2D operator+(const Vector2D &vector); //�verlagrar +operatorn f�r att kunna addera vektorer med varandra
	Vector2D operator-(const Vector2D &vector); //�verlagrar -operatorn f�r att kunna subtrahera vektorer med varandra
	Vector2D operator*(const Vector2D &vector); //�verlagrar *operatorn f�r att kunna multiplicera vektorer med varandra
	Vector2D operator*(const float &i);
	Vector2D operator/(const Vector2D &vector);
	void operator=(const Vector2D &vector); //�verlagrar =operatorn f�r att kunna tilldela vektorer till andra vektorer
	bool operator==(const Vector2D &vector); //�verlagrar ==operatorn f�r att kunna j�mf�ra vektorer med varandra
	bool operator!=(const Vector2D &vector); //�verlagrar !=operatorn f�r att kunna j�mf�ra vektorer med varandra
	float operator[](int i) const;
	float& operator[](int i);
	Vector2D norm(); //Funktion f�r att kunna g�ra en normalvektor av en vektor
	float length(); //Funktion f�r att kunna f� fram l�ngden av en vektor
	float getX() const; //Funktion f�r att f� fram X-v�rdet hos en vektor
	float getY() const; //Funktion f�r att f� fram Y-v�rdet hos en vektor
	float getZ() const; //Funktion f�r att f� fram Z-v�rdet hos en vektor
	void setX(float x); //Funktion f�r att kunna s�tta X-v�rdet hos en vektor
	void setY(float y); //Funktion f�r att kunna s�tta Y-v�rdet hos en vektor

private:
	float arr[3]; //Array som h�ller X-, och Y-v�rderna �t vektorer
};


