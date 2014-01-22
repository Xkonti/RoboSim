#pragma once

// Local debugging switch
#define DEBUG_ROBOT (1)


//////////////////////////////////////////
// INCLUDES & TYPEFEF
//////////////////////////////////////////

#include "robot.h"

typedef std::vector<float> vector;

//////////////////////////////////////////
// ROBOT CONSTRUCTOR/DESTRUCTOR
//////////////////////////////////////////

Robot::Robot() :size{ vector(2, 0) }, pos{ vector(2, 0) }, rotation{ 0 }, leftDistance{ 0 }, leftRotation{ 0 }, maxVelocity{ 0 }, maxAVelocity{ 0 },
headPos{ vector(2, 0) }, headRotation{ 0 }, headRotRange{ vector(2, 0) }, range{ vector(2, 0) }, rangeError{ 0 }, resolution{ 0 } {}
Robot::~Robot() {}


//////////////////////////////////////////
// INITIALIZATION FUNCTIONS
//////////////////////////////////////////

void Robot::initBody(vector _size, vector _pos, float _rotation, float _maxVelocity, float _maxAVelocity) {
	size = _size;
	pos = _pos;
	rotation = _rotation;
	maxVelocity = _maxVelocity;
	maxAVelocity = _maxAVelocity;
}

void Robot::initHead(vector _pos, vector _rotRange, vector _range, float _rangeError, unsigned int _resolution) {
	headPos = _pos;
	headRotRange = _rotRange;
	range = _range;
	rangeError = _rangeError;
	resolution = _resolution;
}


//////////////////////////////////////////
// SET FUNCTIONS
//////////////////////////////////////////

void Robot::setPos(vector _newPos) {
	pos[0] = _newPos[0];
	pos[1] = _newPos[1];
}

void Robot::setPos(float _x, float _y) {
	pos[0] = _x;
	pos[1] = _y;
}