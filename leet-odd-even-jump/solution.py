from bisect import bisect, insort

class Solution:
    def oddEvenJumps(self, arr: list[int]) -> int:
        if not arr:
            return 0

        DP: list[tuple[bool, bool]] = [None] * (len(arr) - 1) + [(True, True)]
        sorted1: list[tuple[int, int]] = [(arr[-1], len(arr) - 1)]
        sorted2: list[tuple[int, int]] = [(arr[-1], -(len(arr) - 1))]

        for i in reversed(range(len(arr) - 1)):
            idx1 = bisect(sorted1, (arr[i], i))
            idx2 = bisect(sorted2, (arr[i], -i))

            DP[i] = (
                DP[sorted1[idx1][1]][1] if idx1 < len(sorted1) else False,
                DP[-sorted2[idx2 - 1][1]][0] if idx2 > 0 else False,
            )

            sorted1.insert(idx1, (arr[i], i)) # TODO: use BST
            sorted2.insert(idx2, (arr[i], -i)) # TODO: use BST

        return sum(1 for is_odd_good, _ in DP if is_odd_good)
