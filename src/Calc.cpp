#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include "Calc.h"
#include "string2number.h"

using namespace std;

Calc::Calc() : Memory() {
	this->result = 0;
	this->showMem = true;
}

Calc::~Calc() {
	this->removeMemory();
	cout << " Destruktor Calc" << endl;
}

void Calc::createMemory() {
	string input = "";
	int cells = 0, success = 0;
	do {
		system("cls");
		cout << "Podaj rozmiar pamieci: " << endl;
		cin >> input;
		cells = stringToInt(input);
		if (cells>0) {
			createMemory(cells);
			success = 1;
		}
	} while (!success);
}

double Calc::appendEquation(int division = 0) {
	double value = 0;
	string input = "";
	cin >> input;
	int dl = input.length();
	if (input[0] == 'm'){
        if(input[dl-1] == 'd'){
            value = getCell(stringToInt(input.substr(1, dl-2)));
        }
        else accessMemory(input);
	}
	else if (input == "c") {
		result = 0;
		value = 0;
	}
	else value = stringToDouble(input);
	if (division && !value) {
		result = 0;
		return 1;
	}
	return value;
}

void Calc::accessMemory(string input) {
    int dl = input.length();
	int cell = stringToInt(input.substr(1, dl-2));
	if (input[dl-1] == '+') addToCell(cell, this->result);
	else if (input[dl-1] == '-') substractFromCell(cell, this->result);
	else if (input[dl-1] == 'r') clearCell(cell);
	else if (input[dl-1] == 'v'){
        if(!showMem)
            showMem = true;
        else showMem = false;
    }
}

void Calc::show() {
	system("cls");
	cout<<"Kalkulator Prosty z pamiecia\n\n";
	cout<<"  Flagi: wyjscie -> \"x\" , zerowanie wyniku -> \"c\".\n\n";
	cout<<"  Wyswietlanie/ukrywanie komorek pamieci -> \"mv\".\n";
	cout<<"  Aby wprowadzic liczbe do wyniku wpisz liczbe i potwierdz klawiszem ENTER\n";
	cout<<"  Aby wykonac operation na wyniku wprowadz symbol dzialania * / + -\n";
	cout<<"  oraz potwierdz klawiszem ENTER\n";
	cout<<"  Aby dodac lub odjac aktualny result od komorki pamieci\n";
        cout<<"  wpisz \"m[rn_kom]+\" \"m[nr_kom]-\" np. \"m10+\".\n";
        cout<<"  \"m[nr_kom]r\" zeruje komorke pamieci np. \"m10r\".\n";
        cout<<"  Aby wczytac wartosc komorki pamieci do wyniku,\n";
        cout<<"  wpisz \"m[rn_kom]d\" np. \"m10d\".\n\n";
	if(showMem)
        for (int i = 0; i<cells; i++) cout << " Pamiec m" << i << ": " << wartosci[i] << endl;
	cout << "\n"
		" result: " << result << "\n"
		">";
}

void Calc::operation() {
	string input = "";
	bool exit = 0;
	while (!exit) {
		show();
		cin >> input;
		int dl = input.length();
		if (input == "x") exit = 1;
		else if (input == "+") result += appendEquation();
		else if (input == "-") result -= appendEquation();
		else if (input == "*") result *= appendEquation();
		else if (input == "/") result /= appendEquation(1);
		else if (input[0] == 'm') {
			if(input[dl-1] == 'd'){
                result = getCell(stringToInt(input.substr(1, dl-2)));
        }
        else accessMemory(input);
		}
		else if (input == "c") result = 0;
		else result = stringToDouble(input);
	}
}

void Calc::start() {
	createMemory();
	operation();
}
