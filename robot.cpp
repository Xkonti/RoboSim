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
headPos{ Vector2D() }, headRotRange{ Vector2D() }, rangeMin{ 0 }, rangeMax{ 0 }, rangeError{ 0 }, resolution{ 0 }, rangeLess{ 0 }, rangeOver{ 0 } {}
Robot::~Robot() {}


//////////////////////////////////////////
// INITIALIZATION FUNCTIONS
//////////////////////////////////////////

void Robot::initBody(Vector2D _size, Vector2D _pos, double _rotation, double _maxVelocity, double _maxAVelocity) {
	size = _size;
	pos = _pos;
	rotation = _rotation;
	maxVelocity = _maxVelocity;
	maxAVelocity = _maxAVelocity;
}

void Robot::initHead(Vector2D _pos, Vector2D _rotRange, double _rangeMin, double _rangeMax, double _rangeError, unsigned int _resolution, double _rangeLess, double _rangeOver) {
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
void Robot::setPos(double _x, double _y) { pos.x = _x; pos.y = _y; }
void Robot::setRotation(double _rad) { rotation = _rad; }


//////////////////////////////////////////
// GET FUNCTIONS
//////////////////////////////////////////

Vector2D Robot::getPos() { return pos; }
Vector2D Robot::getHeadPos() { return pos + headPos; }
double Robot::getRotation() { return rotation; }


//////////////////////////////////////////
// COMMANDS FUNCTIONS
//////////////////////////////////////////

void Robot::move(double _dist) { leftDistance += _dist; }

void Robot::move(double _dist, double _rad) {
	leftDistance += _dist;
	leftRotation += _rad;
}

void Robot::turn(double _rad) { leftRotation += _rad; }


//////////////////////////////////////////
// PERIODICAL FUNCTIONS
//////////////////////////////////////////

void Robot::update(double dt) {

}

void Robot::draw(double dt) {

	// Draw Body
	drawRect(pos, size.x, size.y, rotation);

	// Draw Front indicator
	Vector2D _temp1 = Vector2D(size.x / 2, 0);
	_temp1.rotate(rotation);
	Vector2D _temp2 = Vector2D(size.x / 2.5, 0);
	_temp2.rotate(rotation);
	drawLine(pos + _temp1, pos + _temp2);

	// Draw Head
	drawPolygon(pos+headPos.rotated(rotation), size.x/4, rotation, 6);
}


//////////////////////////////////////////
// BODY FUNCTIONS
//////////////////////////////////////////


//////////////////////////////////////////
// HEAD FUNCTIONS
//////////////////////////////////////////

double Robot::trace(double _rad) {
	Vector2D _dir = Vector2D(rotation);
	_dir.rotate(_rad);
	Vector2D _center = pos + headPos;
	for (double i = 0; i <= rangeMax; i++) {
		Vector2D _point = _center + (_dir * i);
		if (map[int(_point.x)][int(_point.y)]) {
			if (i < rangeMin) return rangeLess;
			else {
				scanPoints.push_back(_point);
				return i;
			}
		}
	}
	return rangeOver;
}