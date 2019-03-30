# https://www.acmicpc.net/problem/2749
from functools import lru_cache

# Pisano period
# Reference: https://en.wikipedia.org/wiki/Pisano_period
MOD = 1000000
PISANO_PERIOD = 1500000

# lru_cache 붙이면 자동으로 memoization이 됨
# Reference: https://docs.python.org/3/library/functools.html#functools.lru_cache
@lru_cache(maxsize=None)
def fibo(num: int) -> int:
    # Base cases
    if num < 14:
        return [0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233][num]

    # d'Ocagne's identity
    # Reference: https://en.wikipedia.org/wiki/Fibonacci_number#d'Ocagne's_identity
    k = num // 2
    return (
        fibo(k)*(2*fibo(k + 1) - fibo(k))
        if num % 2 == 0 else
        fibo(k + 1)**2 + fibo(k)**2
    ) % MOD

if __name__ == '__main__':
    num = int(input())
    print(fibo(num % PISANO_PERIOD))
