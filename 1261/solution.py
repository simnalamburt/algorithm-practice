from sys import stdin

WIDTH, HEIGHT = map(int, input().split())
WORLD = stdin.read() # `WORLD[y*(WIDTH+1)+x]` 이렇게 접근해야함

def dijkstra() -> int:
    COST = [[0xFFFF]*WIDTH for _ in range(HEIGHT)]
    COST[0][0] = 0

    deque = [(0, 0)]
    for iter in range(1000000):
        # TODO
        debug = 1708 <= iter <= 1709
        debug = False
        if debug:
            print('iter =', iter);
            print('sum(costs) =', sum(sum(row) for row in COST))
            print('len(deque) =', len(deque))
            print('deque[:5] =', deque[:5])
            print('deque[-5:] =', deque[-5:])

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
                if debug: print('Push Start', (x, y)) # TODO
                deque.insert(0, (x, y))
            else:
                if debug: print('Push End', (x, y)) # TODO
                deque.append((x, y))
        if debug: print() # TODO

print(dijkstra())
