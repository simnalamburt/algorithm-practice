# N: 정점 수, M: 간선 수
N, M = map(int, input().split())

graph = [None] + [[] for _ in range(N)]
for _ in range(M):
    u, v = map(int, input().split())
    graph[u].append(v)
    graph[v].append(u)

visited = [None] + [False]*N

count = 0
for i in range(1, N+1):
    if visited[i]:
        continue
    tasks = [i]
    while tasks:
        task = tasks.pop()
        if visited[task]:
            continue
        visited[task] = True
        tasks += graph[task]
    count += 1

print(count)

# NOTE:
#   set에 pop 메서드 있는지 확신 없었음
#   set에 대고 append 썼음
