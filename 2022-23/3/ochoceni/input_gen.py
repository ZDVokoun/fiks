import random

def firstBit(n: int) -> int:
    for i in range(32, -1, -1):
        if (1 << i) & n != 0:
            return i
    return -1

def lastBit(n: int) -> int:
    for i in range(32):
        if (1 << i) & n != 0:
            return i
    return -1

primes = [3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61]
def biggestPrime(n):
    res = 5
    for p in primes:
        if p <= n:
            res = p
        else:
            break
    return res


n = random.randint(1 << 16, 1 << 32)


print(n, bin(n))
def task(n, i):
    if (lastBit(n) == -1):
        return i
    x = n ^ ((1 << (biggestPrime(firstBit(n) - lastBit(n)) + 1)) - 1) << lastBit(n)
    return task(x, i + 1)

print(task(n, 0))
