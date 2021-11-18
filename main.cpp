/*
-----------------------------------------------------------------------------------
File name     : main.cpp
Lab name      : "06 Crible"
Author(s)     : Leandro Saraiva Maia, Miguel Jalube
Creation date : 18.11.2021

Description   : 
Remark(s)     : 
 
Compiler      : Mingw-w64 g++ 11.1.0
-----------------------------------------------------------------------------------
*/

#include <cstdlib>             // required for EXIT_SUCCESS
#include <iostream>            // required for cout
#include <limits>              // required for numeric_limits<...>

// Note that this library uses another naming convention that we will not use here
// (snake_case instead of camelCase)
#include "input_validation.h"  // required to get input

using namespace std;

int main() {
	cout << "Hi, please enter a number between 1..100";
   
   //------------------------------------------------------
   // end of program
   cout << "Press ENTER to quit.";
   cin.ignore(numeric_limits<streamsize>::max(), '\n'); // empty buffer
   return EXIT_SUCCESS;
}