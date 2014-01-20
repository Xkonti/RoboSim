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
void events(double dt);	// Handling input events
void update(double dt);	// Computing data
void draw(double dt);	// Drawing what is to draw
void cycleEnd(double dt);// End of cycle
void close();	// Releasing resources


//////////////////////////////////////////
// GLOBAL VARIABLES
//////////////////////////////////////////

XkontiConsoleColors con;
Allegro* allegro = NULL;
bool closeProgram = false;
double frame = 1; // frame count
ALLEGRO_COLOR color;


//////////////////////////////////////////
// MAIN
//////////////////////////////////////////
int main(int argc, char** argv)
{

	if (!init())  return -1;
	if (!setup()) return -1;

	while (!closeProgram) {
		events( allegro->dt() );
		if (closeProgram) break;
		update( allegro->dt() );
		if (closeProgram) break;
		draw( allegro->dt() );
		cycleEnd( allegro->dt() );
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

void events(double dt) {
	if (!(int(frame) % 700)) {
		con.print("Czy zakonczyc dzialanie programu? (y/n)\n");
		if (con.inChar() == 'y') closeProgram = true;
	}
}


//////////////////////////////////////////
// UPDATE
//////////////////////////////////////////

void update(double dt) {
	al_rest(0.003);
	float fr = (sin(frame / 500) * 127);
	float fg = (sin(frame / 900) * 127);
	float fb = (sin(frame / 250) * 127);
	int ir = int(fr)+127;
	int ig = int(fg)+127;
	int ib = int(fb)+127;

	color = al_map_rgb(char(ir), char(ig), char(ib));

}


//////////////////////////////////////////
// DRAW
//////////////////////////////////////////

void draw(double dt) {
	al_clear_to_color(color);

	al_flip_display();
}


//////////////////////////////////////////
// CYCLEEND
//////////////////////////////////////////

void cycleEnd(double dt) {
	if (!(int(frame) % 30)) {
		con.print("FPS: %i\t", int(allegro->getFps()));
		con.print("AFPS: %i\t", int(allegro->getAFps()));
		con.print("dt: %i us\n", int(dt * 1000000));
	}
	allegro->cycleEnd();
	frame++;
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