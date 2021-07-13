count = int(input())
nums = list(map(int, input().split()))
print(sum(nums) / max(nums) * 100 / count)
