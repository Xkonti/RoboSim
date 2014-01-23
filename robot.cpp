#pragma once

// Local debugging switch
#define DEBUG_ROBOT (1)


//////////////////////////////////////////
// INCLUDES & TYPEFEF
//////////////////////////////////////////

#include "robot.h"

//////////////////////////////////////////
// ROBOT CONSTRUCTOR/DESTRUCTOR
//////////////////////////////////////////

Robot::Robot(std::vector< std::vector<bool> >& _map) :map{ _map }, size{ Vector2D() }, pos{ Vector2D() }, rotation{ 0 }, leftDistance{ 0 }, leftRotation{ 0 }, maxVelocity{ 0 }, maxAVelocity{ 0 },
headPos{ Vector2D() }, headRotation{ 0 }, headRotRange{ Vector2D() }, rangeMin{ 0 }, rangeMax{ 0 }, rangeError{ 0 }, resolution{ 0 }, rangeLess{ 0 }, rangeOver{ 0 } {}
Robot::~Robot() {}


//////////////////////////////////////////
// INITIALIZATION FUNCTIONS
//////////////////////////////////////////

void Robot::initBody(Vector2D _size, Vector2D _pos, float _rotation, float _maxVelocity, float _maxAVelocity) {
	size = _size;
	pos = _pos;
	rotation = _rotation;
	maxVelocity = _maxVelocity;
	maxAVelocity = _maxAVelocity;
}

void Robot::initHead(Vector2D _pos, Vector2D _rotRange, float _rangeMin, float _rangeMax, float _rangeError, unsigned int _resolution, float _rangeLess, float _rangeOver) {
	headPos = _pos;
	headRotRange = _rotRange;
	rangeMin = _rangeMin;
	rangeMax = _rangeMax;
	rangeError = _rangeError;
	resolution = _resolution;
	rangeLess = _rangeLess;
	rangeOver = _rangeOver;
}


//////////////////////////////////////////
// SET FUNCTIONS
//////////////////////////////////////////

void Robot::setPos(Vector2D _newPos) { pos = _newPos; }
void Robot::setPos(float _x, float _y) { pos.x = _x; pos.y = _y; }


//////////////////////////////////////////
// GET FUNCTIONS
//////////////////////////////////////////


//////////////////////////////////////////
// BODY FUNCTIONS
//////////////////////////////////////////


//////////////////////////////////////////
// HEAD FUNCTIONS
//////////////////////////////////////////

float Robot::trace(float _rad) {
	Vector2D _dir = Vector2D(rotation);
	_dir.rotate(_rad);
	Vector2D _center = pos + headPos;
	for (float i = 0; i <= rangeMax; i++) {
		Vector2D _point = _center + (_dir * i);
		if (map[int(_point.x)][int(_point.y)]) {
			if (i < rangeMin) return rangeLess;
			else return i;
		}
	}
	return rangeOver;
}


//////////////////////////////////////////
// DRAWING FUNCTIONS
//////////////////////////////////////////