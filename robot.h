#pragma once


//////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////

#include <vector>
#include "libs/xkontiTextUtils.h"
#include "libs/xkontiVector2d.h"

#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_primitives.h>


//////////////////////////////////////////
// ROBOT CLASS
//////////////////////////////////////////

class Robot {
public:
	// Constuctor & Destructor
	Robot(std::vector< std::vector<bool> >& _map);
	~Robot();

	// Initialization functions
	void initBody(Vector2D _size, Vector2D _pos, float _rotation, float _maxVelocity, float _maxAVelocity);
	void initHead(Vector2D _pos, Vector2D _rotRange, float _rangeMin, float _rangeMax, float _rangeError, unsigned int _resolution, float _rangeLess, float _rangeOver);

	// Set Functions
	void setPos(Vector2D _newPos);
	void setPos(float _x, float _y);

	// Get Functions
	Vector2D getPos();
	Vector2D getHeadPos();

	void move(float _dist);				// Move robot forward by specified distance
	void move(float _dist, float _deg);	// Move and turn robot
	void turn(float _deg);				// Turn robot by specified degree value
	std::vector<float>& scan();		// Scans terrain. Returns reference to vector of distances.

	void draw();

private:
	// Body functions

	// Head functions
	float trace(float _rad);			// Measure distance from current position

	// Drawing functions
	void drawRect(float _centerX, float _centerY, float _width, float _height, float _rotation);

	// Outside pointers
	std::vector< std::vector<bool> >& map;

	// Body properties
	Vector2D size;		// Dimensions: Width, Length
	Vector2D pos;			// Position: X, Y
	float rotation;					// Rotation: Z axis
	float leftDistance;				// Distance left to travel
	float leftRotation;				// Rotation left to rotate
	float maxVelocity;				// Max forward velocity
	float maxAVelocity;				// Max angular velocity on Z axis (left/right)

	// Head properties
	Vector2D headPos;			// Head position: X, Y
	float headRotation;					// Head rotation: Z
	Vector2D headRotRange;	// Head Z rotation range: from - to in deg
	float rangeMin;			// Minimum and Maximum detection range
	float rangeMax;
	float rangeError;					// Error percentage on range measuring
	unsigned int resolution;					// Number of traces in left/right scan
	float rangeLess;
	float rangeOver;
};