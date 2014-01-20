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

Allegro::Allegro(int _screenW, int _screenH, XkontiConsoleColors* _con) {

#if(DEBUG_ALLEGROHELPER)
	_con->print(debug, "- Allegro::Allegro - Creating\n");
#endif

	screenW = _screenW;
	screenH = _screenH;
	con = _con;


	initialized = true;

	if (!al_init()) {
		con->print(fatal, "failed to initialize allegro!\n");
		initialized = false;
	}

	display = al_create_display(screenW, screenH);
	if (!display) {
		con->print(fatal, "failed to create display!\n");
		initialized = false;
	}

	event_queue = al_create_event_queue();
	if (!event_queue) {
		con->print(fatal, "failed to create event_queue!\n");
		al_destroy_display(display);
		initialized = false;
	}
	al_register_event_source(event_queue, al_get_display_event_source(display));

#if(DEBUG_ALLEGROHELPER)
	con->print(debug, "- Allegro::Allegro - Created\n");
#endif
}

Allegro::~Allegro() {
#if(DEBUG_ALLEGROHELPER)
	con->print(debug, "- Allegro::~Allegro - Destroying\n");
#endif

	al_destroy_display(display);

#if(DEBUG_ALLEGROHELPER)
	con->print(debug, "- Allegro::~Allegro - Destroyed\n");
#endif
}