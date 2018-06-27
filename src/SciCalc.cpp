#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>
#include "SciCalc.h"

using namespace std;


SciCalc::SciCalc():Calc(){
    this->result = 0;
    this->pos = 0;
    this->equation.clear();
    this->answer.clear();
    this->exit = false;
    this->reset = false;
}

void SciCalc::show(){
    system("cls");
    cout<<"Kalkulator Fake Naukowy z pamiecia\n\n";
    cout<<"  Kolejnosc dzialan: - > + > % > ^ > / > *\n";
    cout<<"  dzielenie modulo zaokraglane do liczb calkowitych.\n";
    cout<<"  Akceptuje dodatnie potegi calkowite.\n";
    cout<<"  Flagi: wyjscie -> \"x\" ,zerowanie wyniku -> \"c\".\n\n";
    cout<<"  Wyswietlanie/ukrywanie komorek pamieci -> \"mv\".\n";
    cout<<"  Wpisz cale rownanie, po czym potwierdz klawiszem ENTER.\n";
    cout<<"  Aby dodac lub odjac aktualny wynik od komorki pamieci\n";
    cout<<"  wpisz \"m[rn_kom]+\" \"m[nr_kom]-\" np. \"m10+\".\n";
    cout<<"  \"m[nr_kom]r\" zeruje komorke pamieci np. \"m10r\".\n";
    cout<<"  Aby uzyc wartosci komorki pamieci w rownaniu wpisz \"m[nr_kom]d\"\n";
    cout<<"  np. \"1+2*m10d/4\".\n\n";
     if(showMem)
        for (int i = 0; i<cells; i++) cout << " Pamiec m" << i << ": " << values[i] << endl;
    cout<<"\nROWNANIE: "<<answer<<endl;
    cout<<"wynik: "<<result<<endl;
}

void SciCalc::getEquation(){
	pos = 0;
	equation.clear();
	show();
	cout<<">";
	cin >> equation;
	answer = equation;
}

bool SciCalc::isDigit(unsigned char character, string addons = "") {
	bool retVal = 0;
	string allowed = "0123456789" + addons;
	for (unsigned int i = 0; i<allowed.length(); i++) {
		if (character == allowed[i]) retVal = 1;
	}

	return retVal;
}

string SciCalc::splitString() {
	string retVal;
	retVal.clear();
	int i = pos;
	if (equation.empty()) {
		getEquation();
	}

	else if (pos >= equation.length()) {
		equation.clear();
		retVal = "s";
	}

	else if(equation[i] == 'm'){
        int j = 1;
        while(equation[i+j]!='d' &&
              equation[i+j]!='r' &&
              equation[i+j]!='+' &&
              equation[i+j]!='-' &&
              equation[i+j]!='v' )
              j++;
        if(equation[i+j]=='d'){
            retVal = equation.substr(i,j+1);
            pos = i + j + 1;
        }
        else if(equation[i+j]=='r' ||
                equation[i+j]=='+' ||
                equation[i+j]=='-' ||
                equation[i+j]=='v'){
            accessMemory(equation.substr(i,j+1));
            retVal = "s";
            equation.clear();
            answer.clear();
            reset = true;
        }
	}

	else if (equation == "x") {
		retVal = "s";
		exit = true;
		equation.clear();
		answer.clear();
		reset = true;
	}

	else if (equation == "c") {
		retVal = "s";
		equation.clear();
		answer.clear();
		reset = true;
	}

	else if (equation[i] == '+' ||
             equation[i] == '*' ||
             equation[i] == '/' ||
             equation[i] == '^' ||
             equation[i] == '%') {
		retVal = equation.substr(i, 1);
		pos += 1;
	}
	else if (equation[i] == '-') {
		if (i>0 && isDigit(equation[i - 1])) {
			retVal = equation.substr(i, 1);
			pos++;
		}
		else {
			i++;
			while (isDigit(equation[i], ".")) i++;
			retVal = equation.substr(pos, i - pos);
			pos += i - pos;
		}
	}
	else {
		while (isDigit(equation[i], ".")) i++;
		retVal = equation.substr(pos, i - pos);
		pos += i - pos;
	}

	return retVal;
}

bool SciCalc::isNumber(string inVal) {
	string firstChar = "-0123456789";
	string nextChar = ".0123456789";
	bool retVal = 1;
	unsigned int dots = 0, i = 0;
	if (inVal[0] == '-') {
		if (inVal.length() <= 1) retVal = 0;
		else if (inVal[1] == '.') retVal = 0;
	}

	while (retVal&&i<inVal.length()) {
		retVal = 0;
		string allowed = nextChar;
		if (!i) allowed = firstChar;
		for (unsigned int j = 0; j<allowed.length(); j++) {
			if (inVal[i] == allowed[j]) retVal = 1;
		}
		if (inVal[i] == '.') dots++;
		if (dots>1) retVal = 0;
		i++;
	}

	return retVal;
}

double SciCalc::subtract(char &character){
    string inVal = "cos";
    double result = 0, number = 0;
    while(inVal[0]!='+' && inVal[0]!='*' && inVal[0]!='s' && inVal[0]!='/' && inVal[0]!='%' && inVal[0]!='^'){
        inVal.clear();
        inVal = splitString();
        if(isNumber(inVal)) result = stringToDouble(inVal);
        else if(inVal[0] == 'm') result = getCell(stringToInt(inVal.substr(1, inVal.length()-2)));
        else if(inVal[0] == '-'){
            string inputTmp = splitString();
            if(inputTmp[0] == 'm') number = getCell(stringToInt(inputTmp.substr(1, inputTmp.length()-2)));
            else number = stringToDouble(inputTmp);
            result = result - number;
        }
    }

    character = inVal[0];

    return result;
}

double SciCalc::add(char &secChar){
    char character = 'v';
    double result = subtract(character);
    while(character == '+'){
        result = result + subtract(character);
    }
    secChar = character;

    return result;
}

double SciCalc::modulo(char &secChar){
    char character = 'v';
    double result = add(character);
    while(character == '%'){
        result = (int)result % (int)add(character);
    }
    secChar = character;

    return result;
}

double SciCalc::raiseTo(char &secChar){
    char character = 'v';
    double result = modulo(character);
    while(character == '^'){
        double pot = modulo(character);
        double wykl = result;
        for(int i=1;i<(int)pot;i++) result *= wykl;
        if(pot == 0) result = 1;
    }
    secChar = character;

    return result;
}

double SciCalc::divide(char &secChar){
    char character = 'v';
    double result = raiseTo(character);
    while(character == '/'){
        double dividend = raiseTo(character);
        if(dividend == 0){
            result = 0;
            character = 's';
        }
        else result = result/dividend;
    }
    secChar = character;

    return result;
}

double SciCalc::multiply(){
    char character = 'v';
    double result = divide(character);
    while(character == '*'){
        result = result * divide(character);
    }

    return result;
}

void SciCalc::start(){
    createMemory();
    while(!exit){
        result = multiply();
        if(reset){
            result = 0;
            reset = false;
        }
        show();
    }
}
