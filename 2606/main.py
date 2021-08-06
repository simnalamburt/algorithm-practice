vertex_count = int(input())
edge_count = int(input())

graph = [None] + [[] for _ in range(vertex_count)]
for _ in range(edge_count):
    a, b = map(int, input().split())
    graph[a].append(b)
    graph[b].append(a)

visited = [None] + [False]*vertex_count

tasks = [1]
while tasks:
    task = tasks.pop()
    if visited[task]:
        continue
    visited[task] = True
    tasks += graph[task]

print(sum(1 for b in visited if b) - 1)
