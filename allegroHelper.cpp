#pragma once

// Local debugging switch
	#define DEBUG_ALLEGROHELPER (1)


//////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////

#include "allegroHelper.h"


//////////////////////////////////////////
// GLOBAL FUNCTIONS
//////////////////////////////////////////

void drawLine(Vector2D _start, Vector2D _end) {
	al_draw_line(_start.x, _start.y, _end.x, _end.y, al_map_rgb(100, 0, 0), 1);
}

void drawRect(Vector2D _center, double _width, double _height, double _rotation) {
	_width /= 2;
	_height /= 2;
	Vector2D _L = Vector2D(-_width, _height);
	_L.rotate(_rotation);
	Vector2D _R = Vector2D(_width, _height);
	_R.rotate(_rotation);

	Vector2D _temp1 = _center - _R;
	Vector2D _temp2 = _center - _L;
	drawLine(_temp1, _temp2);
	_temp1 = _temp2;
	_temp2 = _center + _R;
	drawLine(_temp1, _temp2);
	_temp1 = _temp2;
	_temp2 = _center + _L;
	drawLine(_temp1, _temp2);
	_temp1 = _temp2;
	_temp2 = _center - _R;
	drawLine(_temp1, _temp2);
}

void drawPolygon(Vector2D _center, double _width, double _rotation, unsigned int _faces) {
	_width /= 2;
	double _step = PI * 2 / _faces;		// Angle between 2 points
	double _angle = _rotation + (_step / 2);

	Vector2D _point1 = _center + (Vector2D(_angle) * _width);
	Vector2D _point2 = _center + (Vector2D(_angle + _step) * _width);

	for (unsigned int i = 0; i < _faces; i++) {
		drawLine(_point1, _point2);
		_angle += _step;
		_point1 = _point2;
		_point2 = _center + (Vector2D(_angle) * _width);
	}
	drawLine(_point1, _point2);
}


//////////////////////////////////////////
// ALLEGRO CONSTRUCTOR/DESTRUCTOR
//////////////////////////////////////////

Allegro::Allegro()
:display{ nullptr }, event_queue{ nullptr }, con{ nullptr },
avrBuf{ 120 }, width{ 0 }, height{ 0 }, lastFrame{ 1/60 }, lastTime{ 0 }, fps{ 60 }, aFps{ 60 } {}


Allegro::~Allegro() {
#if(DEBUG_ALLEGROHELPER)
	con->print(debug, "- Allegro::~Allegro - Destroying\n");
#endif


#if(DEBUG_ALLEGROHELPER)
	con->print(debug, "- Allegro::~Allegro - Destroyed\n");
#endif
}


//////////////////////////////////////////
// INIT
//////////////////////////////////////////

bool Allegro::init(XkontiConsoleColors* _con) {

#if(DEBUG_ALLEGROHELPER)
	_con->print(debug, "- Allegro::init - Start\n");
#endif
	
	// Arguments pass
	con = _con;

	// Initialization of Allegro
	if (!al_init()) {
		con->print(fatal, "Failed to initialize allegro!\n");
		return false;
	}
#if(DEBUG_ALLEGROHELPER)
	con->print(debug, "-- Allegro::init - al_init() successful\n");
#endif

	// Initialization of Image Addon
	if (!al_init_image_addon()) {
		con->print(fatal, "Failed to initialize al_init_image_addon!\n");
		return false;
	}
#if(DEBUG_ALLEGROHELPER)
	con->print(debug, "-- Allegro::init - al_init_image_addon() successful\n");
#endif

	// Initialization of Primitives Addon
	if (!al_init_primitives_addon()) {
		con->print(fatal, "Failed to initialize al_init_primitives_addon!\n");
		return false;
	}
#if(DEBUG_ALLEGROHELPER)
	con->print(debug, "-- Allegro::init - al_init_primitives_addon() successful\n");
#endif

	lastTime = al_get_time();

#if(DEBUG_ALLEGROHELPER)
	con->print(debug, "- Allegro::init - Success\n");
#endif

	return true;
}


//////////////////////////////////////////
// SETUP
//////////////////////////////////////////

bool Allegro::setup(int _width, int _height) {

#if(DEBUG_ALLEGROHELPER)
	con->print(debug, "- Allegro::setup - Start\n");
#endif

	// Arguments pass
	width = _width;
	height = _height;

	// Create display
	display = al_create_display(_width, _height);
	if (!display) {
		con->print(fatal, "failed to create display!\n");
		return false;
	}
#if(DEBUG_ALLEGROHELPER)
	con->print(debug, "-- Allegro::setup - al_create_display() successful\n");
#endif

	// Create Event Queue
	event_queue = al_create_event_queue();
	if (!event_queue) {
		con->print(fatal, "failed to create event_queue!\n");
		al_destroy_display(display);
		return false;
	}
	al_register_event_source(event_queue, al_get_display_event_source(display));
#if(DEBUG_ALLEGROHELPER)
	con->print(debug, "-- Allegro::setup - al_create_event_queue() successful\n");
#endif

#if(DEBUG_ALLEGROHELPER)
	con->print(debug, "- Allegro::setup - Success\n");
#endif

	return true;
}


//////////////////////////////////////////
// TIME FUNCTIONS
//////////////////////////////////////////

void Allegro::timeStart() {
	fps = 60;
	aFps = 60;
	lastFrame = 1 / 60;
	lastTime = al_get_time();
}

void Allegro::cycleEnd() {
	fps = 1 / lastFrame;
	aFps = (aFps * (avrBuf - 1) / avrBuf) + (fps / avrBuf);
	lastFrame = al_get_time() - lastTime;
	lastTime = al_get_time();
}

double Allegro::dt() {
	return lastFrame;
}

double Allegro::getFps() {
	return fps;
}

double Allegro::getAFps() {
	return aFps;
}