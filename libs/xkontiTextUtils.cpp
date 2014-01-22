#pragma once


//////////////////////////////////////////
// INCLUDES
//////////////////////////////////////////

#include "xkontiTextUtils.h"


//////////////////////////////////////////
// GLOBAL FUNCTIONS
//////////////////////////////////////////

void xkontiFlushInput() {
	for (int i = 0; i < 10000; i++) {
		int trashBin = getchar();
		//printf("Flushing: %i - nr: %i\n", trashBin, i);
		if (trashBin == 10) break;
	}
}


//////////////////////////////////////////
// XKONTICONSOLECOLORS
//////////////////////////////////////////
//////////////////////////////////////////
// XKONTICONSOLECOLORS CONSTRUCTOR/DEST...
//////////////////////////////////////////

XkontiConsoleColors::XkontiConsoleColors() {
	hstdin = GetStdHandle(STD_INPUT_HANDLE);
	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hstdout, &csbi);

	colors[0] = 15;
	colors[1] = 8;
	colors[2] = 12;
	colors[3] = 207;
	colors[4] = 10;
	colors[5] = 11;
}

XkontiConsoleColors::XkontiConsoleColors(unsigned short int* _colors[6]) {
	hstdin = GetStdHandle(STD_INPUT_HANDLE);
	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hstdout, &csbi);

	colors[0] = *_colors[0];
	colors[1] = *_colors[1];
	colors[2] = *_colors[2];
	colors[3] = *_colors[3];
	colors[4] = *_colors[4];
	colors[5] = *_colors[5];
}

XkontiConsoleColors::~XkontiConsoleColors() {
	FlushConsoleInputBuffer(hstdin);
	SetConsoleTextAttribute(hstdout, csbi.wAttributes);
}


//////////////////////////////////////////
// COLOR FUNCTIONS
//////////////////////////////////////////

void XkontiConsoleColors::setCol(XkontiColorsEnum _color) {
	SetConsoleTextAttribute(hstdout, colors[_color]);
}

void XkontiConsoleColors::setCol(unsigned short int _color) {
	SetConsoleTextAttribute(hstdout, _color);
}

void XkontiConsoleColors::in() {
	SetConsoleTextAttribute(hstdout, colors[input]);
}

unsigned short int XkontiConsoleColors::makeCol(bool fRed, bool fGreen, bool fBlue, bool fIdensity,
	bool bRed, bool bGreen, bool bBlue, bool bIdensity) {

	unsigned short int col = 0;

	if (fBlue) col += 1;
	if (fGreen) col += 2;
	if (fRed) col += 4;
	if (fIdensity) col += 8;
	if (bBlue) col += 16;
	if (bGreen) col += 32;
	if (bRed) col += 64;
	if (bIdensity) col += 128;

	return col;
}


//////////////////////////////////////////
// TEST FUNCTIONS
//////////////////////////////////////////

void XkontiConsoleColors::printTest() {
	this->print(text, "\nTo jest sobie zwykly tekst.\n");
	this->print(debug, "A to jest wiadomosc debugujaca...\n");
	this->print(error, "Zwyczajny blad nr %i.\n", 404);
	this->print(fatal, "Totalnie zly error!\n");
	this->print(good, "Na szczescie sa tez dobre wiadomosci :)\n");
	this->print(input, "A na koncu dane wejsciowe.\n\n");
}

void XkontiConsoleColors::printAllColors() {
	this->print(csbi.wAttributes, "\nAll the colors:\n");
	for (int i = 0; i < 256; i++) {
		this->print(i, "Color %i\n", i);
	}
	this->print(csbi.wAttributes, "---------\n\n");
}


//////////////////////////////////////////
// PRINT FUNCTIONS
//////////////////////////////////////////

void XkontiConsoleColors::print(std::string _text) {
	this->setCol(text);
	printf(_text.c_str());
}

void XkontiConsoleColors::print(std::string _text, int _value) {
	this->setCol(text);
	printf(_text.c_str(), _value);
}

void XkontiConsoleColors::print(XkontiColorsEnum _color, std::string _text) {
	this->setCol(_color);
	printf(_text.c_str());
}

