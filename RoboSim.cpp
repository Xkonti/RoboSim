// Global debugging switch
#define DEBUG_ENABLED (0)


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
ALLEGRO_FONT* font;

Vector2D _tempDir(degToRad(52));

std::vector< std::vector<bool> > map;
std::vector<Vector2D> scanPoints;
std::vector<double> scanDistances;
ALLEGRO_BITMAP* image = nullptr;
unsigned int interfaceWidth = 300;		// Width of additional interface panel
bool closeProgram = false;
double frame = 1; // frame count
ALLEGRO_COLOR color;

Interface inter = Interface(scanPoints, scanDistances);
Robot robot = Robot(map, scanPoints);
Logic logic = Logic(con, robot, scanDistances);


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
	font = al_load_ttf_font("Prototype.ttf", 15, 0);
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

	//al_load_ttf_font(char const *filename, int size, int flags)
	logic.init();

	// Setup GUI
	double _interX = inter.getMapW();

	inter.labels.push_back(new Label("FPS: x", Vector2D(_interX + 10, inter.getH() - 30), font));	//0
	inter.labels.push_back(new Label("Resolution: x [-Q +W]", Vector2D(_interX + 10, 50), font));	//1
	inter.labels.push_back(new Label("HeadRotRange: x [-A +S]", Vector2D(_interX + 10, 70), font));	//2
	inter.labels.push_back(new Label("Side weight: x [-Z +X]", Vector2D(_interX + 10, 90), font));	//3
	inter.labels.push_back(new Label("Minimum range: x [-R +T]", Vector2D(_interX + 10, 110), font));		//4
	inter.labels.push_back(new Label("Minimum range: x [-F +G]", Vector2D(_interX + 10, 130), font));
	inter.labels.push_back(new Label("Less Value: x [-U +I]", Vector2D(_interX + 10, 150), font));
	inter.labels.push_back(new Label("Over Value: x [-J +K]", Vector2D(_interX + 10, 170), font));

	inter.boxes.push_back(new Checkbox("Robot sight", Vector2D(_interX + 10, 10), Vector2D(16, 16), false, font));	//0

	inter.graphs.push_back(new Graph("Scan", scanDistances, Vector2D(_interX + 10, 200), Vector2D(interfaceWidth - 20, 80), font));	//0



	// Start game loop
	allegro.timeStart();
	return true;
}


//////////////////////////////////////////
// EVENTS
//////////////////////////////////////////

