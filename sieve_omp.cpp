/*
-----------------------------------------------------------------------------------
File name     : main.cpp
Lab name      : "06 Crible" or "Sieve"
Author(s)     : Leandro Saraiva Maia, Miguel Jalube
Creation date : 18.11.2021

Description   : This programs asks the user for an amount of prime numbers to
                find. Then, it uses the sieve of Eratosthenes to compute the
                amount of prime numbers wanted (start from 0 -> amount). Finally,
                it displays sieve table and the prime that have been found.
Remark(s)     : The clion console is a bit bugged and may display values
                incorrectly, it is better to use an external console.
                This program is meant to be used only in english, there are no
                constants sets to facilitate potential translation.

 
Compiler      : Mingw-w64 g++ 11.1.0
-----------------------------------------------------------------------------------
*/

#include <cstdlib>   
#include <iostream>  
#include <limits>    
#include <string>    
#include <iomanip>   
#include <cassert>   
#include <cmath>     
#include <time.h>
#include <omp.h>           

using namespace std;

unsigned getNumberOfDigits(const unsigned long long number);
void setAllElementsInArray(bool arrayToSet[], const size_t arrSize,
                           const bool defaultValue);
void setArrayWithAscendingOrder(unsigned long long arrayToSet[], const size_t arrSize,
                                const size_t startsAt);
void displayArrayAsTable(const unsigned long long array[], const size_t arrSize,
                         const unsigned nbCol, const int colWidth);
void sieve(bool sieveArray[], size_t sieveArraySize);
unsigned long long extractPrimeNumbers(const bool sieveArray[], size_t sieveArraySize,
								     unsigned long long primeArray[]);

int main(int argc, char* argv[]) {

   clock_t start_time = clock();

	//---------- Variables and constants ----------
	const unsigned long long   MIN_PRIME_UP_TO =                2;
   const unsigned long long   MAX_PRIME_UP_TO =                100000; // >100000 may cause memory issues
   const unsigned             RESULT_NB_COL =                  20u;
	unsigned long long         primeNumArray[MAX_PRIME_UP_TO];
   unsigned long long         numToCheckForPrime;
	unsigned long long         numOfPrimeNumbers;
	bool                       sieveArray[MAX_PRIME_UP_TO];
   const unsigned             NUM_THREADS =                    4;

   omp_set_num_threads(NUM_THREADS);

   if(argc != 2 || stoull(argv[1]) < MIN_PRIME_UP_TO || stoull(argv[1]) > MAX_PRIME_UP_TO){
      cout << "Usage : ./sieve <number>" << endl;
      cout << MIN_PRIME_UP_TO << " < [number] < " << MAX_PRIME_UP_TO << endl;
      return EXIT_FAILURE;
   }

   numToCheckForPrime = stoull(argv[1]);

   //---------- Initialization ----------
   setArrayWithAscendingOrder(primeNumArray, numToCheckForPrime, 1);
   setAllElementsInArray(sieveArray, (size_t)numToCheckForPrime, true);

   clock_t init_time = clock();

   //---------- Computes prime numbers with Eratosthenes sieve ----------
   sieve(sieveArray, numToCheckForPrime);

   clock_t sieve_time = clock();

   numOfPrimeNumbers = extractPrimeNumbers(sieveArray, numToCheckForPrime, primeNumArray);

   clock_t extract_time = clock();

   //---------- Display the sieve results ----------
   cout << endl << numOfPrimeNumbers << " prime number(s) found up to " << numToCheckForPrime << endl;
   displayArrayAsTable(primeNumArray, numOfPrimeNumbers, RESULT_NB_COL, int(getNumberOfDigits(MAX_PRIME_UP_TO)));
   cout << endl;

   clock_t display_time = clock();

   //---------- Display time measures --------------
   printf("============= Time measures ===============\n");
   printf("Init time :     %f\n", (double)(init_time - start_time) / CLOCKS_PER_SEC);
   printf("Sieve time :    %f\n", (double)(sieve_time - init_time) / CLOCKS_PER_SEC);
   printf("Extract time :  %f\n", (double)(extract_time - sieve_time) / CLOCKS_PER_SEC);
   printf("Display time :  %f\n", (double)(display_time - extract_time) / CLOCKS_PER_SEC);
   printf("Total time :    %f\n", (double)(display_time - start_time) / CLOCKS_PER_SEC);

   return EXIT_SUCCESS;
}

unsigned getNumberOfDigits(const unsigned long long number){
   return number > 0 ? unsigned(log10(double(number))) + 1 : 1;
}

// We could imagine an overload for other data types
void setAllElementsInArray(bool arrayToSet[], const size_t arrSize,
                           const bool defaultValue) {
   // Check if array is not n
   assert(arrayToSet != nullptr);
   for (size_t i = 0; i < arrSize; ++i) {
      arrayToSet[i] = defaultValue;
   }
}

void setArrayWithAscendingOrder(unsigned long long arrayToSet[], const size_t arrSize,
                                const size_t startsAt = 0) {
   // Check if array is not n
   assert(arrayToSet != nullptr);
   for (size_t i = 0; i < arrSize; ++i) {
      arrayToSet[i] = i + startsAt;
   }
}

void displayArrayAsTable(const unsigned long long array[], const size_t arrSize,
                         const unsigned nbCol, const int colWidth) {
   assert(array != nullptr);
   for (size_t i = 0; i < arrSize; ++i) {
      cout << setw(colWidth) << array[i];
      if ((i + 1) % (unsigned long long)nbCol == 0 && i != arrSize - 1)
         cout << endl;
   }
}

void displayArrayAsTable(const bool array[], const unsigned long arrSize,
                         const unsigned nbCol, const int colWidth,
                         const char valueWhenFalse, const char valueWhenTrue) {
   assert(array != nullptr);
   for (size_t i = 0; i < arrSize; ++i) {
      cout << setw(colWidth) << (array[i] ? valueWhenTrue : valueWhenFalse);
      if ((i + 1) % (unsigned long long)nbCol == 0 && i != arrSize - 1)
         cout << endl;
   }
}

void sieve(bool sieveArray[], size_t sieveArraySize){
   assert(sieveArray != nullptr && sieveArray != nullptr);
	sieveArray[0] = false;
   unsigned long long checkNumber;
   unsigned long long currentNumber;

   #pragma omp parallel for schedule(dynamic)
   for (size_t i = 0; i < sieveArraySize; ++i) {
      checkNumber = i + 1;
      for (size_t j = checkNumber; j < sieveArraySize && sieveArray[i]; ++j) {
         currentNumber = j + 1;
         if(currentNumber % (checkNumber) == 0){
			   sieveArray[j] = false;
         }
      }
   }

}

unsigned long long extractPrimeNumbers(const bool sieveArray[], size_t sieveArraySize,
								     unsigned long long primeArray[]) {
	unsigned long long numOfPrimeNumbers = 0;
	for (size_t i = 0; i < sieveArraySize; ++i) {
		if (sieveArray[i]) {
			primeArray[numOfPrimeNumbers++] = i + 1;
		}
	}

	return numOfPrimeNumbers;
}