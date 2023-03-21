#include <iostream>
#include <gmpxx.h>
#include <math.h>
using namespace std;
bool millerrabin(mpz_t n, gmp_randstate_t state);
int main(int argc, char *argv[]) {
    mpz_t n; mpz_init(n);
    gmp_randstate_t state; gmp_randinit_default(state);
    gmp_randseed_ui(state, time(NULL));
    string s; cin >> s;
    mpz_set_str(n, s.c_str(), 10);
    cout<< "resultado: " << millerrabin(n, state) << endl;
    cout<< "resposta certa: " << mpz_probab_prime_p(n, 10000) << endl;
    mpz_clear(n);
}

bool millerrabin(mpz_t n, gmp_randstate_t state){
    bool result = false;
    mpz_t a, n_minus_one, u, x;
    unsigned long long t=0;
    mpz_init(a);
    mpz_init(n_minus_one); mpz_sub_ui(n_minus_one, n, 1);
    mpz_init_set(u, n_minus_one);
    mpz_init(x);

    // select a in [1, n-1] randomly
    do{ mpz_urandomm(a, state, n); } while(!mpz_cmp_d(a, 0));

    // x = gcd(a, n)
    mpz_gcd(x, a, n);

    // if gcd(a, n) =/= {1}, then n is not prime. 
    if (mpz_cmp_d(x,1)){
        goto exit;
    }

    // 2^t * u = n - 1
    while (mpz_even_p(u)) {
        mpz_fdiv_q_2exp(u, u, 1);
        t++;
    }

    // x = a^u % n
    mpz_powm(x, a, u, n);

    // if x == 1, return "yes"
    if (mpz_cmp_ui(x, 1) == 0){
        result = true; goto exit;
    }


    for (int i = 0; i < t-1; i++){
        // if x == n-1, return "yes"
        if (mpz_cmp(x, n_minus_one) == 0){
            result = true;  goto exit;
        }
        mpz_powm_ui (x, x, 2, n); // x = x² % n
    }
    // if x == n-1, return "yes"
    if (mpz_cmp(x, n_minus_one) == 0){
        result = true; goto exit;
    }

    exit:
    mpz_clear(a);
    mpz_clear(n_minus_one);
    mpz_clear(u);
    mpz_clear(x);
    return result;
}