/*
-----------------------------------------------------------------------------------
File name     : utilities.cpp
Author(s)     : Leandro Saraiva Maia, Miguel Jalube
Creation date : 18.11.2021

Description   : See header comment of utilites.h
Remark(s)     :

Compiler      : Mingw-w64 g++ 11.1.0
-----------------------------------------------------------------------------------
*/

#include "utilities.h"       // Prototypes
#include <cmath>

int getNumberOfDigits(unsigned number){
   return int(log10(number)+1);
}