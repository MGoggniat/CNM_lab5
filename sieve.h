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
 * @param nbCol
 * @return
 */
void displaySieve(bool sieveTable[], size_t sieveTableSize, unsigned nbCol);
/**
 *
 * @param sieveTable
 * @param sieveTableSize
 * @param primeTable
 * @param primeTableSize
 * @return
 */
void sieve(bool sieveTable[], size_t sieveTableSize, unsigned primeTable[],
           size_t primeTableSize);
void displayResults();

#endif //INC_06_CRIBLE_SIEVE_H

