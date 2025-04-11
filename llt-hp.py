import numpy as np
from concurrent.futures import ThreadPoolExecutor
import threading

mersenne_primes = [6, 28, 496, 8128, 33550336, 8589869056, 137438691328]

print_lock = threading.Lock()

def llt(p):
    """Lucas-Lehmer Test for Mersenne primes."""
    s = 4
    M = 2**p - 1

    for index in range(p - 2):
        if index % (p // 100) == 0:
            with print_lock:
                print(f"\r[Thread {threading.current_thread().name}] Evaluating {p} - {round(index / (p - 2) * 100, 2)}% completed", end="")
        s = (s * s - 2) % M

    with print_lock:
        print(f"\n[Thread {threading.current_thread().name}] Finished evaluating {p}")

    return s == 0

def process_prime(m):
    """Process a single Mersenne prime."""
    result = llt(m)
    return f"{m} is {'prime' if result else 'composite'}"

if __name__ == "__main__":
    with ThreadPoolExecutor() as executor:
        results = list(executor.map(process_prime, mersenne_primes))

    print("\nResults:")
    for res in results:
        print(res)