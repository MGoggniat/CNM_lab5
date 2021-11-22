/*
-----------------------------------------------------------------------------------
File name     : sieve.cpp
Author(s)     : Leandro Saraiva Maia, Miguel Jalube
Creation date : 18.11.2021

Description   : See header comment of sieve.h
Remark(s)     :

Compiler      : Mingw-w64 g++ 11.1.0
-----------------------------------------------------------------------------------
*/

#include <iomanip>       // Required for setw
#include <cassert>       // Required for asserts
#include "sieve.h"       // Prototypes

using namespace std;

void sieve(bool sieveArray[], size_t sieveArraySize){
   // Check if array is not null
   assert(sieveArray != nullptr && sieveArray != nullptr);
	sieveArray[0] = false; // Set 1 as not a prime number

   // The number for who we are searching for multiples
   unsigned checkNumber;
   // The number being checked if it's divisible by checkNumber
   unsigned currentNumber;

   for (size_t i = 0ull; i < sieveArraySize; ++i) {
      checkNumber = unsigned(i) + 1u;

      // Each number from checkNumber to size-1 and where sieveArray[i] is true will
      // be checked, so only prime numbers can enter this loop.
      for (size_t j = checkNumber; j < sieveArraySize && sieveArray[i]; ++j) {
         currentNumber = unsigned(j) + 1u;

         // Could not simplify this condition due to the loop resetting
         // already ignored numbers (false) to true
         if(currentNumber % checkNumber == 0u){
            // set to false every multiple of checkNumber
				sieveArray[j] = false;
         }
      }
   }
}

unsigned extractPrimeNumbers(const bool sieveArray[], size_t sieveArraySize,
								     unsigned primeArray[]) {
	unsigned numOfPrimeNumbers = 0u;

	// We check all the values in the sieve table
	for (size_t i = 0ull; i < sieveArraySize; ++i) {
		// If the current value was not discarded during the Eratosthenes sieve
		if (sieveArray[i]) {
			// Add the current num to the list of primes and increment the num of prime
			primeArray[numOfPrimeNumbers++] = unsigned(i) + 1u;
		}
	}

	return numOfPrimeNumbers;
}