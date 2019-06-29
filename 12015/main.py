from bisect import bisect_left

def read():
    count = int(input())
    yield from (int(word) for word in input().split())

def solution(inputs) -> int:
    # seqs[i] 에는 길이가 i인 부분수열중 맨 뒤 항의 값이 들어있음
    seqs = []

    for num in inputs:
        idx = bisect_left(seqs, num)
        if idx == len(seqs):
            seqs.append(num)
        else:
            seqs[idx] = num

    return len(seqs)

if __name__ == '__main__':
    print(solution(read()))
