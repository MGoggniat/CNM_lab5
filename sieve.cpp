//
// Created by migue on 18.11.2021.
//
#include <iomanip>      // Required for setw
#include <iostream>     // Required for cout
#include <string>       // Required for const msgs
#include "sieve.h"      // Prototypes
#include "utilities.h"  // Required to set bool table to true

using namespace std;

void sieveRun(const unsigned arraySize, unsigned primeNumArray[], bool
sieveArray[], unsigned nbCol, int colWidth){
   const string INIT_MSG          = "Table initialization";
   const string SIEVE_START_MSG   = "Sieving of the table";
   const string RESULT_MSG_1      = "There are ";
   const string RESULT_MSG_2      = " prime numbers from";
   const string RESULT_MSG_3      = " to ";

   //----------------------------------------------------
   // Initialisation
   //----------------------------------------------------
	initArrayWithAscendingOrder(primeNumArray, arraySize, 1);
	initArrayWithDefault(sieveArray, arraySize, true);

   //----------------------------------------------------
   // Display the table
   //----------------------------------------------------
	cout << endl << INIT_MSG << " : " << endl;
	displayArray(sieveArray, arraySize, nbCol, colWidth, 'X', 'O');
	cout << endl;

   //----------------------------------------------------
   // Sieve
   //----------------------------------------------------
	sieve(sieveArray, arraySize, primeNumArray);
	unsigned numOfPrimeNumbers = extractPrimeNumbers(sieveArray, arraySize, primeNumArray);

   //----------------------------------------------------
   // Display the sieve results
   //----------------------------------------------------
	cout << endl << SIEVE_START_MSG << " : " << endl;
	displayArray(sieveArray, arraySize, nbCol, colWidth, 'X', 'O');
	cout << endl;

	cout << endl << RESULT_MSG_1 << numOfPrimeNumbers << RESULT_MSG_2
   << " 1 " << RESULT_MSG_3
	<< arraySize << endl;
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