void events(double dt) {
	ALLEGRO_EVENT _event;

	while (!al_event_queue_is_empty(allegro.event_queue)) {

		if (al_get_next_event(allegro.event_queue, &_event)) {

			if (_event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
				closeProgram = true;
			}

			// KLAWIATURA
			else if (_event.type == ALLEGRO_EVENT_KEY_DOWN) {
				if (_event.keyboard.keycode == ALLEGRO_KEY_ESCAPE) closeProgram = true;
				else if (_event.keyboard.keycode == ALLEGRO_KEY_Q) {
					if (robot.getResolution() > 3) robot.setResolution(robot.getResolution() - 1);
				}
				else if (_event.keyboard.keycode == ALLEGRO_KEY_W) {
					if (robot.getResolution() < 300) robot.setResolution(robot.getResolution() + 1);
				}
				else if (_event.keyboard.keycode == ALLEGRO_KEY_A) {
					if (robot.getHeadRotRange().y > degToRad(5)) robot.setHeadRotRange(Vector2D(robot.getHeadRotRange().x + degToRad(5), robot.getHeadRotRange().y - degToRad(5)));
				}
				else if (_event.keyboard.keycode == ALLEGRO_KEY_S) {
					if (robot.getHeadRotRange().y < degToRad(175)) robot.setHeadRotRange(Vector2D(robot.getHeadRotRange().x - degToRad(5), robot.getHeadRotRange().y + degToRad(5)));
				}
				else if (_event.keyboard.keycode == ALLEGRO_KEY_Z) {
					if (logic.minSideWeight >= 0.05) logic.minSideWeight -= 0.05;
				}
				else if (_event.keyboard.keycode == ALLEGRO_KEY_X) {
					if (logic.minSideWeight <= 0.95) logic.minSideWeight += 0.05;
				}
				else if (_event.keyboard.keycode == ALLEGRO_KEY_R) {
					robot.setMinRange(robot.getMinRange() - 5);
					if (robot.getMinRange() < robot.getSize().length() / 2) robot.setMinRange(robot.getSize().length() / 2);
				}
				else if (_event.keyboard.keycode == ALLEGRO_KEY_T) {
					robot.setMinRange(robot.getMinRange() + 5);
					if (robot.getMinRange() > robot.getMaxRange()) robot.setMinRange(robot.getMaxRange() - 1);
				}
				else if (_event.keyboard.keycode == ALLEGRO_KEY_F) {
					robot.setMaxRange(robot.getMaxRange() - 5);
					if (robot.getMaxRange() < robot.getMinRange()) robot.setMaxRange(robot.getMinRange() + 1);
				}
				else if (_event.keyboard.keycode == ALLEGRO_KEY_G) {
					robot.setMaxRange(robot.getMaxRange() + 5);
					if (robot.getMaxRange() > 1000) robot.setMaxRange(1000);
				}
				else if (_event.keyboard.keycode == ALLEGRO_KEY_U) {
					robot.setRangeLess(robot.getRangeLess() - 5);
				}
				else if (_event.keyboard.keycode == ALLEGRO_KEY_I) {
					robot.setRangeLess(robot.getRangeLess() + 5);
				}
				else if (_event.keyboard.keycode == ALLEGRO_KEY_J) {
					robot.setRangeOver(robot.getRangeOver() - 5);
				}
				else if (_event.keyboard.keycode == ALLEGRO_KEY_K) {
					robot.setRangeOver(robot.getRangeOver() + 5);
				}
			}

			// MYSZ
			else if (_event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
				if (_event.mouse.button == 1) {
					if (_event.mouse.x > 5 && _event.mouse.x < inter.getMapW() - 5 && _event.mouse.y > 5 && _event.mouse.y < inter.getMapH() - 5) {
						robot.setPos(_event.mouse.x, _event.mouse.y);
						inter.mapVisibility = false;
					}
					else if (_event.mouse.x > inter.getMapW() && _event.mouse.x < inter.getW() && _event.mouse.y > 0 && _event.mouse.y < inter.getH()) {
						inter.mousePressed(Vector2D(_event.mouse.x, _event.mouse.y));
					}
				}
				else if (_event.mouse.button == 2) {
					if (_event.mouse.x > 0 && _event.mouse.x < inter.getMapW() && _event.mouse.y > 0 && _event.mouse.y < inter.getMapH()) {
						inter.mapVisibility = true;
					}
				}
			}
			else if (_event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
				if (_event.mouse.button == 2) {
					if (_event.mouse.x > 0 && _event.mouse.x < inter.getMapW() && _event.mouse.y > 0 && _event.mouse.y < inter.getMapH()) {
						inter.mapVisibility = false;
					}
				}
			}
			
		}

	}
}


//////////////////////////////////////////
// UPDATE
//////////////////////////////////////////

void update(double dt) {
	al_rest(0.003);

	if (robot.getPos().x > 5 && robot.getPos().x < inter.getMapW() - 5 && robot.getPos().y > 5 && robot.getPos().y < inter.getMapH() - 5) {
		robot.update(dt);
		logic.update(dt);
	}

	// Gui update
	if (!(int(frame) % 30)) {
		inter.labels[0]->text = "FPS: " + std::to_string(int(allegro.getFps()));
		inter.labels[1]->text = "Resolution: " + std::to_string(robot.getResolution()) + " [-Q +W]";
		inter.labels[2]->text = "HeadRotRange: " + std::to_string(int(radToDeg(robot.getHeadRotRange().y * 2))) + " [-A +S]";
		inter.labels[3]->text = "Side weight: " + std::to_string(logic.minSideWeight) + " [-Z +X]";
		inter.labels[4]->text = "Minimum range: " + std::to_string(int(robot.getMinRange())) + " [-R +T]";
		inter.labels[5]->text = "Maximum range: " + std::to_string(int(robot.getMaxRange())) + " [-F +G]";
		inter.labels[6]->text = "Less Value: " + std::to_string(int(robot.getRangeLess())) + " [-U +I]";
		inter.labels[7]->text = "Over Value: " + std::to_string(int(robot.getRangeOver())) + " [-J +K]";
	}
	
}


//////////////////////////////////////////
// DRAW
//////////////////////////////////////////

void draw(double dt) {
	al_clear_to_color(al_map_rgb(255,255,255));
	inter.draw(dt);
	robot.draw(dt, inter.boxes[0]->state);
	al_flip_display();
}


//////////////////////////////////////////
// CYCLEEND
//////////////////////////////////////////

void cycleEnd(double dt) {
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