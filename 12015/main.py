import os
import mmap
from bisect import bisect_left

def read():
    '''
    stdin을 문제 스펙에 맞게 읽는 함수. stdin이 mmap(2)가 가능하지 않은 유형의
    파일인 경우 mmap(2)으로 파일을 읽는다.
    '''
    try:
        stdin = mmap.mmap(0, os.stat(0).st_size, mmap.MAP_PRIVATE, mmap.PROT_READ)
    except OSError as e:
        # mmap(2) 실패 이외의 이유로 실패했다면 예외 전파
        if e.errno != 22:
            raise

        # mmap(2) 가 불가능한 유형의 파일이여서 실패했다면 .read()로 입력 읽기
        count = int(input())
        yield from (int(word) for word in input().split())
        return

    # mmap(2) 활용하여 빠르게 입력 처리
    idx = stdin.find(b'\n')
    count = int(stdin[:idx])
    for _ in range(count):
        pos, idx = idx, stdin.find(b' ', idx + 1)
        yield int(stdin[pos:idx])

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
