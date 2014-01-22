#pragma once


//////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////

#include <vector>
#include "libs/xkontiTextUtils.h"

#include <allegro5/allegro.h>
#include "allegro5/allegro_image.h"
#include <allegro5/allegro_primitives.h>


//////////////////////////////////////////
// ROBOT CLASS
//////////////////////////////////////////

class Robot {
public:
	// Constuctor & Destructor
	Robot();
	~Robot();

	// Initialization functions
	void initBody(std::vector<float> _size, std::vector<float> _pos, float _rotation, float _maxVelocity, float _maxAVelocity);
	void initHead(std::vector<float> _pos, std::vector<float> _rotRange, std::vector<float> _range, float _rangeError, unsigned int _resolution);

	// Set Functions
	void setPos(std::vector<float> _newPos);
	void setPos(float _x, float _y);

	// Get Functions
	std::vector<float> getPos();
	std::vector<float> getHeadPos();

	void move(float _dist);				// Move robot forward by specified distance
	void move(float _dist, float _deg);	// Move and turn robot
	void turn(float _deg);				// Turn robot by specified degree value
	std::vector<float>& scan();		// Scans terrain. Returns reference to vector of distances.

	void draw();

private:
	// Body functions

	// Head functions
	float trace();			// Measure distance from current position
	float step();				// Rotate head one step to the right
	void rotateL();				// Rotate head to maximum left position
	void rotate(float _deg);	// Rotate head to Z axis position

	// Drawing functions
	void drawRect(float _centerX, float _centerY, float _width, float _height, float _rotation);

	// Body properties
	std::vector<float> size;		// Dimensions: Width, Length
	std::vector<float> pos;			// Position: X, Y
	float rotation;					// Rotation: Z axis
	float leftDistance;				// Distance left to travel
	float leftRotation;				// Rotation left to rotate
	float maxVelocity;				// Max forward velocity
	float maxAVelocity;				// Max angular velocity on Z axis (left/right)

	// Head properties
	std::vector<float> headPos;			// Head position: X, Y
	float headRotation;					// Head rotation: Z
	std::vector<float> headRotRange;	// Head Z rotation range: from - to in deg
	std::vector<float> range;			// Minimum and Maximum detection range
	float rangeError;					// Error percentage on range measuring
	unsigned int resolution;					// Number of traces in left/right scan
};