#pragma once


//////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////

#include <stdio.h>
#include "libs/xkontiTextUtils.h"
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_primitives.h>
#include "interface.h"


//////////////////////////////////////////
// ALLEGRO CLASS
//////////////////////////////////////////

class Allegro {
public:
	Allegro();
	~Allegro();

	bool init(XkontiConsoleColors* _con);
	bool setup(int _width, int _height);

	void cycleEnd();		// Tells allegro about end of game cycle
	double dt();			// Returns delta time. Time passed from end of last cycle.
	double getFps();			// Returns Frames Per Seconds
	double getAFps();			// Returns Average Frames Per Seconds

	ALLEGRO_DISPLAY* display;		// Have to be public. Allegro library need access to it.
	ALLEGRO_EVENT_QUEUE* event_queue;

private:
	XkontiConsoleColors* con;

	const int avrBuf;				// Average Buffer - constant value used for averages

	unsigned int width;				// Width and Height of screen
	unsigned int height;			

	double lastTime;				// Time of last full game cycle
	double fps;						// Frames Per Second
	double aFps;					// Average Frames Per Second

};