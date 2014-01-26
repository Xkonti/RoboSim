#pragma once


//////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////

#include <stdio.h>
#include "libs/xkontiTextUtils.h"
#include "libs/xkontiVector2d.h"
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "interface.h"

//////////////////////////////////////////
// GLOBAL FUNCTIONS
//////////////////////////////////////////

void drawLine(Vector2D _start, Vector2D _end);
void drawRect(Vector2D _center, double _width, double _height, double _rotation);
void drawRect(Vector2D _upLeft, Vector2D _downRight);
void drawPolygon(Vector2D _center, double _width, double _rotation, unsigned int _faces);


//////////////////////////////////////////
// ALLEGRO CLASS
//////////////////////////////////////////

class Allegro {
public:
	Allegro();
	~Allegro();

	bool init(XkontiConsoleColors* _con);
	bool setup(int _width, int _height);

	void timeStart();		// Starts measuring of time
	void cycleEnd();		// Tells allegro about end of game cycle
	double dt();			// Returns delta time. Time passed from end of last cycle.
	double getFps();			// Returns Frames Per Seconds

	ALLEGRO_DISPLAY* display;		// Have to be public. Allegro library need access to it.
	ALLEGRO_EVENT_QUEUE* event_queue;

private:
	XkontiConsoleColors* con;

	const double avrBuf;				// Average Buffer - constant value used for averages

	unsigned int width;				// Width and Height of screen
	unsigned int height;			

	double lastFrame;						// Delta Time - Duration of last Cycle
	double lastTime;				// Time of last full game cycle
	double fps;						// Frames Per Second

};