import os
import mmap
from dataclasses import dataclass
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

@dataclass(frozen=True)
class Seq:
    '''
    수열을 표현하는 자료구조. 길이와 수열의 맨 마지막 원소 정보만 들고있다.
    '''
    len: int
    last: int

    def __lt__(self, other_num: int):
        '''
        bisect_left 용 메서드
        '''
        return self.last < other_num

def solution(numbers) -> int:
    # Invariant: sorted_seqs는 항상 seq.last 의 오름차순으로 정렬되어있음
    sorted_seqs = []

    # 나머지 숫자 입력
    for num in numbers:
        # Invariant 검사
        # TODO: Comment the line below
        assert all(sorted_seqs[i].last <= sorted_seqs[i+1].last for i in range(len(sorted_seqs)-1))

        idx = bisect_left(sorted_seqs, num)

        # max 함수 정의상 len이 길이가 제일 큰것중 가장 앞에있는것(last가 가장
        # 작은것)을 반환하게됨.
        #
        # Reference:
        #   https://docs.python.org/3/library/functions.html#max
        max_len = max((seq.len for seq in sorted_seqs[:idx]), default=0)

        # 새 부분수열을 sorted_seqs의 적절한 위치에 삽입
        sorted_seqs.insert(idx, Seq(len=max_len+1, last=num))

        # TODO: 중복제거, 리스트에서 빼도 되는거 제거

    return max(sorted_seqs, key=lambda e:e.len).len

if __name__ == '__main__':
    print(solution(read()))
