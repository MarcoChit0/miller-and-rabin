#include <iostream>
#include <math.h>
#include <fstream>
#include <gmpxx.h>
using namespace std;

int main(int argc, char *argv[]){
    unsigned long long digits = atoll(argv[1]);
    mpz_t base, prime; 
    mpz_init_set_ui(base, 1); mpz_init(prime);
    // i := número de dígitos
    for (unsigned long long i = 0; i<=digits; i++){
        ofstream f("primes/" + to_string(i + 1) + ".txt");
        mpz_nextprime(prime, base);
        mpz_mul_ui(base, base, 10);
        f << prime << endl;
        f.close();
    }
    mpz_clear(prime);
    mpz_clear(base);
    return 0;
}