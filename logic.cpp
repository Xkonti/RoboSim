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
Logic::Logic(XkontiConsoleColors& _con, Robot& _robot) : con{ _con }, robot{ _robot }, frame{ 0 } {}
Logic::~Logic() {}

bool Logic::init() {
	robot.initBody(Vector2D(20, 18), Vector2D(400, 100), 0, 40, degToRad(15));
	robot.initHead(Vector2D(3, 0), Vector2D(-PI / 2, PI / 2), 15, 250, 0.01, 20, 0, 300);
	return true;
}

double Logic::scan() {
	std::vector<double> _data = robot.scan();
	
	double _dataAverage = 0;
	for (unsigned int i = 0; i < _data.size(); i++) {
		_dataAverage += _data[i];
	}
	_dataAverage /= _data.size();
	
	double _averageDist = robot.getMaxRange() + robot.getMinRange() + _dataAverage;
	_averageDist /= 3;
	double _idealStep = robot.getIdealStep(_averageDist);

	// Skan ze zwiêkszaniem skoku o 1!
	
	
}


//////////////////////////////////////////
// PERIODICAL FUNCTIONS
//////////////////////////////////////////

void Logic::update(double dt) {
	if (!robot.isBusy()) {
		robot.move(10, scan());
	}
}