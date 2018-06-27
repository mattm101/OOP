#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <string>
#include <sstream>
#include <windows.h>

using namespace std;

class Memory {
protected:
	int cells;
	double *values;

	Memory();
	void createMemory(int);
	void removeMemory();
	double getCell(int);
	void writeCell(int, double);
	void addToCell(int, double);
	void substractFromCell(int, double);
	void clearCell(int);
public:
	virtual void start() = 0;
	virtual ~Memory();
};

#endif // MEMORY_H






