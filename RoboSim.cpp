// Global debugging switch
#define DEBUG_ENABLED (1)


//////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////

#include <iostream>
#include <string>
#include <vector>
#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"

#include "libs/xkontiTextUtils.h"

#include "allegroHelper.h"
#include "interface.h"

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
Allegro allegro;
Interface inter;

std::vector< std::vector<bool> > map;
ALLEGRO_BITMAP* image = nullptr;
unsigned int interfaceWidth = 200;		// Width of additional interface panel
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
		events( allegro.dt() );
		if (closeProgram) break;
		update( allegro.dt() );
		if (closeProgram) break;
		draw( allegro.dt() );
		cycleEnd( allegro.dt() );
	}

	close();

	return 0;
}


//////////////////////////////////////////
// INIT
//////////////////////////////////////////

bool init() {

	//con = XkontiConsoleColors();		// Zainicjowanie domy�lnych kolor�w do konsoli

#if(DEBUG_ENABLED)
	con.deb("\n==== Debugowanie jest wlaczone ====\n");
#endif

	// Get user data
	con.print("Witaj w RoboSim!\n\nPodaj nazwe mapy:\n");
	//std::string _path = con.inString();
	std::string _path;
	std::cin >> _path;

	// Init Allegro and Interface
	if (!allegro.init("map1.png", inter, interfaceWidth, &con)) {
		con.print(error, "Failed to initialize Allegro class!");
		return false;
	}
	

	

	image = al_load_bitmap("map1.png");

	if (!image) {
		con.print(error, "Failed to load map image: " + _path);
		return false;
	}

	// Create obstruction map
	//inter->getMap(map);

	

	return true;
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
	al_draw_bitmap(image, 5, 5, 0);

	al_flip_display();
}


//////////////////////////////////////////
// CYCLEEND
//////////////////////////////////////////

void cycleEnd(double dt) {
	if (!(int(frame) % 30)) {
		con.print("FPS: %i\t", int(allegro.getFps()));
		con.print("AFPS: %i\t", int(allegro.getAFps()));
		con.print("dt: %i us\n", int(dt * 1000000));
	}
	allegro.cycleEnd();
	frame++;
}

//////////////////////////////////////////
// CLOSE
//////////////////////////////////////////

void close() {

	al_destroy_bitmap(image);
	allegro.~Allegro();		// Usu� allegro

#if(DEBUG_ENABLED)
	con.deb("\n==== Enter aby zakonczyc ====\n");
	con.inAny();	// Potwierd� zako�czenie programu
#endif

	con.~XkontiConsoleColors();	// Usu� XkontiConsoleColors

}