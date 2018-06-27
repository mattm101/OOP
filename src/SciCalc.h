#ifndef SCICALC_H
#define SCICALC_H

#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include "Calc.h"
#include "string2number.h"

using namespace std;

class SciCalc :public Calc {
    string equation;
    string answer;
	unsigned int pos;
	bool exit;
	bool reset;

    friend double stringToDouble(string);
    friend int stringToInt(string);

    void getEquation();
    void show();
    bool isDigit(unsigned char, string);
    string splitString();
    bool isNumber(string);
    double subtract(char &);
    double add(char &);
    double modulo(char &);
    double raiseTo(char &);
    double divide(char &);
    double multiply();

public:
    SciCalc();
    void start();

};
#endif // SCICALC_H




