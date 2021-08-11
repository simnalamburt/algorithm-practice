class Solution:
    def threeSum(self, nums: list[int]) -> list[list[int]]:
        #
        # Make 'nums' uniq and find duplicates
        #
        nums.sort()

        nums_uniq = []
        dup2 = []
        is_zero_dup3 = False

        last_num = None
        last_num_count = 0
        for num in nums:
            if num == last_num:
                last_num_count += 1

                if last_num_count == 2:
                    dup2.append(num)
                elif last_num_count == 3 and num == 0:
                    is_zero_dup3 = True
            else:
                last_num = num
                last_num_count = 1
                nums_uniq.append(num)

        nums = nums_uniq
        L = len(nums)

        # Create a hash set
        numsSet = set(nums)

        # triplets with different numbers
        A = [
            (nums_uniq[i], nums_uniq[j], rest)
            for i in range(L)
            for j in range(i + 1, L)
            if (rest := -nums_uniq[i]-nums_uniq[j]) in numsSet and nums_uniq[j] < rest
        ]

        # triplets with two same number and different one number
        B = [
            (num, num, rest)
            for num in dup2
            if (rest := -2*num) in numsSet and num != rest
        ]

        # triplets with three same number
        C = [(0, 0, 0)] if is_zero_dup3 else []

        return A + B + C
