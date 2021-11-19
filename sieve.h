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
void displaySieve(bool sieveTable[], std::size_t sieveTableSize, unsigned
nbCol);
/**
 *
 * @param sieveTable
 * @param sieveTableSize
 * @param primeTable
 * @param primeTableSize
 * @return
 */
void sieve(bool sieveTable[], std::size_t sieveTableSize, const unsigned
primeTable[]);
void displayResults();

#endif //INC_06_CRIBLE_SIEVE_H

