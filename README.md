# miller and rabin

## To compile: 

g++ -o mr miller_rabin.cpp -lgmpxx -lgmp

## To run:

./mr

Output on terminal. Format answer = {'s', 'n'}

## To run -- time test:

./mr --time

Output on terminal. Format "#digits,time(ms),answer"

## To run -- probability test

./mr --prob

Output on probtest folder.

### Required

GMP: https://gmplib.org/
