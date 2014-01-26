#pragma once


//////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////

#include <math.h>


//////////////////////////////////////////
// GLOBAL CONSTANTS
//////////////////////////////////////////

const double PI = 3.141592653589793238462643383279;


//////////////////////////////////////////
// MISC FUNCTIONS
//////////////////////////////////////////

double radToDeg(double _rad);		// Convert radians to degrees
double degToRad(double _deg);		// Convert degrees to radians


//////////////////////////////////////////
// VECTOR2D CLASS
//////////////////////////////////////////

class Vector2D {
public:
	// Constructor & Destructor
	Vector2D();
	Vector2D(double _rad);
	Vector2D(double _x, double _y);
	Vector2D(Vector2D _vec1, Vector2D _vec2);
	~Vector2D();

	// Operators
	void operator = (Vector2D _a);
	Vector2D operator + (Vector2D _a);
	Vector2D operator + (double _a);
	Vector2D operator - (Vector2D _a);
	Vector2D operator - (double _a);
	Vector2D operator * (Vector2D _a);
	Vector2D operator * (double _a);
	Vector2D operator / (Vector2D _a);
	Vector2D operator / (double _a);
	bool operator == (Vector2D _right);
	bool operator != (Vector2D _right);

	// Constants
	inline Vector2D forward();

	// Functions
	double rad();		// Returns direction of vector in radians
	double length();	// Returns length of vector
	double distance(Vector2D _vec1, Vector2D _vec2);
	Vector2D normalized();			// Returns normalized vector
	Vector2D rotated(double _rad);	// Returns rotated vector

	// Procedures
	void normalize();		// Normalizes vector
	void rotate(double _rad);	// Rotate vector

	// Contents
	double x;
	double y;
private:

};