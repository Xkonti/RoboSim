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
#include <allegro5/allegro_primitives.h>

#include "libs/xkontiTextUtils.h"
#include "libs/xkontiVector2d.h"

#include "allegroHelper.h"
#include "interface.h"
#include "robot.h"
#include "logic.h"

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

Vector2D _tempDir(degToRad(52));

std::vector< std::vector<bool> > map;
std::vector<Vector2D> scanPoints;
ALLEGRO_BITMAP* image = nullptr;
unsigned int interfaceWidth = 200;		// Width of additional interface panel
bool closeProgram = false;
double frame = 1; // frame count
ALLEGRO_COLOR color;

Interface inter = Interface(scanPoints);
Robot robot = Robot(map, scanPoints);
Logic logic = Logic(con, robot);


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

#if(DEBUG_ENABLED)
	con.deb("\n==== Debugowanie jest wlaczone ====\n");
#endif

	// Get user data
	con.print("Witaj w RoboSim!\n\nPodaj nazwe mapy:\n");
	//std::string _path = con.inString();
	std::string _path;
	std::cin >> _path;

	// Init Allegro and Interface
	if (!allegro.init(&con)) {
		con.print(error, "Failed to initialize Allegro class!");
		return false;
	}
#if(DEBUG_ENABLED)
	con.print(debug, "-- init - allegro.init() success\n");
#endif
	/*
	al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP);
	ALLEGRO_BITMAP* _image = al_load_bitmap("map1.bmp");

	if (!_image) {
		con.print(error, "Failed to load map image: " + _path);
		return false;
	}

	al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP);
	image = al_load_bitmap("map1.bmp");

	if (!image) {
		con.print(error, "Failed to load map image: " + _path);
		return false;
	}
	*/
#if(DEBUG_ENABLED)
	con.print(debug, "-- init - image map1.png - loaded\n");
#endif

	if (!inter.init(_path, interfaceWidth, &con)) {
		con.print(error, "Failed to initialize Interface class!");
		return false;
	}

	inter.getMap(map);

	if (!allegro.setup(inter.getW(), inter.getH())) {
		con.print(error, "Failed to setup Allegro class!");
		return false;
	}
#if(DEBUG_ENABLED)
	con.print(debug, "-- init - allegro.setup() success\n");
#endif

	return true;
}


//////////////////////////////////////////
// SETUP
//////////////////////////////////////////

bool setup() {

	logic.init();

	con.print(error, "Robot x, y: %i", int(robot.getPos().x));
	con.print(error, ", %i\n", int(robot.getPos().y));
	
	allegro.timeStart();

	return true;
}


//////////////////////////////////////////
// EVENTS
//////////////////////////////////////////

void events(double dt) {
	if (!(int(frame) % 70000)) {
		con.print("Czy zakonczyc dzialanie programu? (y/n)\n");
		if (con.inChar() == 'y') closeProgram = true;
	}
}


//////////////////////////////////////////
// UPDATE
//////////////////////////////////////////

void update(double dt) {
	al_rest(0.003);
	float fr = (sin(frame / 150) * 127);
	float fg = (sin(frame / 151) * 127);
	float fb = (sin(frame / 152) * 127);
	int ir = int(fr)+127;
	int ig = int(fg)+127;
	int ib = int(fb)+127;

	color = al_map_rgb(char(ir), char(ig), char(ib));

	robot.update(dt);
	logic.update(dt);
}


//////////////////////////////////////////
// DRAW
//////////////////////////////////////////

void draw(double dt) {
	al_clear_to_color(color);
	inter.draw(dt);
	robot.draw(dt);
	al_flip_display();
}


//////////////////////////////////////////
// CYCLEEND
//////////////////////////////////////////

void cycleEnd(double dt) {
	if (!(int(frame) % 30)) {
		con.print("FPS: %i\t", int(allegro.getFps()));
		con.print("AFPS: %i\t", int(allegro.getAFps()));
		con.print("PTS: %i\n", scanPoints.size());
		//con.print("dt: %i us\n", int(dt * 1000000));
	}
	allegro.cycleEnd();
	frame++;
}

//////////////////////////////////////////
// CLOSE
//////////////////////////////////////////

void close() {

	al_destroy_bitmap(image);
	allegro.~Allegro();		// Usuñ allegro

#if(DEBUG_ENABLED)
	con.deb("\n==== Enter aby zakonczyc ====\n");
	con.inAny();	// PotwierdŸ zakoñczenie programu
#endif

	con.~XkontiConsoleColors();	// Usuñ XkontiConsoleColors

}