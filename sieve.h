//
// Created by migue on 18.11.2021.
//

#ifndef INC_06_CRIBLE_SIEVE_H
#define INC_06_CRIBLE_SIEVE_H

#include <cstdlib>

/**
 *
 * @param size
 * @return
 */
void sieveRun(unsigned size);

/**
 *
 * @param sieveTable
 * @param sieveTableSize
 * @param primeTable
 * @return
 */
void sieve(bool sieveTable[], std::size_t sieveTableSize,
			  const unsigned primeTable[]);

/**
 *
 * @param sieveArray
 * @param sieveArraySize
 * @param primeArray
 * @return
 */
unsigned extractPrimeNumbers(const bool sieveArray[], size_t sieveArraySize,
									  unsigned primeArray[]);

#endif //INC_06_CRIBLE_SIEVE_H

