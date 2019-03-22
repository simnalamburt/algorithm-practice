from unittest import TestCase, main

from main import Seq, solution
from inputgen import dummy_input

def solution_naive(numbers) -> int:
    sequences = set()
    for num in numbers:
        sequences |= {
            Seq(len=seq.len+1, last=num) for seq in sequences if seq.last < num
        } | {Seq(len=1, last=num)}
    return max(sequences, key=lambda e:e.len).len

class TestStringMethods(TestCase):
    '''
    테스트코드
    '''
    def test_small_input(self):
        answers = {
            (50, 0): 9,
            (50, 1): 11,
            (50, 2): 11,
            (50, 3): 11,
            (50, 4): 11,
            (50, 5): 10,
        }

        self.assertEqual(solution([10, 20, 10, 30, 20, 50]), 4)
        for (count, seed), actual_answer in answers.items():
            expected_answer = solution(dummy_input(count, seed))
            self.assertEqual(expected_answer, actual_answer)

    def test_with_naive_solution(self):
        for count in [10, 30, 50]:
            for seed in [100, 200, 300, 400, 500]:
                self.assertEqual(
                    solution(dummy_input(count, seed)),
                    solution_naive(dummy_input(count, seed)),
                )

if __name__ == '__main__':
    main()
