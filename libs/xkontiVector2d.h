#pragma once


//////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////

#include <math.h>


//////////////////////////////////////////
// GLOBAL CONSTANTS
//////////////////////////////////////////

const float PI = 3.141592653589793238462643383279;


//////////////////////////////////////////
// MISC FUNCTIONS
//////////////////////////////////////////

float radToDeg(float _rad);		// Convert radians to degrees
float degToRad(float _deg);		// Convert degrees to radians


//////////////////////////////////////////
// VECTOR2D CLASS
//////////////////////////////////////////

class Vector2D {
public:
	// Constructor & Destructor
	Vector2D();
	Vector2D(float _rad);
	Vector2D(float _x, float _y);
	~Vector2D();

	// Operators
	Vector2D operator = (Vector2D _a);
	Vector2D operator + (Vector2D _a);
	Vector2D operator - (Vector2D _a);
	Vector2D operator * (Vector2D _a);
	Vector2D operator * (float _a);
	Vector2D operator / (Vector2D _a);
	Vector2D operator / (float _a);

	// Constants
	inline Vector2D forward();

	// Functions
	float rad();		// Returns direction of vector in radians
	float length();	// Returns length of vector
	Vector2D normalized();			// Returns normalized vector
	Vector2D rotated(float _rad);	// Returns rotated vector

	// Procedures
	void normalize();		// Normalizes vector
	void rotate(float _rad);	// Rotate vector

	// Contents
	float x;
	float y;
private:

};