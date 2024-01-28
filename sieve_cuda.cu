/*
-----------------------------------------------------------------------------------
File name     : main.cpp
Lab name      : "06 Crible" or "Sieve"
Author(s)     : Leandro Saraiva Maia, Miguel Jalube
Creation date : 18.11.2021

Description   : This programs asks the user for an amount of prime numbers to
                find. Then, it uses the sieve of Eratosthenes to compute the
                amount of prime numbers wanted (start from 0 -> amount). Finally,
                it displays sieve table and the prime that have been found.
Remark(s)     : The clion console is a bit bugged and may display values
                incorrectly, it is better to use an external console.
                This program is meant to be used only in english, there are no
                constants sets to facilitate potential translation.

 
Compiler      : Mingw-w64 g++ 11.1.0
-----------------------------------------------------------------------------------
*/

#include <cstdlib>   
#include <iostream>  
#include <limits>
#include <string>    
#include <iomanip>   
#include <cassert>   
#include <cmath>     
#include <time.h>
#include <cuda_runtime.h>

// taille du tableau = quantité de nombre que le bloc peut vérifier si il est prmier ou non 
// Ne pas dépasser 40000 car il y a une limite à la mémoire partagée par bloc
#define SHARE_MEMORY_SIZE 40000

using namespace std;

unsigned getNumberOfDigits(const unsigned long long number);
void setAllElementsInArray(bool arrayToSet[], const size_t arrSize,
                           const bool defaultValue);
void setArrayWithAscendingOrder(unsigned long long arrayToSet[], const size_t arrSize,
                                const size_t startsAt);
void displayArrayAsTable(const unsigned long long array[], const size_t arrSize,
                         const unsigned nbCol, const int colWidth);
void sieve(bool sieveArray[], size_t sieveArraySize);
unsigned long long extractPrimeNumbers(const bool sieveArray[], size_t sieveArraySize,
								     unsigned long long primeArray[]);

int main(int argc, char* argv[]) {
   clock_t start_time = clock();

	//---------- Variables and constants ----------
	const unsigned long long   MIN_PRIME_UP_TO =                2ull;
   const unsigned long long   MAX_PRIME_UP_TO =                100000ull; // >100000 may cause memory issues
   const unsigned             RESULT_NB_COL =                  20u;
	unsigned long long         primeNumArray[MAX_PRIME_UP_TO];
   unsigned long long         numToCheckForPrime;
	unsigned long long         numOfPrimeNumbers;
	bool                       sieveArray[MAX_PRIME_UP_TO];


   if(argc != 2 || stoull(argv[1]) < MIN_PRIME_UP_TO || stoull(argv[1]) > MAX_PRIME_UP_TO){
      cout << "Usage : ./sieve <number>" << endl;
      cout << MIN_PRIME_UP_TO << " < [number] < " << MAX_PRIME_UP_TO << endl;
      return EXIT_FAILURE;
   }

   numToCheckForPrime = stoull(argv[1]);

   //---------- Initialization ----------
   setArrayWithAscendingOrder(primeNumArray, numToCheckForPrime, 1);
   setAllElementsInArray(sieveArray, (size_t)numToCheckForPrime, true);

   clock_t init_time = clock();

   //---------- Computes prime numbers with Eratosthenes sieve ----------
   sieve(sieveArray, numToCheckForPrime);

   clock_t sieve_time = clock();

   numOfPrimeNumbers = extractPrimeNumbers(sieveArray, numToCheckForPrime, primeNumArray);

   clock_t extract_time = clock();

   //---------- Display the sieve results ----------
   cout << endl << numOfPrimeNumbers << " prime number(s) found up to " << numToCheckForPrime << endl;
   displayArrayAsTable(primeNumArray, numOfPrimeNumbers, RESULT_NB_COL, int(getNumberOfDigits(MAX_PRIME_UP_TO)));
   cout << endl;

   clock_t display_time = clock();

   //---------- Display time measures --------------
   printf("============= Time measures ===============\n");
   printf("Init time :     %f\n", (double)(init_time - start_time) / CLOCKS_PER_SEC);
   printf("Sieve time :    %f\n", (double)(sieve_time - init_time) / CLOCKS_PER_SEC);
   printf("Extract time :  %f\n", (double)(extract_time - sieve_time) / CLOCKS_PER_SEC);
   printf("Display time :  %f\n", (double)(display_time - extract_time) / CLOCKS_PER_SEC);
   printf("Total time :    %f\n", (double)(display_time - start_time) / CLOCKS_PER_SEC);

   return EXIT_SUCCESS;
}

unsigned getNumberOfDigits(const unsigned long long number){
   return number > 0ull ? unsigned(log10(double(number))) + 1ull : 1ull;
}

