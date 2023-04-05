#include <iostream>
#include <gmpxx.h>
#include <math.h>
#include <time.h>
#include <chrono>
#include <fstream>
using namespace std;

#define NUMRUNS 50

bool millerrabin(mpz_t n, mpz_t a);

int main(int argc, char *argv[]) {
    bool time_test = false, prob_test = false;
    auto start = chrono::steady_clock::now();
    string s, answer = "n"; cin >> s;
    mpz_t n; mpz_init(n); mpz_set_str(n, s.c_str(), 10);
    mpz_t a; mpz_init(a);
    
    if (strcmp(argv[1], "--time") == 0){ time_test = true; }
    if (strcmp(argv[1], "--prob") == 0){ prob_test = true; goto probtest; }

    for (int i = 0; i < NUMRUNS; i++){
        gmp_randstate_t state; gmp_randinit_default(state);
        gmp_randseed_ui(state, time(NULL));
        
        // select a in [1, n-1] randomly
        do{ mpz_urandomm(a, state, n); } while(!mpz_cmp_d(a, 0));    
        
        if (!millerrabin(n, a)){    
            goto mainexit;
        }
    }
    answer = "s";
    mainexit:
    if (time_test){
        auto end = chrono::steady_clock::now();
        auto diff = end - start;
        cout 
            << s.length() << ","
            << chrono::duration <double, milli> (diff).count() << ","
            << answer << endl;
    }
    else{
        cout << answer << endl;
    }
    mpz_clear(n); mpz_clear(a);
    return 0; 

    probtest:
    if (prob_test){
        cout << s << endl;
        ofstream f("probtest/" + s + ".csv");
        f << "base,result\n";
        string result = "n";
        for (unsigned long long base = 1; mpz_cmp_ui(n, base) > 0; base++){
            mpz_set_ui(a, base);
            if (!(base % 2 == 0) && millerrabin(n, a)){
                result = "s";
            }
            else{
                result = "n";
            }
            f << base << "," << result << endl;
        }
        f << s << "," << mpz_probab_prime_p(n, 50) << endl;
        goto mainexit;
    }

}

bool millerrabin(mpz_t n, mpz_t a){
    bool result = false;
    mpz_t n_minus_one, u, x;
    unsigned long long t=0;
    mpz_init(n_minus_one); mpz_sub_ui(n_minus_one, n, 1);
    mpz_init_set(u, n_minus_one);
    mpz_init(x); mpz_mod_ui(x, n, 2);
    if (mpz_cmp_ui(x, 0) == 0) {goto exit;}

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
    mpz_clear(n_minus_one);
    mpz_clear(u);
    mpz_clear(x);
    return result;
}