/*
-----------------------------------------------------------------------------------
File name     : inputValidation.h
Author(s)     : Leandro Saraiva Maia
Creation date : 22.11.2021

Description   : Set of function to retrieve user input more easily. It handles
                wrong values types and specific values ranges.
Remark(s)     :

Compiler      : Mingw-w64 g++ 11.1.0
-----------------------------------------------------------------------------------
*/

#ifndef LABO_06_INPUT_VALIDATION_H
#define LABO_06_INPUT_VALIDATION_H

/**
 * Get and validate the user input in unsigned int.
 * @param min The minimum value required (included)
 * @param max The maximum value required (included)
 * @return the user input
 */
unsigned getInput(unsigned min, unsigned max);

#endif