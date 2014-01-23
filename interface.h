#pragma once


//////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////

#include <string>
#include <vector>
#include "libs/xkontiTextUtils.h"
#include "libs/xkontiVector2d.h"
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_primitives.h>
#include "robot.h"
#include "allegroHelper.h"


//////////////////////////////////////////
// INTERFACE CLASS
//////////////////////////////////////////

class Interface {
public:
	Interface();
	~Interface();

	bool init(std::string _mapPath, int _width, XkontiConsoleColors* _con, Robot* _robot);
	unsigned int getW(){ return intW; }
	unsigned int getH(){ return intH; }
	unsigned int getMapW(){ return mapW; }
	unsigned int getMapH(){ return mapH; }

	void getMap(std::vector< std::vector<bool> >& _array);

	void update(double dt);
	void draw(double dt);

	Robot* robot;
private:
	XkontiConsoleColors* con;

	ALLEGRO_BITMAP* map;			// Loaded map bitmap

	unsigned int mapW;			// Width of map
	unsigned int mapH;			// Height of map
	unsigned int intW;			// Width of whole interface (window)
	unsigned int intH;			// Height of whole interface (window)
	unsigned int addW;			// Width of additional interface panel
};