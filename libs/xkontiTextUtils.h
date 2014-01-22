#pragma once


//////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////

#include <iostream>
#include <stdio.h>
#include <string>
#include <Windows.h>


//////////////////////////////////////////
// ENUMERATIONS
//////////////////////////////////////////

// Used in XkontiConsoleColors for selecting colors:
enum XkontiColorsEnum { text, debug, error, fatal, good, input };


//////////////////////////////////////////
// GLOBAL FUNCTIONS
//////////////////////////////////////////

// Flushes input stream passed by Enter key:
void xkontiFlushInput();


//////////////////////////////////////////
// XKONTICONSOLECOLORS CLASS
//////////////////////////////////////////

// Allows for colored text in console.
// In addition provides various input and output functions with built in coloring and error handling.
class XkontiConsoleColors {
public:
	// Constructors, Destructor
	XkontiConsoleColors();									// Standard colors
	XkontiConsoleColors(unsigned short int* _colors[6]);	// Own created colors
	~XkontiConsoleColors();

	// Color Functions
	void setCol(XkontiColorsEnum _color);		// Sets color of output
	void setCol(unsigned short int _color);		// Sets color of output
	void in();									// Sets color of output as input
	unsigned short int makeCol(bool fRed, bool fGreen, bool fBlue, bool fIdensity,	// Calculates color from provided bits
		bool bRed, bool bGreen, bool bBlue, bool bIdensity);

	// Test Functions
	void printTest();		// Prints text with all standard colors
	void printAllColors();	// Prints all available colors in console

	// Print Functions
	void print(std::string _text);					// Prints text with standard text color
	void print(std::string _text, int _value);		// Prints text with standard text color
	void print(XkontiColorsEnum _color, std::string _text);		// Prints text with selected standard color
	void print(unsigned short int _color, std::string text);	// Prints text with custom color
	void print(XkontiColorsEnum _color, std::string text, int _value);	// Prints text with selected standard color
	void print(unsigned short int _color, std::string text, int _value);// Prints text with custom color

	// Specialised Print Functions
	void deb(std::string _text);							// Prints debug text
	void deb(std::string _text, int _value);				// Prints debug text with one variable
	void deb(std::string _text, int _value1, int _value2);	// Prints debug text with two variables

	// External Input Functions [[ variable = inputFunction(); ]]
	int inInt();			// Prompts user for integer input and then returns it
	char inChar();			// Prompts user for character input and then returns it
	std::string inString();	// Prompts user for string input and then returns it

	// Internal Input Functions [[ inputFunction(&variable); ]]
	void in(int& _target);			// Prompts user for integer input and then puts it in provided variable
	void in(char& _target);			// Prompts user for character input and then puts it in provided variable
	void in(std::string& _target);	// Prompts user for string input and then puts it in provided variable

	// Other Input Functions
	bool inAny();			// Prompts user for any character and returns if any was entered

private:
	// Input Handles
	HANDLE hstdin = GetStdHandle(STD_INPUT_HANDLE);
	HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);

	// Console properties before XkontiConsoleColors initialization
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	// Color table
	unsigned short int colors[6];
};