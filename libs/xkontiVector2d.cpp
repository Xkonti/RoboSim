#pragma once


//////////////////////////////////////////
// INCLUDES & TYPEFEF
//////////////////////////////////////////

#include "xkontiVector2d.h"


//////////////////////////////////////////
// MISC FUNCTIONS
//////////////////////////////////////////

float radToDeg(float _rad) {
	return _rad * (180 / PI);
}

float degToRad(float _deg) {
	return _deg / (180 / PI);
}


//////////////////////////////////////////
// VECTOR2D CONSTRUCTOR/DESTRUCTOR
//////////////////////////////////////////

Vector2D::Vector2D() : x{ 0 }, y{ 0 } {}
Vector2D::Vector2D(float _rad) : x{ cos(_rad) }, y{ sin(_rad) } {}
Vector2D::Vector2D(float _x, float _y) : x{ _x }, y{ _y } {}
Vector2D::~Vector2D() {}


//////////////////////////////////////////
// OPERATORS
//////////////////////////////////////////

void Vector2D::operator = (Vector2D _a) {
	this->x = _a.x;
	this->y = _a.y;
}

Vector2D Vector2D::operator + (Vector2D _a) {
	return Vector2D(x + _a.x, y + _a.y);
}

Vector2D Vector2D::operator - (Vector2D _a) {
	return Vector2D(x - _a.x, y - _a.y);
}

Vector2D Vector2D::operator * (Vector2D _a) {
	return Vector2D(x * _a.x, y * _a.y);
}

Vector2D Vector2D::operator * (float _a) {
	return Vector2D(x * _a, y * _a);
}

Vector2D Vector2D::operator / (Vector2D _a) {
	return Vector2D(x / _a.x, y / _a.y);
}

Vector2D Vector2D::operator / (float _a) {
	return Vector2D(x / _a, y / _a);
}


//////////////////////////////////////////
// CONSTANTS
//////////////////////////////////////////

Vector2D Vector2D::forward() { Vector2D(1, 0); }


//////////////////////////////////////////
// FUNCTIONS
//////////////////////////////////////////

float Vector2D::rad() {
	// I quarter
	if (x >= 0 && y >= 0) return atan(y / x);
	else if (x < 0) return PI + atan(y / x);
	else return PI + PI + atan(y / x);
}

float Vector2D::length() {
	return sqrt((x * x) + (y * y));
}

Vector2D Vector2D::normalized() {
	if (x >= y) return Vector2D(1, y / x);
	else return Vector2D(x / y, 1);
}

Vector2D Vector2D::rotated(float _rad) {
	return Vector2D(this->rad() + _rad) * this->length();
}


//////////////////////////////////////////
// PROCEDURES
//////////////////////////////////////////

void Vector2D::normalize() {
	if (x >= y) {
		y /= x;
		x = 1;
	}
	else {
		x /= y;
		y = 1;
	}
}

void Vector2D::rotate(float _rad) {
	float _dir = this->rad() + _rad;
	float _length = this->length();
	x = cos(_dir) * _length;
	y = sin(_dir) * _length;
}