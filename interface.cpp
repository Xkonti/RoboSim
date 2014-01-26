#pragma once

// Local debugging switch
#define DEBUG_INTERFACE (0)


//////////////////////////////////////////
// INCLUDES & TYPEFEF
//////////////////////////////////////////

#include "interface.h"

typedef std::string string;


//////////////////////////////////////////
// LABEL CLASS
//////////////////////////////////////////

Label::Label(std::string _text, Vector2D _pos, ALLEGRO_FONT* _font) : text{ _text }, pos{ _pos }, font{ _font } {}
Label::~Label() {}

void Label::draw(double dt) {
	al_draw_text(font, al_map_rgb(0, 0, 0), pos.x, pos.y, ALLEGRO_ALIGN_LEFT, text.c_str());
}


//////////////////////////////////////////
// CHECKBOX CLASS
//////////////////////////////////////////

Checkbox::Checkbox(std::string _text, Vector2D _pos, Vector2D _size, bool _state, ALLEGRO_FONT* _font) : text{ _text }, pos{ _pos }, size{ _size }, state{ _state }, font{ _font } {}
Checkbox::~Checkbox() {}

bool Checkbox::press(Vector2D _mousePos) {
	if (_mousePos.x >= pos.x && _mousePos.x <= pos.x + size.x && _mousePos.y >= pos.y && _mousePos.y <= pos.y + size.y) {
		if (state) state = false;
		else state = true;
		return true;
	}
	return false;
}

void Checkbox::draw(double dt) {
	drawRect(pos, pos + size);
	if (state) drawRect(pos + (size / 4), pos + (size * 0.75));
	al_draw_text(font, al_map_rgb(0, 0, 0), pos.x + size.x + 5, pos.y, ALLEGRO_ALIGN_LEFT, text.c_str());
}


//////////////////////////////////////////
// GRAPH CLASS
//////////////////////////////////////////

Graph::Graph(std::string _text, std::vector<double>& _data, Vector2D _pos, Vector2D _size, ALLEGRO_FONT* _font) : text{ _text }, data{ _data }, pos{ _pos }, size{ _size }, font{ _font } {}
Graph::~Graph() {}

void Graph::draw(double dt) {
	// Frame
	drawRect(pos, pos + size);
	
	double _minX = pos.x + 2;
	double _maxX = pos.x + size.x - 2;
	double _step = (_maxX - _minX) / (data.size() - 1);
	double _minY = pos.y + 2;
	double _maxY = pos.y + size.y - 2;
	double _maxData = 0;

	for (unsigned int i = 0; i < data.size(); i++) if (data[i] > _maxData) _maxData = data[i];

	double _mul = (_maxY - _minY) / _maxData;

	Vector2D _start;
	Vector2D _end;

	for (unsigned int i = 0; i < data.size(); i++) {
		_start = Vector2D(_minX + (i * _step), _maxY);
		_end = Vector2D(_minX + (i * _step), _maxY - (data[i] * _mul));
		drawLine(_start, _end);
	}
}


//////////////////////////////////////////
// INTERFACE CONSTRUCTOR/DESTRUCTOR
//////////////////////////////////////////

Interface::Interface(std::vector<Vector2D>& _scanPoints, std::vector<double>& _scanDistances)
:mapVisibility{ true }, scanPoints{ _scanPoints }, scanDistances{ _scanDistances }, con{ nullptr }, map{ nullptr },
mapW{ 0 }, mapH{ 0 }, intW{ 0 }, intH{ 0 }, addW{ 0 } {}

Interface::~Interface() {}


//////////////////////////////////////////
// INIT FUNCTION
//////////////////////////////////////////

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


//////////////////////////////////////////
// GET FUNCTIONS
//////////////////////////////////////////

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

void Interface::mousePressed(Vector2D _pos) {
	bool end = false;
	for (unsigned int i = 0; i < boxes.size(); i++) {
		if (boxes[i]->press(_pos)) {
			end = true;
			break;
		}
	}

	if (!end) {}
}


//////////////////////////////////////////
// PERIODICAL FUNCTIONS
//////////////////////////////////////////

void Interface::draw(double dt) {
	// Draw Map
	if (mapVisibility) al_draw_bitmap(map, 0, 0, 0);

	// Draw points detected by robot
	al_lock_bitmap(al_get_target_bitmap(), al_get_bitmap_format(al_get_target_bitmap()), ALLEGRO_LOCK_READWRITE);
	for (unsigned int i = 0; i < scanPoints.size(); i++) {
		al_put_pixel(scanPoints[i].x, scanPoints[i].y, al_map_rgba_f(0, 0, 0, 0.05));
	}
	al_unlock_bitmap(al_get_target_bitmap());

	// Draw gui
	for (unsigned int i = 0; i < boxes.size(); i++) boxes[i]->draw(dt);
	for (unsigned int i = 0; i < labels.size(); i++) labels[i]->draw(dt);
	for (unsigned int i = 0; i < graphs.size(); i++) graphs[i]->draw(dt);
}



//////////////////////////////////////////
// CHECKBOX CONSTRUCTOR/DESTRUCTOR
//////////////////////////////////////////




//////////////////////////////////////////
// OTHER FUNCTIONS
//////////////////////////////////////////

