#pragma once

// Local debugging switch
#define DEBUG_INTERFACE (1)


//////////////////////////////////////////
// INCLUDES & TYPEFEF
//////////////////////////////////////////

#include "interface.h"

typedef std::string string;

//////////////////////////////////////////
// INTERFACE CONSTRUCTOR/DESTRUCTOR
//////////////////////////////////////////

Interface::Interface(std::vector<Vector2D>& _scanPoints)
:scanPoints{ _scanPoints }, con{ nullptr }, map{ nullptr },
mapW{ 0 }, mapH{ 0 }, intW{ 0 }, intH{ 0 }, addW{ 0 } {}

Interface::~Interface() {
}

bool Interface::init(string _mapPath, int _width, XkontiConsoleColors* _con) {

	addW = _width;
	con = _con;

	// Load map from file
	map = al_load_bitmap(_mapPath.c_str());
	if (!map) {
		con->print(error, "Failed to load map image: " + _mapPath);
		return false;
	}
	
	// Set some constants
	mapW = al_get_bitmap_width(map);
	mapH = al_get_bitmap_height(map);
	intW = mapW + addW;
	intH = mapH;

	return true;
}

void Interface::getMap(std::vector< std::vector<bool> >& _array) {
	_array = std::vector< std::vector<bool> >(mapW, std::vector<bool>(mapH, false));	// Creating blank map

	// Insert true values
	al_lock_bitmap(map, al_get_bitmap_format(map), ALLEGRO_LOCK_READWRITE);
	for (unsigned int x = 0; x < mapW; ++x)
	{
		for (unsigned int y = 0; y < mapH; ++y)
		{
			ALLEGRO_COLOR _col = al_get_pixel(map, x, y);
			if ( _col.r == 0 && _col.g == 0 && _col.b == 0 ) _array[x][y] = true;
		}
	}
	al_unlock_bitmap(map);
}

void Interface::draw(double dt) {
	//al_draw_bitmap(map, 0, 0, 0);

	// Draw points detected by robot
	al_lock_bitmap(al_get_target_bitmap(), al_get_bitmap_format(al_get_target_bitmap()), ALLEGRO_LOCK_READWRITE);
	for (unsigned int i = 0; i < scanPoints.size(); i++) {
		al_put_pixel(scanPoints[i].x, scanPoints[i].y, al_map_rgba_f(0, 0, 0, 0.05));
	}
	al_unlock_bitmap(al_get_target_bitmap());
}