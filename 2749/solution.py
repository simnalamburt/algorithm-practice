# https://www.acmicpc.net/problem/2749

# Pisano period
# Reference: https://en.wikipedia.org/wiki/Pisano_period
MODULO = 1000000
PISANO_PERIOD = 1500000
BASE_CASES = [0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233]

def fibo2(num: int) -> tuple:
    '''
    fibo2(num) 은 num번째와 num+1 번째 피보나치 수를 반환하는 함수다
    '''

    # Base cases
    if num < 13:
        return (BASE_CASES[num], BASE_CASES[num+1])

    # d'Ocagne's identity
    # Reference: https://en.wikipedia.org/wiki/Fibonacci_number#d'Ocagne's_identity
    k = num // 2
    fibo_k0, fibo_k1 = fibo2(k)
    answer0, answer1 = (
        (fibo_k0*(2*fibo_k1 - fibo_k0), fibo_k0**2 + fibo_k1**2)
        if num % 2 == 0 else
        (fibo_k0**2 + fibo_k1**2, fibo_k1*(2*fibo_k0 + fibo_k1))
    )

    # Mod out
    return (answer0 % MODULO, answer1 % MODULO)

if __name__ == '__main__':
    num = int(input())
    answer = fibo2(num % PISANO_PERIOD)[0]
    print(answer)
