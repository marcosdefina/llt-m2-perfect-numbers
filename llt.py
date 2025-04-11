mersenne_primes = [6, 28, 496, 8128, 33550336, 8589869056, 137438691328]

def llt(p, found):
    s = 4
    M = 2**p - 1

    for index in range(p - 2):
        print(f"\revaluating {p} as candidate for perfect number - {round(index / (p - 2) * 100, 6)}% completed", end="")
    
        s = (s * s - 2) % M

    print("\n")

    for f in found:
        print(f"{f} found to be a prime")

    return s == 0

found = []
for m in mersenne_primes: # Takes 1 minute to process 0.0001% of 5th marsenne prime
    found.append(m)
    print(f"{m} is {'prime' if llt(m, found) else 'composite'}")