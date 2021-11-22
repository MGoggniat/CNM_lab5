/*
-----------------------------------------------------------------------------------
File name     : utilities.h
Author(s)     : Leandro Saraiva Maia, Miguel Jalube
Creation date : 22.11.2021

Description   : This library is used for utility functions
Remark(s)     :

Compiler      : Mingw-w64 g++ 11.1.0
-----------------------------------------------------------------------------------
*/

#ifndef INC_06_CRIBLE_UTILITIES_H
#define INC_06_CRIBLE_UTILITIES_H

#include <cstdlib>   // Required for size_t

/**
 *
 * @param number number to get digits
 * @return number of digits
 */
unsigned getNumberOfDigits(unsigned number);

/**
 * Sets every element of an array to a value
 * @param arrayToSet The array that will be filled with the initial value
 * @param arrSize Size of the array passed in parameter
 * @param defaultValue The value that we want to set every element of the array
 */
void setAllElementsInArray(bool arrayToSet[], std::size_t arrSize,
                           bool defaultValue);

/**
 * Set all elements of array to an ascending order of numbers. It goes from index
 * 0 to arrSize. It is also possible to start by another number than 0 with the
 * param startsAt
 * @param arrayToSet The array that will be set with ascending numbers
 * @param arrSize Size of the array passed in parameter
 * @param startsAt The number at which the ascending order starts
 */
void setArrayWithAscendingOrder(unsigned arrayToSet[], std::size_t arrSize,
                                std::size_t startsAt);

/**
 * Display an array like a table
 * @param array The array to display
 * @param arrSize Size of the array passed in parameter
 * @param nbCol The number of column of the table
 * @param colWidth The width in character of every column. If the number does not
 * have enough digits, it will be filled with space
 */
void displayArrayAsTable(const unsigned array[], std::size_t arrSize, unsigned nbCol,
                         int colWidth);

/**
 * Display an array like a table
 * @param array The array to display
 * @param arrSize Size of the array passed in parameter
 * @param nbCol The number of column of the table
 * @param colWidth The width in character of every column. If the number does not
 * have enough digits, it will be filled with space
 * @param valueWhenFalse The displayed value when an element is false
 * @param valueWhenTrue The displayed value when an element is true
 */
void displayArrayAsTable(const bool array[], std::size_t arrSize, unsigned nbCol,
                         int colWidth,
                         char valueWhenFalse = '0', char valueWhenTrue = '1');

#endif //INC_06_CRIBLE_UTILITIES_H
