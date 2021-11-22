/*
-----------------------------------------------------------------------------------
File name     : sieve.cpp
Author(s)     : Leandro Saraiva Maia, Miguel Jalube
Creation date : 18.11.2021

Description   : See header comment of the .h file
Remark(s)     :

Compiler      : Mingw-w64 g++ 11.1.0
-----------------------------------------------------------------------------------
*/

#include <iomanip>       // Required for setw
#include <iostream>      // Required for cout
#include <string>        // Required for const msgs
#include <cassert>       // Required for asserts
#include "sieve.h"       // Prototypes
#include "arrayManip.h"  // Required to set bool table to true

using namespace std;

void sieve(bool sieveArray[], size_t sieveArraySize){
   // Check if array is not null
   assert(sieveArray != nullptr && sieveArray != nullptr);
	sieveArray[0] = false; // We set 1 as not a prime number

   // The number for who we are searching for multiples
   unsigned checkNumber;
   // The number being checked if it is divisible by checkNumber
   unsigned currentNumber;

   for (size_t i = 0ull; i < sieveArraySize; ++i) {
      checkNumber = i+1ull;

      // Each number from cheknumber to size-1 and not false will be checked
      for (size_t j = checkNumber; j < sieveArraySize && sieveArray[i]; ++j) {
         currentNumber = j+1ull;

         // Could not simplify this condition due to the loop resetting
         // already ignored numbers (false) to true
         if(currentNumber % checkNumber == 0u){
            // set to false every multiple of checkNumber
				sieveArray[j] = false;
         }
      }
   }
}

// TODO: Comment function
unsigned extractPrimeNumbers(const bool sieveArray[], size_t sieveArraySize,
								     unsigned primeArray[]) {
	unsigned numOfPrimeNumbers = 0u;
	for (size_t i = 0ull; i < sieveArraySize; ++i) {
		if (sieveArray[i]) {
			primeArray[numOfPrimeNumbers++] = unsigned(i) + 1u;
		}
	}

	return numOfPrimeNumbers;
}