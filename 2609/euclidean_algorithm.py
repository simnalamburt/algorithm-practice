from math import gcd
from random import sample

def my_gcd(a, b):
    if a == b:
        return a
    if a < b:
        return my_gcd(b, a)

    # Invariant: a > b
    rem = a % b
    if rem == 0:
        return b

    return my_gcd(b, a % b)

def test(a, b):
    expected = my_gcd(a, b)
    actual = gcd(a, b)

    if expected == actual:
        print(f'Good : GCD({a}, {b}) = {actual}')
    else:
        print(f'Bad  : GCD({a}, {b}) = {actual}, not {expected}')

if __name__ == '__main__':
    test(1400, 720)
    test(4100, 270)

    for _ in range(10):
        a, b, c = sample(range(100, 200), 3)
        test(a*b, a*c)
