//
// Created by Leandrinho on 20.11.2021.
//

#ifndef INC_06_CRIBLE_UTILITIES_H
#define INC_06_CRIBLE_UTILITIES_H

/**
 *
 * @param boolTable
 * @param arrSize
 * @param defaultValue
 */
void initArrayWithDefault(bool boolTable[], size_t arrSize, bool defaultValue);

/**
 *
 * @param boolTt
 * @param arrSize
 * @param startsAt
 */
void initArrayWithAscendingOrder(unsigned boolTt[], size_t arrSize,
											size_t startsAt);

/**
 *
 * @param array
 * @param arrSize
 * @param nbCol
 * @param colWidth
 */
void displayArray(const unsigned array[], size_t arrSize, unsigned nbCol,
						int colWidth);

/**
 *
 * @param array
 * @param arrSize
 * @param nbCol
 * @param colWidth
 * @param valueWhenFalse
 * @param valueWhenTrue
 */
void displayArray(const bool array[], size_t arrSize, unsigned nbCol,
						int colWidth,
						char valueWhenFalse = '0', char valueWhenTrue = '1');

#endif //INC_06_CRIBLE_UTILITIES_H
