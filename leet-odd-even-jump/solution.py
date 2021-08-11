class Solution:
    def oddEvenJumps(self, arr: list[int]) -> int:
        if not arr:
            return 0

        DP: list[tuple[bool, bool]] = [None] * len(arr)
        DP[-1] = (True, True)

        for i in reversed(range(len(arr) - 1)):
            bigger = [j for j in range(i + 1, len(arr)) if arr[i] <= arr[j]]
            smaller = [j for j in range(i + 1, len(arr)) if arr[i] >= arr[j]]

            DP[i] = (
                bigger and DP[min(bigger, key=lambda j:arr[j])][1],
                smaller and DP[max(smaller, key=lambda j:arr[j])][0],
            )

        return sum(1 for is_odd_good, _ in DP if is_odd_good)
