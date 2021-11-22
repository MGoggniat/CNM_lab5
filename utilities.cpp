/*
-----------------------------------------------------------------------------------
File name     : utilities.cpp
Author(s)     : Leandro Saraiva Maia, Miguel Jalube
Creation date : 18.11.2021

Description   : See header comment of utilites.h
Remark(s)     : Mr. Breguet said to leave the warnings of the assert checking the
                array

Compiler      : Mingw-w64 g++ 11.1.0
-----------------------------------------------------------------------------------
*/

#include "utilities.h"       // Prototypes
#include <cmath>
#include <cstdlib>           // Required for size_t
#include <iostream>          // Required for cout
#include <iomanip>           // Required for setw
#include <cassert>           // Required for asserts

using namespace std;

unsigned getNumberOfDigits(const unsigned number){
   return number > 0u ? unsigned(log10(double(number))) + 1u : 1u;
}

// We could imagine an overload for other data types
void setAllElementsInArray(bool arrayToSet[], const size_t arrSize,
                           const bool defaultValue) {
   // Check if array is not null
   assert(arrayToSet != nullptr);
   for (size_t i = 0ull; i < arrSize; ++i) {
      arrayToSet[i] = defaultValue;
   }
}

void setArrayWithAscendingOrder(unsigned arrayToSet[], const size_t arrSize,
                                const size_t startsAt = 0ull) {
   // Check if array is not null
   assert(arrayToSet != nullptr);
   for (size_t i = 0ull; i < arrSize; ++i) {
      arrayToSet[i] = unsigned(i + startsAt);
   }
}

//colWidth is not an unsigned because there would be implicit conversion with setw
void displayArrayAsTable(const unsigned array[], const size_t arrSize,
                         const unsigned nbCol, const int colWidth) {
   // Check if array is not null
   assert(array != nullptr);
   for (size_t i = 0ull; i < arrSize; ++i) {
      cout << setw(colWidth) << array[i];
      // Add new line on end of row
      if ((i + 1ull) % (unsigned long long)nbCol == 0ull && i != arrSize - 1ull)
         cout << endl;
   }
}

void displayArrayAsTable(const bool array[], const size_t arrSize,
                         const unsigned nbCol, const int colWidth,
                         const char valueWhenFalse, const char valueWhenTrue) {
   // Check if array is not null
   assert(array != nullptr);
   for (size_t i = 0ull; i < arrSize; ++i) {
      cout << setw(colWidth) << (array[i] ? valueWhenTrue : valueWhenFalse);
      // Add new line on end of row
      if ((i + 1ull) % (unsigned long long)nbCol == 0ull && i != arrSize - 1ull)
         cout << endl;
   }
}