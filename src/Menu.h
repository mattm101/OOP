#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include "SciCalc.h"

using namespace std;

class Menu {
	Memory *calc;
public:
	Menu();
	~Menu();
	void start();
};

#endif // MENU_H

