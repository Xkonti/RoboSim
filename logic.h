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
	Logic(XkontiConsoleColors& _con, Robot& _robot);
	~Logic();

	bool init();

	double scan();

	// Periodical Functions
	void update(double dt);
private:
	XkontiConsoleColors& con;
	Robot& robot;

	unsigned int frame;

};