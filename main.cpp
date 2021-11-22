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
                This program is meant to be use only in english, there are no
                constants sets to facilitate potential translation.

 
Compiler      : Mingw-w64 g++ 11.1.0
-----------------------------------------------------------------------------------
*/

#include <cstdlib>             // Required for EXIT_SUCCESS
#include <iostream>            // Required for cout
#include <limits>              // Required for numeric_limits<...>
#include <string>              // Required for the use of strings
#include "sieve.h"             // Prototypes
// Note that this library uses another naming convention that we will not use here
// (snake_case instead of camelCase)
#include "input_validation.h"  // Required to get input

using namespace std;

int main() {
	//---------- Variables and constants ----------
	const unsigned MIN_PRIME_UP_TO = 2u, MAX_PRIME_UP_TO = 100u;
	unsigned primeNumArray[MAX_PRIME_UP_TO], numToCheckForPrime;
	bool sieveArray[MAX_PRIME_UP_TO];

	//---------- User input ----------
	cout << "Hi, this program computes the sieve of Eratosthenes to find prime "
	     << "numbers. Please enter the numbers you want to check for prime" <<  "["
		  << MIN_PRIME_UP_TO << ".." << MAX_PRIME_UP_TO << "] :";
	numToCheckForPrime = get_input(MIN_PRIME_UP_TO, MAX_PRIME_UP_TO);

	//---------- Compute and display result of the sieve of Eratosthenes ----------
	sieveRun(numToCheckForPrime, primeNumArray, sieveArray);

   //---------- End of program ----------
   cout << "Press ENTER to quit.";
   cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Empty buffer

   return EXIT_SUCCESS;
}