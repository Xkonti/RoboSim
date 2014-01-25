#pragma once

// Local debugging switch
#define DEBUG_LOGIC (1)


//////////////////////////////////////////
// INCLUDES & TYPEFEF
//////////////////////////////////////////

#include "logic.h"

//////////////////////////////////////////
// LOGIC CONSTRUCTOR/DESTRUCTOR
//////////////////////////////////////////
																					   // TEMP //
Logic::Logic(XkontiConsoleColors& _con, Robot& _robot) : con{ _con }, robot{ _robot }, frame{ 0 }, stepVelocity{ 0 } {}
Logic::~Logic() {}

bool Logic::init() {
	stepVelocity = 15;

	robot.initBody(
	//	Size				Position
		Vector2D(10, 9),	Vector2D(400, 100),

	//	Rot.	MaxVel.		Max Angular Velocity
		0,		90,			degToRad(120));

	robot.initHead(
	//	Position			Rotation Range
		Vector2D(2, 0),		Vector2D(-PI / 2, PI / 2),
		
	//	MinRange	MaxRange
		10,			300,
		
	//	ErrorRange	Resolution
		0.05,		30,
		
	//	RangeLess	RangeOver
		0,			320);
	return true;
}

std::vector<double> Logic::scan() {
	return robot.scan();
}

Vector2D Logic::computeMovement(std::vector<double> _scan) {
	double _rotation = computeRotation(_scan);		// Compute rotation angle
	double _distance = computeVelocity(_scan);		// Compute velocity ( 0..1 )

	_distance *= stepVelocity;

	return Vector2D(_distance, _rotation);
}

double Logic::computeRotation(std::vector<double>& _scan) {
	
	double _centerAng = (robot.getHeadRotRange().x + robot.getHeadRotRange().y) / 2;	// Center angle of head rotation range
	double _step = robot.getHeadStep();		// Angle between 2 scan values
	double _over = robot.getRangeOver();	// Get max value provided by scan data
	double _offset = _scan.size() / 2;		// Center of scan data

	double _rotation = 0;					// Rotation - returned in Vector2D.y
	double _min = 0.5;						// Weight of data on min and max angle
	double _temp = 0;						// Variable used in computing

	// Computing rotation
	for (unsigned int i = 0; i < _scan.size(); i++) {
		_temp = (i - _offset) * _step;	// Get angle of scan[i]
		_temp *= _scan[i] / _over;		// Multiply by value of scan[i] in range of 0..1
		_temp *= computeLinearMultipiler(_min, _scan.size(), i);	// Multiply by weight of _scan[i] (according to its angle)
		_rotation += _centerAng + _temp;	// Add assembled angle
	}

	// Make _rotation the average of all angles
	_rotation /= _scan.size();		

	return _rotation;
}

double Logic::computeVelocity(std::vector<double>& _scan) {

	double _radius = robot.getSize().length() / 2;			// Get radius of robot
	double _averageDistance = computeDataAverage(_scan);	// Get average of scan distances
	double _over = robot.getRangeOver();					// Get max value provided by scan data

	// Get smallest distance in scan data
	double _minimalDistance = _over;
	for (unsigned int i = 0; i < _scan.size(); i++) {
		if (_scan[i] < _minimalDistance) _minimalDistance = _scan[i];
	}
	
	// Make minimalDistance mean something in averageDistance
	_averageDistance += _minimalDistance;
	_averageDistance /= 2;

	double _temp = _averageDistance - _radius;	// Value of velocity

	// If velocity > 0
	if (_temp > 0) {
		// Return velocity in range of 0..1
		return _temp / (_over - _radius);
	}
	else return 0;
}

double Logic::computeDataAverage(std::vector<double>& _scan) {
	double _dataAverage = 0;
	for (unsigned int i = 0; i < _scan.size(); i++) {
		_dataAverage += _scan[i];
	}
	_dataAverage /= _scan.size();
	return _dataAverage;
}

double Logic::computeLinearMultipiler(double _minPercentage, double _maxData, double _data) {
	double _offset = _maxData / 2;

	if (_data <= _offset) {
		return ((_minPercentage * _offset) + ((1 - _minPercentage) * _data)) / _offset;
	}
	else {
		return _offset / ((_minPercentage * _offset) + ((1 - _minPercentage) * _data));
	}
}


//////////////////////////////////////////
// PERIODICAL FUNCTIONS
//////////////////////////////////////////

void Logic::update(double dt) {
	if (!robot.isBusy()) {
		Vector2D _movement = computeMovement(scan());
		robot.move(_movement.x, _movement.y);
	}
}