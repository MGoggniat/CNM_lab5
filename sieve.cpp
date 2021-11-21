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

#include <iomanip>      // Required for setw
#include <iostream>     // Required for cout
#include <string>       // Required for const msgs
#include "sieve.h"      // Prototypes
#include "arrayManip.h"  // Required to set bool table to true

using namespace std;

void sieveRun(const unsigned findPrimeUpTo, unsigned primeNumArray[], bool
sieveArray[], unsigned nbCol, int colWidth) {
	const string INIT_MSG = "Table initialization";
	const string SIEVE_START_MSG = "Sieving of the table";
	const string RESULT_MSG_1 = "There are ";
	const string RESULT_MSG_2 = " prime numbers up to ";

	//---------- Initialization ----------
	setArrayWithAscendingOrder(primeNumArray, findPrimeUpTo, 1);
	setAllElementsInArray(sieveArray, findPrimeUpTo, true);

	//---------- Display empty sieve table ----------
	cout << endl << "Table initialization : " << endl;
	displayArrayAsTable(sieveArray, findPrimeUpTo, nbCol, colWidth, 'X', 'O');
	cout << endl;

	//---------- Computes prime numbers with Eratosthenes sieve ----------
	sieve(sieveArray, findPrimeUpTo, primeNumArray);
	unsigned numOfPrimeNumbers = extractPrimeNumbers(sieveArray, findPrimeUpTo,
																	 primeNumArray);

	//---------- Display the sieve table ----------
	cout << endl << "Sieving of the table : " << endl;
	displayArrayAsTable(sieveArray, findPrimeUpTo, nbCol, colWidth, 'X', 'O');
	cout << endl;

	//---------- Display the sieve results ----------
	cout << endl << RESULT_MSG_1 << numOfPrimeNumbers << RESULT_MSG_2
		  << findPrimeUpTo << endl;
	displayArrayAsTable(primeNumArray, numOfPrimeNumbers, 5u, 4);
	cout << endl;
}

void sieve(bool sieveArray[], size_t sieveArraySize, const unsigned primeArray[]){
	sieveArray[0] = false; // We set 1 as not a prime number

   for (size_t i = 0ull; i < sieveArraySize; ++i) {
      unsigned nb = primeArray[i];
      for (size_t j = i+1ull; j < sieveArraySize && sieveArray[i]; ++j) {
         if(primeArray[j] % nb == 0){
				sieveArray[j] = false;
         }
      }
   }
}

unsigned extractPrimeNumbers(const bool sieveArray[], size_t sieveArraySize,
								     unsigned primeArray[]) {
	unsigned numOfPrimeNumbers = 0;

	for (size_t i = 0ull; i < sieveArraySize; ++i) {
		if (sieveArray[i]) {
			primeArray[numOfPrimeNumbers++] = unsigned(i) + 1u;
		}
	}

	return numOfPrimeNumbers;
}