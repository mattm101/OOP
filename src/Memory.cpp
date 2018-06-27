#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include "Memory.h"

using namespace std;

Memory::Memory() {
	this->cells = 0;
	this->values = NULL;
}

Memory::~Memory() {
	this->removeMemory();
	cout << " Destruktor Rezerwuar" << endl;
}

void Memory::createMemory(int cells) {
	values = new double[cells];
	this->cells = cells;
	for (int i = 0; i<cells; i++) values[i] = 0;
}

void Memory::removeMemory() {
	delete[] values;
	values = NULL;
}

double Memory::getCell(int cell) {
	if (values && (cell >= 0) && (cell < cells))
		return values[cell];

	return 0;
}

void Memory::writeCell(int cell, double value) {
	if (values && (cell >= 0) && (cell < cells))
		values[cell] = value;
}

void Memory::addToCell(int cell, double value) {
	if (values && (cell >= 0) && (cell < cells))
		values[cell] += value;
}

void Memory::sutractFromCell(int cell, double value) {
	if (values && (cell >= 0) && (cell < cells))
		values[cell] -= value;
}

void Memory::clearCell(int cell) {
	if (values && (cell >= 0) && (cell < cells))
		values[cell] = 0;
}

void Memory::start() {}






