def fibo(n: int) -> int:
    if n == 0:
        return 0
    if n < 0:
        return (
            -fibo(-n) if n % 2 == 0 else
            fibo(-n)
        )

    a = 0
    b = 1
    for _ in range(n-1):
        c = a + b
        a, b = b, c
    return b

for _ in range(int(input())):
    num = int(input())
    print(f'{fibo(num-1)} {fibo(num)}')
