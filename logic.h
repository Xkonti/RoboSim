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
private:
	XkontiConsoleColors& con;
	Robot& robot;

};