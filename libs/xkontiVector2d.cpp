#pragma once


//////////////////////////////////////////
// INCLUDES & TYPEFEF
//////////////////////////////////////////

#include "xkontiVector2d.h"


//////////////////////////////////////////
// VECTOR2D CONSTRUCTOR/DESTRUCTOR
//////////////////////////////////////////

Vector2D::Vector2D() : x{ 0 }, y{ 0 } {}
Vector2D::Vector2D(float _x, float _y) : x{ _x }, y{ _y } {}
Vector2D::~Vector2D() {}


//////////////////////////////////////////
// OPERATORS
//////////////////////////////////////////

inline Vector2D Vector2D::operator = (Vector2D _a) {
	return Vector2D(_a.x, _a.y);
}

inline Vector2D Vector2D::operator + (Vector2D _a) {
	return Vector2D(x + _a.x, y + _a.y);
}

inline Vector2D Vector2D::operator - (Vector2D _a) {
	return Vector2D(x - _a.x, y - _a.y);
}

inline Vector2D Vector2D::operator * (Vector2D _a) {
	return Vector2D(x * _a.x, y * _a.y);
}

inline Vector2D Vector2D::operator * (float _a) {
	return Vector2D(x * _a, y * _a);
}

inline Vector2D Vector2D::operator / (Vector2D _a) {
	return Vector2D(x / _a.x, y / _a.y);
}

inline Vector2D Vector2D::operator / (float _a) {
	return Vector2D(x / _a, y / _a);
}


//////////////////////////////////////////
// FUNCTIONS
//////////////////////////////////////////

inline Vector2D Vector2D::normal() {
	if (x >= y) return Vector2D(1, y / x);
	else return Vector2D(x / y, 1);
}


//////////////////////////////////////////
// PROCEDURES
//////////////////////////////////////////

inline void Vector2D::normal(Vector2D& _vec) {
	_vec = _vec.normal();
}