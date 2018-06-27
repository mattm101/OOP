#ifndef CALC_H
#define CALC_H

#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include "Memory.h"

using namespace std;

class Calc : public Memory {
protected:
	double result;
	bool showMem;

	void createMemory();
	double appendEquation(int);
	void accessMemory(string);
	void show();
	void operation();

	friend double stringToDouble(string);
	friend int stringToInt(string);
public:
	Calc();
	~Calc();
	void start();
};

#endif // CALC_H

