# https://www.acmicpc.net/problem/2749
from functools import lru_cache

MOD = 1000000

# 피사노 주기
# Reference: https://en.wikipedia.org/wiki/Pisano_period
PISANO_PERIOD = 1500000

# lru_cache 붙이면 자동으로 memoization이 됨
# Reference: https://docs.python.org/3/library/functools.html#functools.lru_cache
@lru_cache(maxsize=None)
def fibo(n: int) -> int:
    # Base cases
    if n in range(10):
        return [0, 1, 1, 2, 3, 5, 8, 13, 21, 34][n]

    # d'Ocagne's identity
    # Reference: https://en.wikipedia.org/wiki/Fibonacci_number#d'Ocagne's_identity
    k = n // 2
    return (
        fibo(k)*(2*fibo(k + 1) - fibo(k))
        if n % 2 == 0 else
        fibo(k + 1)**2 + fibo(k)**2
    ) % MOD

if __name__ == '__main__':
    num = int(input())
    print(fibo(num % PISANO_PERIOD))
