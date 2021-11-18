/*
-----------------------------------------------------------------------------------
File name     : main.cpp
Lab name      : 
Author(s)     : Leandro Saraiva Maia, Miguel
Creation date : 18.11.2021

Description   : 
Remark(s)     : 
 
Compiler      : Mingw-w64 g++ 11.1.0
-----------------------------------------------------------------------------------
*/

#include <cstdlib>  // required for EXIT_SUCCESS
#include <iostream> // required for cout
#include <limits>   // required for numeric_limits<...>

using namespace std;

int main() {
   
   //------------------------------------------------------
   // end of program
   cout << "Press ENTER to quit.";
   cin.ignore(numeric_limits<streamsize>::max(), '\n'); // empty buffer
   return EXIT_SUCCESS;
}