//
// Created by migue on 18.11.2021.
//
#include <iostream>
#include <iomanip>
#include "sieve.h"

using namespace std;

void sieveRun(unsigned size){

   //----------------------------------------------------
   // Initialisation
   //----------------------------------------------------
   //TODO : replace by initialisation() function
   unsigned tab[100];
   for (unsigned i = 0; i < size; ++i) {
      tab[i] = i+1;
   }
   bool tabB[100];
   for (bool & i : tabB) {
      i = true;
   }
   tabB[0] = false;

   //----------------------------------------------------
   // Display the table
   //----------------------------------------------------
   //TODO : replace by display() function

   //----------------------------------------------------
   // Sieve
   //----------------------------------------------------
   //TODO : replace by display() function
   sieve(tabB, size, tab);

   //----------------------------------------------------
   // Display the sieve results
   //----------------------------------------------------
   //TODO : replace by display() function
   cout << endl;
   for (size_t i = 0ull; i< size; ++i) {
      char display = 'X';
      if(tabB[i] && i>0){
         display = 'O';
      }
      cout << display;
      if((i+1)%10 == 0)
         cout << endl;
   }

   //-----------------------------------------------------
   // for tests :
   //-----------------------------------------------------
   // TODO : remove this loop for the final version
   for (size_t i = 0ull; i< size; ++i) {
      unsigned display = 0;
      if(tabB[i] && i>0){
         display = tab[i];
      }
      cout << setw(3) << right;
      cout << display;
      if((i+1)%10 == 0)
         cout << endl;
   }
}

void displaySieve(bool sieveTable[], size_t sieveTableSize, unsigned nbCol){

}

void sieve(bool sieveTable[], size_t sieveTableSize, const unsigned
primeTable[]){
   for (size_t i = 0ull; i < sieveTableSize; ++i) {
      unsigned nb = primeTable[i];
      for (size_t j = i+1ull; j < sieveTableSize &&
      sieveTable[i];
      ++j) {
         if(primeTable[j]%nb==0){
            sieveTable[j] = false;
         }
      }
   }
}
void displayResults(){

}