void XkontiConsoleColors::print(unsigned short int _color, std::string _text) {
	this->setCol(_color);
	printf(_text.c_str());
}

void XkontiConsoleColors::print(XkontiColorsEnum _color, std::string _text, int _value) {
	this->setCol(_color);
	printf(_text.c_str(), _value);
}

void XkontiConsoleColors::print(unsigned short int _color, std::string _text, int _value) {
	this->setCol(_color);
	printf(_text.c_str(), _value);
}


//////////////////////////////////////////
// SPECIALISED PRINT FUNCTIONS
//////////////////////////////////////////

void XkontiConsoleColors::deb(std::string _text) {
	this->setCol(debug);
	printf(_text.c_str());
}

void XkontiConsoleColors::deb(std::string _text, int _value) {
	this->setCol(debug);
	printf(_text.c_str(), _value);
}

void XkontiConsoleColors::deb(std::string _text, int _value1, int _value2) {
	this->setCol(debug);
	printf(_text.c_str(), _value1, _value2);
}


//////////////////////////////////////////
// EXTERNAL INPUT FUNCTIONS
//////////////////////////////////////////

int XkontiConsoleColors::inInt() {
	int _target = NULL;
	while (1) {
		_target = NULL;
		SetConsoleTextAttribute(hstdout, colors[input]);
		scanf_s("%d", &_target);
		if (_target != NULL) break;
		xkontiFlushInput();
		
		this->print(error, "Passed value is not integer. Try again:\n");
	}
	xkontiFlushInput();
	return _target;
}

char XkontiConsoleColors::inChar() {
	char _target = NULL;
	while (1) {
		_target = NULL;
		SetConsoleTextAttribute(hstdout, colors[input]);
		scanf_s("%c", &_target);
		if (_target != NULL) break;
		xkontiFlushInput();

		this->print(error, "Passed value is not character. Try again:\n");
	}
	xkontiFlushInput();
	return _target;
}

std::string XkontiConsoleColors::inString() {
	SetConsoleTextAttribute(hstdout, colors[input]);
	std::string _target = "";
	while (1) {
		_target = "";
		SetConsoleTextAttribute(hstdout, colors[input]);
		scanf_s("%s", _target);
		if (_target != "") break;
		xkontiFlushInput();

		this->print(error, "Passed value is not string. Try again:\n");
	}
	xkontiFlushInput();
	return _target;
}


//////////////////////////////////////////
// INTERNAL INPUT FUNCTIONS
//////////////////////////////////////////

void XkontiConsoleColors::in(int& _target) {
	int __target = NULL;
	while (1) {
		__target = NULL;
		SetConsoleTextAttribute(hstdout, colors[input]);
		scanf_s("%d", &__target);
		if (__target != NULL) break;
		xkontiFlushInput();

		this->print(error, "Passed value is not integer. Try again:\n");
	}
	xkontiFlushInput();
	_target = __target;
}

void XkontiConsoleColors::in(char& _target) {
	char __target = NULL;
	while (1) {
		__target = NULL;
		SetConsoleTextAttribute(hstdout, colors[input]);
		scanf_s("%c", &__target);
		if (__target != NULL) break;
		xkontiFlushInput();

		this->print(error, "Passed value is not character. Try again:\n");
	}
	xkontiFlushInput();
	_target = __target;
}

void XkontiConsoleColors::in(std::string& _target) {
	SetConsoleTextAttribute(hstdout, colors[input]);
	std::string __target = "";
	while (1) {
		__target = "";
		SetConsoleTextAttribute(hstdout, colors[input]);
		scanf_s("%s", &__target);
		if (__target != "") break;
		xkontiFlushInput();

		this->print(error, "Passed value is not string. Try again:\n");
	}
	xkontiFlushInput();
	_target = __target;
}


//////////////////////////////////////////
// OTHER INPUT FUNCTIONS
//////////////////////////////////////////

bool XkontiConsoleColors::inAny() {
	char _target = NULL;
	scanf_s("%c", &_target);
	if (_target == 10) return false;
	xkontiFlushInput();
	return true;
}