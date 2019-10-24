#include "pch.h"
#include <iostream>
#include "consts.h"
#include "tgeom.h"
#include "circle.h"
#include "consoleroutine.h"

TCircle::TCircle() {
	TGeom::TGeom();
	symb = ' ';
	r = rand() % 5 + 10;
	strcpy_s(name, defaultNameLength, "TCircle");
}

TCircle::~TCircle() {

	TGeom::~TGeom();
}

int TCircle::cointainsPoint(short X, short Y) {
	int result = 0;
	if (((X - x)*(X - x) + (Y - y)*(Y - y)) <= (r * r)) {
		result = 1;
	}
	return result;
};

//


void TCircle::Print() {
	consoleSetColors(clLightRed, clLightRed);
	for (int i = (x - r); i <= (x + r); i++) {
		for (int j = (y - r); j <= (y + r); j++) {
			if (1 == cointainsPoint(i, j)) {
				consoleGotoXY(i, j);
				printf("%c", symb);
			}
		}
	}
}
void TCircle::Erase() {
	consoleSetColors(clBlack, clBlack);
	for (int i = (x - r); i <= (x + r); i++) {
		for (int j = (y - r); j <= (y + r); j++) {
			if (1 == cointainsPoint(i, j)) {
				consoleGotoXY(i, j);
				printf(" ");
			}
		}
	}
}