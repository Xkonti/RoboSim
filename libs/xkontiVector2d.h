#pragma once


//////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////



//////////////////////////////////////////
// VECTOR2D CLASS
//////////////////////////////////////////

class Vector2D {
public:
	// Constructor & Destructor
	Vector2D();
	Vector2D(float _x, float _y);
	~Vector2D();

	// Operators
	inline Vector2D operator = (Vector2D _a);
	inline Vector2D operator + (Vector2D _a);
	inline Vector2D operator - (Vector2D _a);
	inline Vector2D operator * (Vector2D _a);
	inline Vector2D operator * (float _a);
	inline Vector2D operator / (Vector2D _a);
	inline Vector2D operator / (float _a);

	// Functions
	inline Vector2D normal();

	// Procedures
	inline void normal(Vector2D& _vec);

	// Contents
	float x;
	float y;
private:

};