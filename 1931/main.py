N = int(input())

meetings = []
for _ in range(N):
    start, end = map(int, input().split())
    meetings.append((start, end))
meetings.sort(key=lambda pair:(pair[1], pair[0]))

end_at = 0
count = 0
for start, end in meetings:
    if end_at <= start:
        end_at = end
        count += 1

print(count)
