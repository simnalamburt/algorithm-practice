# 수열이 강한단조감소하다가 "하나의 최소점" 이후로 강한단조증가한다고 가정할 수 있는 경우,
# 이진탐색으로 최소점을 찾을 수 있다.
def find_min(seq: list) -> tuple[int, int]:
    lo = 0
    hi = len(seq)

    # Loop invariant:
    #   lo < hi
    #   seq[lo] 는 강한단조감소하는 수열의 일부
    #   seq[hi-1] 은 강한단조증가하는 수열의 일부
    while lo + 1 < hi:
        print(seq[lo:hi])

        mid = (lo + hi)//2
        # NOTE: 문제조건상 seq[mid - 1] == seq[mid] 는 불가능
        if seq[mid - 1] > seq[mid]:
            # 강한단조감소, 최소점은 [mid, hi) 안에 있음
            lo = mid
        else:
            # 강한단조증가, 최소점은 [lo, mid) 안에 있음
            hi = mid

    print(seq[lo:hi])
    return (seq[lo], lo)

print('min:', find_min([10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 2, 4, 6, 8, 10, 12, 14]))
print('min:', find_min([10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 2, 4, 6, 8, 10, 12]))
print('min:', find_min([10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0]))
print('min:', find_min([0, 2, 4, 6, 8, 10, 12]))
print('min:', find_min([0]))

# 위의 알고리즘을 살짝 고치면 최소점이 여러개인 경우도 찾을 수 있다.
def find_rightmost_min(seq: list) -> tuple[int, int]:
    lo = 0
    hi = len(seq)

    # Loop invariant:
    #   lo < hi
    #   seq[lo] 는 강한단조감소하는 수열 + 최소점들의 일부
    #   seq[hi] 는 강한단조증가하는 수열 + 최소점들의 일부
    while lo + 1 < hi:
        print(seq[lo:hi])

        mid = (lo + hi)//2
        if seq[mid - 1] >= seq[mid]:
            # 강한단조감소 or 최소점
            lo = mid
        else:
            # 강한단조증가
            hi = mid

    print(seq[lo:hi])
    return (seq[lo], lo)

print('rightmost min:', find_rightmost_min([10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 0, 0, 2, 4, 6, 8, 10, 12, 14]))
print('rightmost min:', find_rightmost_min([10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 0, 0, 2, 4, 6, 8, 10, 12]))
print('rightmost min:', find_rightmost_min([10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 0, 0]))
print('rightmost min:', find_rightmost_min([0, 0, 0, 0, 2, 4, 6, 8, 10, 12]))
print('rightmost min:', find_rightmost_min([0, 0, 0, 0]))
