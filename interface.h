#pragma once


//////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////

#include <string>
#include <vector>
#include "libs/xkontiTextUtils.h"
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_primitives.h>

//////////////////////////////////////////
// INTERFACE CLASS
//////////////////////////////////////////

class Interface {
public:
	Interface();
	~Interface();

	bool init(std::string _mapPath, int _width, XkontiConsoleColors* _con);
	unsigned int getW(){ return intW; }
	unsigned int getH(){ return intH; }
	unsigned int getMapW(){ return mapW; }
	unsigned int getMapH(){ return mapH; }

	void getMap(std::vector< std::vector<bool> >& _array);

	void draw(double dt);
private:
	XkontiConsoleColors* con;

	ALLEGRO_BITMAP* map;			// Loaded map bitmap
	ALLEGRO_BITMAP* mapScan;		// Detected obstructions
	ALLEGRO_BITMAP* overlay;		// Total overlay (used with slowly disappearing data)

	unsigned int mapW;			// Width of map
	unsigned int mapH;			// Height of map
	unsigned int intW;			// Width of whole interface (window)
	unsigned int intH;			// Height of whole interface (window)
	unsigned int addW;			// Width of additional interface panel
};