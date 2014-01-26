#pragma once

// Local debugging switch
#define DEBUG_ROBOT (0)


//////////////////////////////////////////
// INCLUDES & TYPEFEF
//////////////////////////////////////////

#include "robot.h"

//////////////////////////////////////////
// ROBOT CONSTRUCTOR/DESTRUCTOR
//////////////////////////////////////////

Robot::Robot(std::vector< std::vector<bool> >& _map, std::vector<Vector2D>& _scanPoints) :map{ _map }, scanPoints{ _scanPoints }, size{ Vector2D() }, pos{ Vector2D() }, rotation{ 0 }, leftDistance{ 0 }, leftRotation{ 0 }, maxVelocity{ 0 }, maxAVelocity{ 0 },
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

void Robot::setResolution(unsigned int _res) { resolution = _res; }
void Robot::setHeadRotRange(Vector2D _rotRange) { headRotRange = _rotRange; }
void Robot::setMinRange(double _range) { rangeMin = _range; }
void Robot::setMaxRange(double _range) { rangeMax = _range; }
void Robot::setRangeOver(double _range) { rangeOver = _range; }
void Robot::setRangeLess(double _range) { rangeLess = _range; }


//////////////////////////////////////////
// GET FUNCTIONS
//////////////////////////////////////////

Vector2D Robot::getPos() { return pos; }
Vector2D Robot::getHeadPos() { return pos + headPos; }
double Robot::getRotation() { return rotation; }
Vector2D Robot::getSize() { return size; }
unsigned int Robot::getResolution() { return resolution; }
double Robot::getHeadStep() { return (abs(headRotRange.x) + abs(headRotRange.y)) / (resolution - 1); }
Vector2D Robot::getHeadRotRange() { return headRotRange; }
double Robot::getMaxRange() { return rangeMax; }
double Robot::getMinRange() { return rangeMin; }
double Robot::getRangeLess() { return rangeLess; }
double Robot::getRangeOver() { return rangeOver; }
double Robot::getMaxVelocity() { return maxVelocity; }
double Robot::getMaxAVelocity() { return maxAVelocity; }

double Robot::getIdealStep(double _distance) { return atan(size.x / 2 / _distance); }

bool Robot::isBusy() {
	if (leftDistance == 0 && leftRotation == 0) return false;
	else return true;
}


//////////////////////////////////////////
// COMMANDS FUNCTIONS
//////////////////////////////////////////

void Robot::move(double _dist) { leftDistance += _dist; }

void Robot::move(double _dist, double _rad) {
	leftDistance += _dist;
	leftRotation += _rad;
}

void Robot::turn(double _rad) {
	leftRotation += _rad; }

std::vector<double> Robot::scan() {
	if (scanPoints.size() > resolution * 5) scanPoints.clear();

	std::vector<double> _data;
	double _step = (abs(headRotRange.x) + abs(headRotRange.y)) / (resolution - 1);
	for (unsigned int i = 0; i < resolution; i++) {
		_data.push_back(this->trace(headRotRange.x + (_step * i)));
	}
	return _data;
}


//////////////////////////////////////////
// PERIODICAL FUNCTIONS
//////////////////////////////////////////

void Robot::update(double dt) {

	// Applying Rotation
	if (leftRotation > 0) {
		if (leftRotation > maxAVelocity * dt) {
			rotation += maxAVelocity * dt;
			leftRotation -= maxAVelocity * dt;
		}
		else {
			rotation += leftRotation * dt;
			leftRotation = 0;
		}
	}
	else if (leftRotation < 0) {
		if (leftRotation < -maxAVelocity * dt) {
			rotation -= maxAVelocity * dt;
			leftRotation += maxAVelocity * dt;
		}
		else {
			rotation += leftRotation * dt;
			leftRotation = 0;
		}
	}

	// Applying Position
	if (leftRotation == 0) {
		if (leftDistance > 0) {
			if (leftDistance > maxVelocity * dt) {
				pos = pos + (Vector2D(rotation) * maxVelocity * dt);
				leftDistance -= maxVelocity * dt;
			}
			else {
				pos = pos + (Vector2D(rotation) * leftDistance * dt);
				leftDistance = 0;
			}
		}
		else if (leftDistance < 0) {
			if (leftDistance < -maxVelocity * dt) {
				pos = pos - (Vector2D(rotation) * maxVelocity * dt);
				leftDistance += maxVelocity * dt;
			}
			else {
				pos = pos + (Vector2D(rotation) * leftDistance * dt);
				leftDistance = 0;
			}
		}
	}
}

void Robot::draw(double dt, bool _drawSight) {

	// Draw Body
	drawRect(pos, size.x, size.y, rotation);

	// Draw Front indicator
	Vector2D _temp1 = Vector2D(size.x / 2, 0);
	_temp1.rotate(rotation);
	Vector2D _temp2 = Vector2D(size.x / 2.5, 0);
	_temp2.rotate(rotation);
	drawLine(pos + _temp1, pos + _temp2);

	// Draw Head
	Vector2D _head = pos + headPos.rotated(rotation);
	drawPolygon(_head, size.x/4, rotation+PI, 3);

	// Draw Robot Sight Rays
	if (_drawSight) {
		double _step = this->getHeadStep();
		for (unsigned int i = 0; i < resolution; i++) {
			drawLine(_head + (Vector2D(rotation + headRotRange.x + (_step*i)) * rangeMin), _head + (Vector2D(rotation + headRotRange.x + (_step*i)) * rangeMax));
		}
	}
}


//////////////////////////////////////////
// BODY FUNCTIONS
//////////////////////////////////////////


//////////////////////////////////////////
// HEAD FUNCTIONS
//////////////////////////////////////////

double Robot::trace(double _rad) {
	// _dir is direction of ray
	Vector2D _dir = Vector2D(rotation);		
	_dir.rotate(_rad);

	Vector2D _center = pos + headPos;	// Starting position of tracing

	// Error computing
	double _error = 0;							// Variable used thile computing range error
	int _rand = (rand() % 1000) - 500;			// Random number ( -500..499 )
	_error = _rand;								// Int -> Double
	_error /= 1000;								// Error multipiler
	_error = rangeMax * (rangeError * _error);	// Actual range error

	// Trace
	for (double i = 0; i <= rangeMax; i++) {

		Vector2D _point = _center + (_dir * i);		// Point of tracing

		// If there is obstacle in point position
		if (map[int(_point.x)][int(_point.y)]) {
			// If its less than minimal range
			if (i + _error < rangeMin) return rangeLess;
			
			// If its in range of trace
			else {
				scanPoints.push_back(_center + (_dir * (i + _error)));	// Add point (with error) to the points vector
				return i + _error;							// Return trace distance (with error)
			}
		}
	}
	scanPoints.push_back(_center + (_dir * (rangeOver + _error)));
	return rangeOver + _error;
}