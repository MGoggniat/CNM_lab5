//
// Created by Leandrinho on 20.11.2021.
//

#include <cstdlib>      // Required for size_t
#include <iostream>     // Required for cout
#include <iomanip>      // Required for setw
#include "utilities.h"  // Prototypes

using namespace std;

// We could imagine an overload for other data types
void initArrayWithDefault(bool boolTable[], size_t arrSize, bool defaultValue
=true) {
	for (size_t i = 0ull; i < arrSize; ++i) {
		boolTable[i] = defaultValue;
	}
}

void initArrayWithAscendingOrder(unsigned boolTt[], size_t arrSize,
											size_t startsAt = 0) {
	for (size_t i = 0; i < arrSize; ++i) {
		boolTt[i] = (unsigned)(i + startsAt);
	}
}

//colWidth is not an unsigned because there would be implicit conversion with setw
void displayArray(const unsigned array[], const size_t arrSize, const unsigned nbCol,
						const int colWidth) {
	for (size_t i = 0ull; i < arrSize; ++i) {
		cout << setw(colWidth) << array[i];
		if ((i+1) % nbCol == 0) cout << endl;
	}
}

void displayArray(const bool array[], const size_t arrSize, const unsigned nbCol,
						const int colWidth,
						const char valueWhenFalse, const char valueWhenTrue) {
	for (size_t i = 0ull; i < arrSize; ++i) {
		cout << setw(colWidth) << (array[i] ? valueWhenTrue : valueWhenFalse);
		if ((i+1) % nbCol == 0) cout << endl;
	}
}