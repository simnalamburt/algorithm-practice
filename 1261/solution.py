from sys import stdin

WIDTH, HEIGHT = map(int, input().split())
WORLD = stdin.read() # `WORLD[y*(WIDTH+1)+x]` 이렇게 접근해야함

def dijkstra() -> int:
    COST = [[0xFFFF]*WIDTH for _ in range(HEIGHT)]
    COST[0][0] = 0

    deque = [(0, 0)]
    while True:
        x0, y0 = deque.pop()

        # 도착함
        if x0 == WIDTH - 1 and y0 == HEIGHT - 1:
            return COST[HEIGHT - 1][WIDTH - 1]

        cost = COST[y0][x0]

        # 인접한 점들 순회
        for x, y in [(x0, y0-1), (x0-1, y0), (x0+1, y0), (x0, y0+1)]:
            if not (0 <= x < WIDTH and 0 <= y < HEIGHT):
                continue

            is_wall = WORLD[y*(WIDTH+1)+x] == '1'
            new_cost = cost + (1 if is_wall else 0)

            if COST[y][x] <= new_cost:
                continue

            COST[y][x] = new_cost

            # 코스트가 무조건 0 아니면 1이어서 이렇게 해도 됨
            if is_wall:
                deque.insert(0, (x, y))
            else:
                deque.append((x, y))

print(dijkstra())
