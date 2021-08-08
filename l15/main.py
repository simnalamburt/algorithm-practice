class Solution:
    def threeSum(self, nums: list[int]) -> list[list[int]]:
        L = len(nums)
        nums.sort()

        def bsearch(query: int, lo: int, hi: int) -> bool:
            if lo >= hi:
                return False
            mid = (lo + hi)//2
            test = nums[mid]
            if test < query:
                return bsearch(query, mid + 1, hi)
            elif test > query:
                return bsearch(query, lo, mid)
            else:
                return True

        return list({
            (nums[i], nums[j], rest)
            for i in range(L)
            for j in range(i + 1, L)
            if bsearch((rest := -nums[i]-nums[j]), j + 1, L)
        })

print(Solution().threeSum([-1,0,1,2,-1,-4]))
