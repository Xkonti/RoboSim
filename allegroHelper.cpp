#pragma once

// Local debugging switch
	#define DEBUG_ALLEGROHELPER (1)


//////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////

#include "allegroHelper.h"


//////////////////////////////////////////
// ALLEGRO CONSTRUCTOR/DESTRUCTOR
//////////////////////////////////////////

Allegro::Allegro()
:display{ nullptr }, event_queue{ nullptr }, con{ nullptr },
avrBuf{ 120 }, width{ 0 }, height{ 0 }, lastTime{ 0 }, fps{ 0 }, aFps{ 0 } {}


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

void Allegro::cycleEnd() {
	fps = 1 / this->dt();
	aFps = (aFps * (avrBuf - 1) / avrBuf) + (fps / avrBuf);
	lastTime = al_get_time();
}

double Allegro::dt() {
	return al_get_time() - lastTime;
}

double Allegro::getFps() {
	return fps;
}

double Allegro::getAFps() {
	return aFps;
}