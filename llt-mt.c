#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <math.h>

#define NUM_THREADS 4

typedef struct {
    long long int p;
    long long int M;
    long long int start;
    long long int end;
    long long int* s;
    bool is_valid;
} ThreadArgs;

pthread_mutex_t print_lock;

void* llt_partial(void* args) {
    ThreadArgs* thread_args = (ThreadArgs*)args;
    long long int s = *(thread_args->s);
    long long int M = thread_args->M;

    for (long long int index = thread_args->start; index < thread_args->end; index++) {
        s = (s * s - 2) % M;
    }

    pthread_mutex_lock(&print_lock);
    *(thread_args->s) = s;
    pthread_mutex_unlock(&print_lock);

    pthread_exit(NULL);
}

bool llt(long long int p) {
    long long int s = 4;
    long long int M = (1LL << p) - 1; // M = 2^p - 1
    pthread_t threads[NUM_THREADS];
    ThreadArgs thread_args[NUM_THREADS];

    long long int range = (p - 2) / NUM_THREADS;
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_args[i].p = p;
        thread_args[i].M = M;
        thread_args[i].start = i * range;
        thread_args[i].end = (i == NUM_THREADS - 1) ? (p - 2) : (i + 1) * range;
        thread_args[i].s = &s;
        thread_args[i].is_valid = true;

        if (pthread_create(&threads[i], NULL, llt_partial, &thread_args[i]) != 0) {
            perror("Failed to create thread");
            return false;
        }
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    return s == 0;
}

int main() {
    pthread_mutex_init(&print_lock, NULL);

    long long int mersenne_primes[] = {6, 28, 496, 8128, 33550336, 8589869056, 137438691328}; // Took 2 mins to process all
    int num_primes = sizeof(mersenne_primes) / sizeof(mersenne_primes[0]);

    for (int i = 0; i < num_primes; i++) {
        long long int p = mersenne_primes[i];
        printf("Evaluating %lld...\n", p);
        bool is_prime = llt(p);
        printf("%lld is %s\n", p, is_prime ? "prime" : "composite");
    }

    pthread_mutex_destroy(&print_lock);
    return 0;
}