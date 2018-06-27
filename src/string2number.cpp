#include <string>
#include <sstream>
#include "string2number.h"

using namespace std;

double stringToDouble(string number) {
	istringstream os(number);
	double d;
	os >> d;
	return d;
}

int stringToInt(string number) {
	istringstream os(number);
	int i;
	os >> i;
	return i;
}