// We could imagine an overload for other data types
void setAllElementsInArray(bool arrayToSet[], const size_t arrSize,
                           const bool defaultValue) {
   // Check if array is not null
   assert(arrayToSet != nullptr);
   for (size_t i = 0ull; i < arrSize; ++i) {
      arrayToSet[i] = defaultValue;
   }
}

void setArrayWithAscendingOrder(unsigned long long arrayToSet[], const size_t arrSize,
                                const size_t startsAt = 0ull) {
   // Check if array is not null
   assert(arrayToSet != nullptr);
   for (size_t i = 0ull; i < arrSize; ++i) {
      arrayToSet[i] = i + startsAt;
   }
}

void displayArrayAsTable(const unsigned long long array[], const size_t arrSize,
                         const unsigned nbCol, const int colWidth) {
   assert(array != nullptr);
   for (size_t i = 0ull; i < arrSize; ++i) {
      cout << setw(colWidth) << array[i];
      if ((i + 1ull) % (unsigned long long)nbCol == 0ull && i != arrSize - 1ull)
         cout << endl;
   }
}

void displayArrayAsTable(const bool array[], const unsigned long arrSize,
                         const unsigned nbCol, const int colWidth,
                         const char valueWhenFalse, const char valueWhenTrue) {
   assert(array != nullptr);
   for (size_t i = 0ull; i < arrSize; ++i) {
      cout << setw(colWidth) << (array[i] ? valueWhenTrue : valueWhenFalse);
      if ((i + 1ull) % (unsigned long long)nbCol == 0ull && i != arrSize - 1ull)
         cout << endl;
   }
}

__global__ void kernel(size_t sieveArraySize, bool *sieveArray) {

   unsigned int thread_id = threadIdx.x;

   __shared__ bool sharedSieveArray[SHARE_MEMORY_SIZE];

   // défini le nombre d'itération du crible d'hératostène
   int threadRangeNb = (sieveArraySize + blockDim.x - 1) / blockDim.x;

   // défini la quantité de nombre que le bloc va vérifier (doit être )
   int blockRangeNb = (sieveArraySize + gridDim.x - 1) / gridDim.x;
   assert(SHARE_MEMORY_SIZE >= blockRangeNb);

   // Tous les nombres sont initialisé comme premiers 
   for (int i = 0; i < blockRangeNb; ++i) {
      sharedSieveArray[i] = true;
   }

   __syncthreads();
   
   // Pour toute les itérations du crible de ce treads
   for (int i = 0; i < threadRangeNb; ++i) {

      //nombre de l'itéreation du crible
      int n = threadRangeNb * thread_id + i + 1;

      if(n == 1){
         // il ne faut pas tenter de diviser les nombres par 1
         continue;
      }else if (n < sieveArraySize) { // pourrait être opimisé en remplacant par racine de n mais nous gardons la structure originale du code

         // itére uniquement sur les nombres du bloc
         for (size_t j = max(n, blockIdx.x * blockRangeNb); j < min((size_t)(blockRangeNb * (blockIdx.x+1)), sieveArraySize); ++j) {
            // retires les nombres qui ne sont pas premiers
            if((j + 1ull) % n == 0ull){
               sharedSieveArray[j-blockIdx.x * blockRangeNb] = false;
            }
         }
      }
   }
   __syncthreads();

   // copie les nombres depuis la mémoire partagée
   for (int i = blockIdx.x * blockRangeNb; i < (blockIdx.x+1) * blockRangeNb; ++i) {
      sieveArray[i] = sharedSieveArray[i-blockIdx.x * blockRangeNb];
   }
}





void sieve(bool sieveArray[], size_t sieveArraySize){

   // 1 n'est pas premier
   sieveArray[0] = false;

   assert(sieveArray != nullptr && sieveArray != nullptr);

   size_t size = sieveArraySize * sizeof(bool);

   bool *d_sieveArray;
   cudaMalloc((void **)&d_sieveArray, size);

   int blockSize = 256;
   int numBlocks = 4; // attention (sieveArray / numBlocks) doiit être supérieur à 40000 sinon problème de mémoire sur la gpu

   kernel<<<numBlocks, blockSize>>>(sieveArraySize, d_sieveArray);

   cudaMemcpy(sieveArray, d_sieveArray, size, cudaMemcpyDeviceToHost);
   
   cudaFree(d_sieveArray);
}

unsigned long long extractPrimeNumbers(const bool sieveArray[], size_t sieveArraySize,
								     unsigned long long primeArray[]) {
	unsigned long long numOfPrimeNumbers = 0ull;
	for (size_t i = 0ull; i < sieveArraySize; ++i) {
		if (sieveArray[i]) {
			primeArray[numOfPrimeNumbers++] = i + 1ull;
		}
	}

	return numOfPrimeNumbers;
}