def main(count: int) -> int:
    for i in range(666, 2666799 + 1):
        if '666' not in str(i):
            continue

        count -= 1
        if count == 0:
            return i

count = int(input())
result = main(count)
print(result)
