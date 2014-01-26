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
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "allegroHelper.h"


//////////////////////////////////////////
// GUI Classes
//////////////////////////////////////////

class Label {
public:
	Label(std::string _text, Vector2D _pos, ALLEGRO_FONT* _font);
	~Label();

	void draw(double dt);

	ALLEGRO_FONT* font;

	std::string text;
private:
	Vector2D pos;
};


class Checkbox {
public:
	Checkbox(std::string _text, Vector2D _pos, Vector2D _size, bool _state, ALLEGRO_FONT* _font);
	~Checkbox();

	bool press(Vector2D _mousePos);
	void draw(double dt);

	ALLEGRO_FONT* font;

	std::string text;
	bool state;
private:
	Vector2D pos;
	Vector2D size;
};


class Graph {
public:
	Graph(std::string _text, std::vector<double>& _data, Vector2D _pos, Vector2D _size, ALLEGRO_FONT* _font);
	~Graph();

	void draw(double dt);

	ALLEGRO_FONT* font;

	std::string text;
	std::vector<double>& data;
private:
	Vector2D pos;
	Vector2D size;
};


//////////////////////////////////////////
// INTERFACE CLASS
//////////////////////////////////////////

class Interface {
public:
	Interface(std::vector<Vector2D>& _scanPoints, std::vector<double>& _scanDistances);
	~Interface();

	bool init(std::string _mapPath, int _width, XkontiConsoleColors* _con);
	unsigned int getW(){ return intW; }
	unsigned int getH(){ return intH; }
	unsigned int getMapW(){ return mapW; }
	unsigned int getMapH(){ return mapH; }

	void getMap(std::vector< std::vector<bool> >& _array);

	void mousePressed(Vector2D _pos);

	void update(double dt);
	void draw(double dt);

	bool mapVisibility;

	std::vector<Label*> labels;
	std::vector<Checkbox*> boxes;
	std::vector<Graph*> graphs;
private:
	XkontiConsoleColors* con;
	std::vector<Vector2D>& scanPoints;
	std::vector<double>& scanDistances;

	ALLEGRO_BITMAP* map;			// Loaded map bitmap

	unsigned int mapW;			// Width of map
	unsigned int mapH;			// Height of map
	unsigned int intW;			// Width of whole interface (window)
	unsigned int intH;			// Height of whole interface (window)
	unsigned int addW;			// Width of additional interface panel
};