// Global debugging switch
#define DEBUG_ENABLED (1)


//////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////

#include <iostream>
#include <allegro5/allegro.h>

#include "xkontiTextUtils.h"

#include "allegroHelper.h"


//////////////////////////////////////////
// FUNCTION DECLARATIONS
//////////////////////////////////////////

bool init();	// Pre-allegro settings, allegro setup
bool setup();	// Allegro settings
void events();	// Handling input events
void update();	// Computing data
void draw();	// Drawing what is to draw
void close();	// Releasing resources


//////////////////////////////////////////
// GLOBAL VARIABLES
//////////////////////////////////////////

XkontiConsoleColors con;
Allegro* allegro = NULL;
bool closeProgram = false;
float i = 0; // TEMP
ALLEGRO_COLOR color;


//////////////////////////////////////////
// MAIN
//////////////////////////////////////////
int main(int argc, char** argv)
{

	if (!init())  return -1;
	if (!setup()) return -1;

	while (!closeProgram) {
		events();
		if (closeProgram) break;
		update();
		if (closeProgram) break;
		draw();
	}

	close();

	return 0;
}


//////////////////////////////////////////
// INIT
//////////////////////////////////////////

bool init() {

	con = XkontiConsoleColors();		// Zainicjowanie domyœlnych kolorów do konsoli

#if(DEBUG_ENABLED)
	con.deb("\n==== Debugowanie jest wlaczone ====\n");
#endif

	con.print("Witaj w RoboSim - Dwu i pol wymiarowym symulatorze robota!\n\nPodaj szerokosc okna:\n");
	int _w = con.inInt();
	con.print("\nPodaj wysokosc okna:\n");
	int _h = con.inInt();

	allegro = new Allegro(_w, _h, &con);
	if (!allegro->initialized) return false;
}


//////////////////////////////////////////
// SETUP
//////////////////////////////////////////

bool setup() {
	return true;
}


//////////////////////////////////////////
// EVENTS
//////////////////////////////////////////

void events() {
	if (i == 1000) {
		con.print("Czy zakonczyc dzialanie programu? (y/n)\n");
		if (con.inChar() == 'y') closeProgram = true;
		i = 0;
	}
}


//////////////////////////////////////////
// UPDATE
//////////////////////////////////////////

void update() {
	al_rest(0.001);
	float fr = (sin(i / 500) * 127);
	float fg = (sin(i / 900) * 127);
	float fb = (sin(i / 250) * 127);
	int ir = int(fr)+127;
	int ig = int(fg)+127;
	int ib = int(fb)+127;

	color = al_map_rgb(char(ir), char(ig), char(ib));
	i++;

}


//////////////////////////////////////////
// DRAW
//////////////////////////////////////////

void draw() {
	al_clear_to_color(color);

	al_flip_display();
}


//////////////////////////////////////////
// CLOSE
//////////////////////////////////////////

void close() {

	allegro->~Allegro();		// Usuñ allegro

#if(DEBUG_ENABLED)
	con.deb("\n==== Enter aby zakonczyc ====\n");
	con.inAny();	// PotwierdŸ zakoñczenie programu
#endif

	con.~XkontiConsoleColors();	// Usuñ XkontiConsoleColors

}