#pragma once


//////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////

#include <iostream>

#include <vector>
#include <math.h>
#include "libs/xkontiTextUtils.h"
#include "libs/xkontiVector2d.h"

#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_primitives.h>

#include "allegroHelper.h"


//////////////////////////////////////////
// ROBOT CLASS
//////////////////////////////////////////

class Robot {
public:
	// Constuctor & Destructor
	Robot(std::vector< std::vector<bool> >& _map, std::vector<Vector2D>& scanPoints);
	~Robot();

	// Initialization functions
	void initBody(Vector2D _size, Vector2D _pos, double _rotation, double _maxVelocity, double _maxAVelocity);
	void initHead(Vector2D _pos, Vector2D _rotRange, double _rangeMin, double _rangeMax, double _rangeError, unsigned int _resolution, double _rangeLess, double _rangeOver);

	// Set Functions
	void setPos(Vector2D _newPos);
	void setPos(double _x, double _y);
	void setRotation(double _rad);

	// Get Functions
	Vector2D getPos();
	Vector2D getHeadPos();
	double getRotation();
	Vector2D getSize();
	unsigned int getResolution();
	double getHeadStep();
	Vector2D getHeadRotRange();
	double getMaxRange();
	double getMinRange();

	double getIdealStep(double _distance);

	bool isBusy();

	// Commands Functions
	void move(double _dist);				// Move robot forward by specified distance
	void move(double _dist, double _rad);	// Move and turn robot
	void turn(double _rad);				// Turn robot by specified degree value
	std::vector<double> scan();		// Scans terrain. Returns reference to vector of distances.

	// Periodical Functions
	void update(double dt);
	void draw(double dt);

private:
	// Body functions

	// Head functions
	double trace(double _rad);			// Measure distance from current position

	// Outside pointers
	std::vector< std::vector<bool> >& map;
	std::vector<Vector2D>& scanPoints;

	// Body properties
	Vector2D size;		// Dimensions: Width, Length
	Vector2D pos;			// Position: X, Y
	double rotation;					// Rotation: Z axis
	double leftDistance;				// Distance left to travel
	double leftRotation;				// Rotation left to rotate
	double maxVelocity;				// Max forward velocity
	double maxAVelocity;				// Max angular velocity on Z axis (left/right)

	// Head properties
	Vector2D headPos;			// Head position: X, Y
	Vector2D headRotRange;	// Head Z rotation range: from - to in deg
	double rangeMin;			// Minimum and Maximum detection range
	double rangeMax;
	double rangeError;			// Error percentage on range measuring
	unsigned int resolution;	// Number of traces in left/right scan
	double rangeLess;			// Number used when something was nearer than rangeMin
	double rangeOver;			// Number used when nothing was detected
};