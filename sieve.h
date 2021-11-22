/*
-----------------------------------------------------------------------------------
File name     : sieve.h
Author(s)     : Leandro Saraiva Maia, Miguel Jalube
Creation date : 18.11.2021

Description   : This library computes and display the sieve of Eratosthenes. It is
                only necessary to call sieveRun, as it is the entry point that
                will call the other functions to perform the algorithm.
Remark(s)     :

Compiler      : Mingw-w64 g++ 11.1.0
-----------------------------------------------------------------------------------
*/

#ifndef LAB_06_CRIBLE_SIEVE_H
#define LAB_06_CRIBLE_SIEVE_H

#include <cstdlib>   // Required for size_t

/**
 * Entry point of the library. Handles the variables needed, the computing of the
 * algorithm and the display of the result
 * @param findPrimeUpTo Defines until which integer we search for prime numbers
 */
void sieveRun(unsigned findPrimeUpTo, unsigned primeNumArray[], bool sieveArray[],
              unsigned nbCol = 10u, int colWidth = 2);

/**
 * Computes the algorithm of the sieve of Eratosthenes
 * @param sieveArray Bool array where each index+1 represents an natural number in
 * ascending order
 * @param sieveArraySize Size of the array passed in parameter
 * @param primeArray Array where prime number will be stored. For now, it is only
 * an array containing number in ascending number (starting at 1)
 */
void sieve(bool sieveArray[], std::size_t sieveArraySize);

/**
 * Fill an array with the prime numbers that have been found using the sieve table
 * @param sieveArray Bool array where each index+1 represents an natural number in
 * ascending order. The value set to true are prime and the value set to false are
 * not prime
 * @param sieveArraySize Size of the array passed in parameter
 * @param primeArray The array in which the prime numbers will be stored
 * @return The number of primes found
 */
unsigned extractPrimeNumbers(const bool sieveArray[], std::size_t sieveArraySize,
									  unsigned primeArray[]);

#endif