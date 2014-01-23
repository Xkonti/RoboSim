#pragma once


//////////////////////////////////////////
// INCLUDES & TYPEFEF
//////////////////////////////////////////

#include "xkontiVector2d.h"


//////////////////////////////////////////
// MISC FUNCTIONS
//////////////////////////////////////////

double radToDeg(double _rad) {
	return _rad * (180 / PI);
}

double degToRad(double _deg) {
	return _deg / (180 / PI);
}


//////////////////////////////////////////
// VECTOR2D CONSTRUCTOR/DESTRUCTOR
//////////////////////////////////////////

Vector2D::Vector2D() : x{ 0 }, y{ 0 } {}
Vector2D::Vector2D(double _rad) : x{ cos(_rad) }, y{ sin(_rad) } {}
Vector2D::Vector2D(double _x, double _y) : x{ _x }, y{ _y } {}
Vector2D::Vector2D(Vector2D _vec1, Vector2D _vec2) : x{ _vec2.x - _vec1.x }, y{ _vec2.y - _vec1.y } {}
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

Vector2D Vector2D::operator * (double _a) {
	return Vector2D(x * _a, y * _a);
}

Vector2D Vector2D::operator / (Vector2D _a) {
	return Vector2D(x / _a.x, y / _a.y);
}

Vector2D Vector2D::operator / (double _a) {
	return Vector2D(x / _a, y / _a);
}

bool Vector2D::operator == (Vector2D _right) {
	if (x == _right.x && y == _right.y) return true;
	else return false;
}

bool Vector2D::operator != (Vector2D _right) {
	if (x != _right.x || y != _right.y) return true;
	else return false;
}


//////////////////////////////////////////
// CONSTANTS
//////////////////////////////////////////

Vector2D Vector2D::forward() { Vector2D(1, 0); }


//////////////////////////////////////////
// FUNCTIONS
//////////////////////////////////////////

double Vector2D::rad() {
	// I quarter
	if (x >= 0 && y >= 0) return atan(y / x);
	else if (x < 0) return PI + atan(y / x);
	else return PI + PI + atan(y / x);
}

double Vector2D::length() {
	return sqrt((x * x) + (y * y));
}

double Vector2D::distance(Vector2D _vec1, Vector2D _vec2) {
	return (_vec2 - _vec1).length();
}

Vector2D Vector2D::normalized() {
	if (x >= y) return Vector2D(1, y / x);
	else return Vector2D(x / y, 1);
}

Vector2D Vector2D::rotated(double _rad) {
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

void Vector2D::rotate(double _rad) {
	double _dir = this->rad() + _rad;
	double _length = this->length();
	x = cos(_dir) * _length;
	y = sin(_dir) * _length;
}