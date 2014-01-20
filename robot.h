#pragma once


//////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////

#include <vector>
#include "xkontiTextUtils.h"


//////////////////////////////////////////
// ROBOT CLASS
//////////////////////////////////////////

class Robot {
public:
	Robot();
	~Robot();

	void move(float _dist);				// Move robot forward by specified distance
	void move(float _dist, float _deg);	// Move and turn robot
	void turn(float _deg);				// Turn robot by specified degree value
	std::vector<float>& scan(float _deg);		// Scans terrain. Returns reference to vector of distances.
			// _deg is degree pointing towards -Z from XY plane {?!?}


private:
	std::vector<float> size;		// Dimensions: Width, Length, Height
	std::vector<float> pos;			// Position: X, Y
	float rotation;					// Rotation: Z axis
	float velocity;					// Forward vector velocity
	float maxVelocity;				// Max forward velocity
	float maxAVelocity;				// Max angular velocity on Z axis (left/right)
	
	Scanner scanner;
};


//////////////////////////////////////////
// SCANNER CLASS
//////////////////////////////////////////

class Scanner {
public:
	Scanner();
	~Scanner();

	std::vector<float>& scan(float _deg);		// Scans terrain. Returns reference to vector of distances.
			// _deg is degree pointing towards -Z from XY plane {?!?}

private:
	float trace();			// Measure distance from current position
	void rotate(float _xDeg, float _zDeg);	// Rotate head to X and Z axis position
	void rotateX(float _deg);				// Rotate head to X axis position
	void rotateY(float _deg);				// Rotate head to Z axis position

	std::vector<float> scanSize;		// Arm dimensions: W, L, H
	std::vector<float> scanPos;			// Head position: X, Y, Z
	std::vector<float> scanRotation;	// Head rotation: X, Z
	std::vector<float> scanXRotRange;	// Head X rotation range: from - to in deg
	std::vector<float> scanZRotRange;	// Head Z rotation range: from - to in deg

	std::vector<float> scanRange;		// Minimum and Maximum detection range
	float rangeError;					// Error percentage on range measuring
	float resolution;					// Number of traces in left/right scan
};