/*
-----------------------------------------------------------------------------------
File name     : arrayManip.cpp
Author(s)     : Leandro Saraiva Maia, Miguel Jalube
Creation date : 20.11.2021

Description   : See header comment of the .h file
Remark(s)     : Mr. Breguet said to leave the warnings of the assert checking the
                array

Compiler      : Mingw-w64 g++ 11.1.0
-----------------------------------------------------------------------------------
*/

#include <cstdlib>      // Required for size_t
#include <iostream>     // Required for cout
#include <iomanip>      // Required for setw
#include <cassert>      // Required for asserts
#include "arrayManip.h" // Prototypes

using namespace std;

// We could imagine an overload for other data types
void setAllElementsInArray(bool arrayToSet[], size_t arrSize, bool defaultValue) {
   // Check if array is not null
   assert(arrayToSet != nullptr);
	for (size_t i = 0ull; i < arrSize; ++i) {
		arrayToSet[i] = defaultValue;
	}
}

void setArrayWithAscendingOrder(unsigned arrayToSet[], size_t arrSize,
										  size_t startsAt = 0ull) {
   // Check if array is not null
   assert(arrayToSet != nullptr);
	for (size_t i = 0ull; i < arrSize; ++i) {
		arrayToSet[i] = (unsigned)(i + startsAt);
	}
}

//colWidth is not an unsigned because there would be implicit conversion with setw
void displayArrayAsTable(const unsigned array[], size_t arrSize, unsigned nbCol,
								 int colWidth) {
   // Check if array is not null
   assert(array != nullptr);
	for (size_t i = 0ull; i < arrSize; ++i) {
		cout << setw(colWidth) << array[i];
		if ((i+1ull) % (unsigned long long)nbCol == 0ull) cout << endl;
	}
}

void displayArrayAsTable(const bool array[], size_t arrSize, unsigned nbCol,
								 int colWidth,
								 char valueWhenFalse, char valueWhenTrue) {
   // Check if array is not null
   assert(array != nullptr);
	for (size_t i = 0ull; i < arrSize; ++i) {
		cout << setw(colWidth) << (array[i] ? valueWhenTrue : valueWhenFalse);
		if ((i+1ull) % (unsigned long long)nbCol == 0ull) cout << endl;
	}
}