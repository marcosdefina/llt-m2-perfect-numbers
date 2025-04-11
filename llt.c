#include <stdio.h>  
#include <stdlib.h> 
#include <math.h>   
#include <stdbool.h>

int llt(long long int p, long long int found[], int size) {
    long long int s = 4;
    long long int M = (1LL << p) - 1; // M = 2^p - 1

    for (int index = 0; index < p - 2; index++) {
        printf("\revaluating %lld as candidate for perfect number - %.2f%% completed", p, (float)index / (p - 2) * 100);
        fflush(stdout);

        s = (s * s - 2) % M;
    }
    printf("\n");

    for (int i = 0; i < size; i++) {
        printf("%lld found to be a prime\n", found[i]);
    }

    return s == 0;
}

int main() {
    long long int mersenne_primes[10] = {6, 28, 496, 8128, 33550336, 8589869056, 137438691328}; // 3% a second on 5th marsenne prime
    long long int found[10]; 
    int p;

    for (int i = 0; i < sizeof(mersenne_primes) / sizeof(mersenne_primes[0]); i++) {
        p = mersenne_primes[i];
        found[i] = p;
        printf("%lld is %s\n", p, llt(p, found, i + 1) ? "prime" : "composite");
    }

    return 0;
}