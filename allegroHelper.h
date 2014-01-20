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

	void cycleEnd();		// Tells allegro about end of game cycle
	double dt();			// Returns delta time. Time passed from end of last cycle.
	double getFps();			// Returns Frames Per Seconds
	double getAFps();			// Returns Average Frames Per Seconds
	
	bool initialized;

private:
	XkontiConsoleColors* con;

	const int avrBuf;				// Average Buffer - constant value used for averages

	int screenW; int screenH;		// Width and Height of screen
	double lastTime;				// Time of last full game cycle
	double fps;						// Frames Per Second
	double aFps;					// Average Frames Per Second

};