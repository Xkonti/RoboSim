#pragma once


//////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////

#include <stdio.h>
#include "xkontiTextUtils.h"
#include <allegro5/allegro.h>


//////////////////////////////////////////
// ALLEGRO CLASS
//////////////////////////////////////////

class Allegro {
public:
	Allegro(int _screenWidth, int _screenHeight, XkontiConsoleColors* _con);
	~Allegro();

	ALLEGRO_DISPLAY* display;		// Have to be public. Allegro library need access to it.
	ALLEGRO_EVENT_QUEUE* event_queue;
	
	bool initialized;

private:
	XkontiConsoleColors* con;

	int screenW; int screenH;		// Width and Height of screen

};