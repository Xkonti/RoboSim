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
//#include "allegroHelper.h"


//ALLEGRO_COLOR BLACK_x5 = al_map_rgba_f(0, 0, 0, 0.05);

//////////////////////////////////////////
// INTERFACE CLASS
//////////////////////////////////////////

class Interface {
public:
	Interface(std::vector<Vector2D>& _scanPoints);
	~Interface();

	bool init(std::string _mapPath, int _width, XkontiConsoleColors* _con);
	unsigned int getW(){ return intW; }
	unsigned int getH(){ return intH; }
	unsigned int getMapW(){ return mapW; }
	unsigned int getMapH(){ return mapH; }

	void getMap(std::vector< std::vector<bool> >& _array);

	void update(double dt);
	void draw(double dt);
private:
	XkontiConsoleColors* con;
	std::vector<Vector2D>& scanPoints;

	ALLEGRO_BITMAP* map;			// Loaded map bitmap

	unsigned int mapW;			// Width of map
	unsigned int mapH;			// Height of map
	unsigned int intW;			// Width of whole interface (window)
	unsigned int intH;			// Height of whole interface (window)
	unsigned int addW;			// Width of additional interface panel
};