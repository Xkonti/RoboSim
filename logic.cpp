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

Logic::Logic(XkontiConsoleColors& _con, Robot& _robot) : con{ _con }, robot{ _robot } {}
Logic::~Logic() {}

bool Logic::init() {
	robot.initBody(Vector2D(30, 30), Vector2D(40, 40), 0, 10, 10);
	robot.initHead(Vector2D(), Vector2D(-PI / 2, PI / 2), 30, 150, 0.01, 100, 0, 300);
	return true;
}