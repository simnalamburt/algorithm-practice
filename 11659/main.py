N, M = map(int, input().split())

partialSums = [0] * (N + 1)

partialSum = 0
for i, num in enumerate(map(int, input().split())):
    partialSum += num
    partialSums[i + 1] = partialSum

# Invariant:
#   partialSums[i] = sum(nums[:i])
#   partialSums[end] - partialSums[start] = sum(nums[start:end])

for _ in range(M):
    i, j = map(int, input().split())
    start = i - 1
    end = j
    print(partialSums[end] - partialSums[start])
