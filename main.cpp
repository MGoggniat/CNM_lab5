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

#include <cstdlib>             // Required for EXIT_SUCCESS
#include <iostream>            // Required for cout
#include <limits>              // Required for numeric_limits<...>
#include <string>              // Required for the use of strings
#include "sieve.h"             // Prototypes for the sieving functions
#include "arrayManip.h"        // Prototypes for the array manipulations
#include "inputValidation.h"   // Required to get input

using namespace std;

int main() {
	//---------- Variables and constants ----------
	const unsigned MIN_PRIME_UP_TO = 2u,
                  MAX_PRIME_UP_TO = 100u;    // must be <= 100000
   const char     VALUE_FALSE     = 'X',
                  VALUE_TRUE      = 'O';
	unsigned       primeNumArray[MAX_PRIME_UP_TO],
                  numToCheckForPrime;
	bool           sieveArray[MAX_PRIME_UP_TO];

   const unsigned NB_COL      = 10u;
   const int      COL_WIDTH   = 2;

	//---------- User input ----------
	cout << "Hi, this program computes the sieve of Eratosthenes to find prime "
	     << "numbers." << endl << "Please enter the numbers you want to check for"
        << "prime [" << MIN_PRIME_UP_TO << ".." << MAX_PRIME_UP_TO << "] :";
   // TODO: change everything
	numToCheckForPrime = getInput(MIN_PRIME_UP_TO, MAX_PRIME_UP_TO);

   //---------- Initialization ----------
   setArrayWithAscendingOrder(primeNumArray, numToCheckForPrime, 1);
   setAllElementsInArray(sieveArray, numToCheckForPrime, true);

   //---------- Display empty sieve table ----------
   cout << endl << "Table initialization : " << endl;
   displayArrayAsTable(sieveArray, numToCheckForPrime, NB_COL, COL_WIDTH,
                       VALUE_FALSE, VALUE_TRUE);
   cout << endl;

   //---------- Computes prime numbers with Eratosthenes sieve ----------
   sieve(sieveArray, numToCheckForPrime);
   unsigned numOfPrimeNumbers = extractPrimeNumbers(sieveArray, numToCheckForPrime,
                                                    primeNumArray);

   //---------- Display the sieve table ----------
   cout << endl << "Sieving of the table : " << endl;
   displayArrayAsTable(sieveArray, numToCheckForPrime, NB_COL, COL_WIDTH,
                       VALUE_FALSE, VALUE_TRUE);
   cout << endl;

   //---------- Display the sieve results ----------
   cout << endl << numOfPrimeNumbers << " prime number(s) found up to "
        << numToCheckForPrime << endl;
   displayArrayAsTable(primeNumArray, numOfPrimeNumbers, 5u, 4);
   cout << endl;

   //---------- End of program ----------
   cout << "Press ENTER to quit.";
   cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Empty buffer

   return EXIT_SUCCESS;
}