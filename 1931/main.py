N = int(input())
meetings = sorted(tuple(map(int, input().split())) for _ in range(N))

next_meeting = float('inf')
count = 0
for start, end in reversed(meetings):
    if end <= next_meeting:
        next_meeting = start
        count += 1
print(count)
