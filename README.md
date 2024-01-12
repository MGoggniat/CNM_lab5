# Sieve
## Code modifications
### 1. Moved the prompt that asks the prime number to main program args
The reason for this is that the program should be able to run without any user input so we can use it in a ahell script for measures.

### 2. Removed the 100 limit for the prime number
The reason for this is that calculate prime numbers up to 100 is too fast, we need a bigger number to see the difference between the sequential and parallel version.

### 3. Removed the sieve grid
The reason for this is that the sieve grid is not needed for this lab.

### 4. Removed "Press ENTER to quit" prompt

### 5. Replaced CMakeLists.txt with Makefile for easier compilation
This was done by ChatGPT
