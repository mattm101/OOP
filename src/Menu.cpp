#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include "Menu.h"

using namespace std;

Menu::Menu() {
	this->calc = NULL;
}
Menu::~Menu() {
	delete this->calc;
	cout << " Destruktor Menu\n";
}

void Menu::start() {
	unsigned char x = 0;
	bool exit = 0;
	while (!exit) {
		system("cls");
		cout << "Wybierz model kalkulatora.\n\n"
			" s - kalkulator z pamiecia\n"
			" n - kalkulator naukowy z pamiecia\n\n"
			" Aby zamknac wcisnij dowolny klawisz alfanumeryczny.\n"
			">";
		cin >> x;
		switch (x) {
		case 's':
			calc = new Calc;
			break;
		case 'n':
			calc = new SciCalc;
			break;
		default:
			exit = 1;
			break;
		}
		if (calc) {
			calc->start();
			delete calc;
			calc = NULL;
		}
	}
}
