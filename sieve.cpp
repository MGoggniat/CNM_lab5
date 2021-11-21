//
// Created by migue on 18.11.2021.
//
#include <iomanip>      // Required for setw
#include <iostream>     // Required for cout
#include "sieve.h"      // Prototypes
#include "utilities.h"  // Required to set bool table to true

using namespace std;

void sieveRun(const unsigned size){
   //----------------------------------------------------
   // Initialisation
   //----------------------------------------------------
   unsigned primeNumArray[100];
	initArrayWithAscendingOrder(primeNumArray, size, 1);

   bool sieveArray[100];
	initArrayWithDefault(sieveArray, size, true);

   //----------------------------------------------------
   // Display the table
   //----------------------------------------------------
	cout << endl << "Table initialization : " << endl;
	displayArray(sieveArray, size, 10u, 2, 'X', 'O');
	cout << endl;

   //----------------------------------------------------
   // Sieve
   //----------------------------------------------------
	sieve(sieveArray, size, primeNumArray);
	unsigned numOfPrimeNumbers = extractPrimeNumbers(sieveArray, size, primeNumArray);

   //----------------------------------------------------
   // Display the sieve results
   //----------------------------------------------------
	cout << endl << "Sieving of the table : " << endl;
	displayArray(sieveArray, size, 10u, 2, 'X', 'O');
	cout << endl;

	cout << endl << "There are " << numOfPrimeNumbers << " prime numbers from 1 to "
	<< size << endl;
	displayArray(primeNumArray, numOfPrimeNumbers, 5u, 4);
	cout << endl;
}

void sieve(bool sieveTable[], size_t sieveTableSize, const unsigned primeTable[]){
	sieveTable[0] = false; // We set 1 as not a prime number

   for (size_t i = 0ull; i < sieveTableSize; ++i) {
      unsigned nb = primeTable[i];
      for (size_t j = i+1ull; j < sieveTableSize && sieveTable[i]; ++j) {
         if(primeTable[j]%nb==0){
            sieveTable[j] = false;
         }
      }
   }
}

unsigned extractPrimeNumbers(const bool sieveArray[], size_t sieveArraySize,
								     unsigned primeArray[]) {
	unsigned j = 0, numOfPrimeNumbers = 0;

	for (size_t i = 0ull; i < sieveArraySize; ++i) {
		if (sieveArray[i]) {
			primeArray[j++] = (unsigned) i+1u;
			++numOfPrimeNumbers;
		}
	}

	return numOfPrimeNumbers;
}