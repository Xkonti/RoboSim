#pragma once


//////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////

#include <vector>
#include "libs/xkontiTextUtils.h"
#include "libs/xkontiVector2d.h"

#include <allegro5/allegro.h>

#include "robot.h"


//////////////////////////////////////////
// LOGIC CLASS
//////////////////////////////////////////

class Logic {
public:
	Logic(XkontiConsoleColors& _con, Robot& _robot, std::vector<double>& _scanDistances);
	~Logic();

	bool init();

	std::vector<double> scan();
	Vector2D computeMovement(std::vector<double> _scan);
	double computeRotation(std::vector<double>& _scan);
	double computeVelocity(std::vector<double>& _scan);
	double computeDataAverage(std::vector<double>& _scan);
	double computeLinearMultipiler(double _minPercentage, double _maxData, double _data);

	// Periodical Functions
	void update(double dt);
	std::vector<double>& scanDistances;

	double minSideWeight;
private:
	XkontiConsoleColors& con;
	Robot& robot;

	unsigned int frame;

	double stepVelocity;

};