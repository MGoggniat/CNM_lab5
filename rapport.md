# Laboratory 5 CNM - Optimisation of the Sieve of Eratosthenes
- **Authors :** Miguel Jalube and Michael Gogniat
- **Professor :** Marina Zapater
- **Course :** CNM
- **Date :** 28.01.2024
## Introduction
The goal of this laboratory is to optimize the Sieve of Eratosthenes algorithm. This algorithm is used to find all the prime numbers up to a given limit. The base program was developed in C++ by Miguel Jalube and Leandro Saraiva Maia (another student of the course) as a PRG1 laboratory. After analyzing the code, we noticed that the algorithm was no so well coded as the real version should check divisors up to the square root of the number but in this case the algorithm cheks divisors up to N - 1.

## Algorithm description

The algorithm is based on the Sieve of Eratosthenes algorithm. The algorithm is based on the following steps:

1. Initialize an array of size N with all the values up to N set to true
2. For each value in the array (normally up to square root of N in the true algorithm), search for all the multiples of the value and set them to false.
3. Extract all the values that are true in the array and display them. These are the prime numbers.

## Optimizations
### Unoptimized version

First of all to find what was the bottleneck of the algorithm, we cut the program in different phases and measured the time of each phase :

- Init phase : Here every array and variable is initialized.
- Sieve phase : Here the algorithm is executed.
- Extract phase : Here the prime numbers are extracted from the array.
- Display phase : Here the prime numbers are displayed.

The unoptimizted results are shown in the following table:

Normal sieve 100'000
```
============= Time measures ===============
Init time :     0.001169
Sieve time :    2.207875
Extract time :  0.000544
Display time :  0.003027
Total time :    2.212615
```

As we can see, the sieve phase is the most time consuming phase. So we decided to focus on this phase to optimize the algorithm.

This is the code of the unoptimized sieve function:

```cpp
void sieve(bool sieveArray[], size_t sieveArraySize){
    assert(sieveArray != nullptr && sieveArray != nullptr);
    sieveArray[0] = false;
    unsigned long long checkNumber;
    unsigned long long currentNumber;

    for (size_t i = 0; i < sieveArraySize; ++i) {
        checkNumber = i + 1;
        for (size_t j = checkNumber; j < sieveArraySize && sieveArray[i]; ++j) {
            currentNumber = j + 1;
            if(currentNumber % (checkNumber) == 0){
                sieveArray[j] = false;
            }
        }
    }
}
```

### OpenMP parallelization

The first optimization we did was to parallelize the sieve phase using OpenMP. To do so there were three possibilities :
1. Parallelize the outer loop
2. Parallelize the inner loop
3. Parallelize both loops

The outer loop actually iterates over each value of the array. This means that the first value to be checked is 2. Then the inner loop iterates search for every multiple of 2 and set them to false. The problem with this approach is that the first value to be checked will be more time consuming than the last one. If one thread is assigned to i = 2 and another to i = 4, the first will take more time to finish than the second. As 4 is multiple of 2 it is important that 2 is checked before 4. For this reason, if we parallelize the outer loop with multiple threads, it will be longer than if it is treated by a single thread.

The inner loop iterates over the multiples of the current value. This means that the first value to be checked is the first multiple of the current value. Then the next value to be checked is the second multiple of the current value and so on. This means that the first value to be checked will be the same for every thread. First it seemed like a good idea to parallelize this loop, but after testing it we noticed than the results were worse than a single threaded solution. The reason for this is because the overhead of creating the threads is bigger than the time saved by parallelizing the loop.

The last option is to parallelize both loops. This means that each thread will be assigned a value to check and then it will check all the multiples of this value. We managed to parallelize both loops using OpenMP but never got better results than the single threaded solution.

Finally the best results among all the OpenMP solutions was to parallelize the outer loop with dynamic schedule. The code of this solution is shown below:

```cpp
void sieve(bool sieveArray[], size_t sieveArraySize){
    assert(sieveArray != nullptr && sieveArray != nullptr);
    sieveArray[0] = false;
    unsigned long long checkNumber;
    unsigned long long currentNumber;

    #pragma omp parallel for schedule(dynamic)
    for (size_t i = 0; i < sieveArraySize; ++i) {
        checkNumber = i + 1;
        for (size_t j = checkNumber; j < sieveArraySize && sieveArray[i]; ++j) {
            currentNumber = j + 1;
            if(currentNumber % (checkNumber) == 0){
                sieveArray[j] = false;
            }
        }
    }
}
```

The results of the single threaded and 8 threaded solutions are shown below:

OMP sieve N = 100'000

```
============= Time measures ===============
For 1 threads
Init time :     0.001184
Sieve time :    2.195234
Extract time :  0.000541
Display time :  0.003480
Total time :    2.200439
```

```
============= Time measures ===============
For 8 threads
Init time :     0.001117
Sieve time :    2.238839
Extract time :  0.001138
Display time :  0.003127
Total time :    2.244221
```

### CUDA parrallelization

The next step was to parallelize the sieve phase using CUDA. To do so we had to copy the array to the GPU, execute the algorithm on the GPU and then copy the array back to the CPU. The code of the kernel is shown below:

```cpp
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
```

The results obtained with CUDA parallelization are 97.42% faster than the single threaded solution. The results are shown below:

CUDA sieve N = 100'000

```
============= Time measures ===============
Init time :     0.001174
Sieve time :    0.056964
Extract time :  0.001118
Display time :  0.006168
Total time :    0.065424
```

By commenting out the line //kernel<<<numBlocks, blockSize>>>(sieveArraySize, d_sieveArray), we can see that almost all of the sieve time is spent on GPU memory allocation/copying.

No significant changes are observed by increasing the number of blocks because the computation is too fast. It is important to use a sufficient number of blocks because for a large number (e.g., 100,000), a single block does not have enough shared memory.

```
============= Time measures ===============
Init time :     0.001173
Sieve time :    0.057847
Extract time :  0.000397
Display time :  0.000128
Total time :    0.059545
```

## Conclusion
After trying different optimizations, we managed to get a 97.42% faster solution than the single threaded solution. The best results were obtained using CUDA parallelization. Curiously we never managed to get better results using OpenMP than the single threaded solution. Thinking about it, the only possible explanation is that the overhead of creating the threads is bigger than the time saved by parallelizing the algorithm. We came to conclusion that the algorithm is not suited for OpenMP parallelization. On the other hand, the algorithm is well suited for CUDA parallelization because the overhead of copying the array to the GPU is not so big compared to the time saved by parallelizing the algorithm.