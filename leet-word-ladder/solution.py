from heapq import heappop, heappush

def isDifferBySingleLetter(A: str, B: str) -> bool:
    diff = 0
    for a, b in zip(A, B):
        if a != b:
            diff += 1
    return diff == 1

class Solution:
    def ladderLength(self, beginWord: str, endWord: str, wordList: list[str]) -> int:
        vertices = [beginWord] + wordList
        V = len(vertices)
        matrix = [[False]*V for _ in range(V)]
        for i in range(V):
            for j in range(i + 1, V):
                matrix[i][j] = matrix[j][i] = isDifferBySingleLetter(vertices[i], vertices[j])

        # Dijkstra's Algorithm
        DIST = [float('inf')]*V
        try:
            target = vertices.index(endWord)
        except ValueError:
            return 0

        DIST[0] = 1
        Q = [(1, 0)]
        while Q:
            dist, idx = heappop(Q)
            if dist < DIST[idx]:
                continue

            # Found answer
            if idx == target:
                break

            new_dist = dist + 1
            for i in range(V):
                if not matrix[idx][i]:
                    continue
                # Invariant: i is neighbor
                if DIST[i] <= new_dist:
                    continue
                DIST[i] = new_dist
                heappush(Q, (new_dist, i))

        if DIST[target] == float('inf'):
            return 0
        return DIST[target]

# NOTE: if 뒤에 ':' 빼먹음, False를 false라고 씀, inf 써야하는 자리에 -inf 써버림, DIST[target] 대신 DIST[-1] 반환
