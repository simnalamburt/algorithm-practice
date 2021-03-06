node_count, query_count = map(int, input().split())

# Graph
indices = [None] + [set() for _ in range(node_count)] # 1-base Array[Set[int]]
values = [None] * (node_count + 1) # 1-base Array[int]

# Tree
root = None
parents = [None] * (node_count + 1) # 1-base Array[int]
children = [None] * (node_count + 1) # 1-base Array[Set[int]]
depths = [None] * (node_count + 1) # 1-base Array[int]

for _ in range(node_count - 1):
    u, v = map(int, input().split())
    indices[u].add(v)
    indices[v].add(u)
for i in range(1, node_count + 1):
    values[i] = int(input())
root = int(input())


def init_tree(node: int, depth: int = 0, parent: int = 0) -> None:
    '''
    주어진 루트로 트리 부모자식관계, 깊이 정보를 초기화함.
    Time complexity: θ(sizeofsubtree(node))
    '''
    parents[node] = parent
    c = indices[node] - {parent}
    children[node] = c
    depths[node] = depth
    for child in c:
        init_tree(child, depth+1, node)

def init_depth(node: int, depth: int = 0) -> None:
    '''
    주어진 서브트리의 깊이 정보를 초기화함
    Time complexity: θ(sizeofsubtree(node))
    '''
    depths[node] = depth
    for child in children[node]:
        init_depth(child, depth+1)

def dump_state() -> None:
    '''
    State 변수들을 모두 출력
    '''
    print(f'indices:    {indices[1:]}')
    print(f'values:     {values[1:]}')
    print(f'parents:    {parents[1:]}')
    print(f'children:   {children[1:]}')
    print(f'depths:     {depths[1:]}')
    print()

def change_root(new_root: int) -> None:
    '''
    트리의 루트를 new_root로 바꿈
    Time complexity: θ(distance(old_root, new_root))
    '''
    global root
    if new_root == root:
        return

    old_root = root
    root = new_root

    parents[new_root], current, next = 0, new_root, parents[new_root]
    while next != 0:
        # 기존 부모와의 연결 해제
        children[next] -= {current}
        # 새 부모 연결 생성
        children[current].add(next)
        parents[next], current, next = current, next, parents[next]

    init_depth(new_root)

def each_subtree(node: int):
    '''
    node의 서브트리(node 포함) 안에 있는 모든 정점들을 DFS로 순회하는
    generator를 반환한다.
    Time complexity: θ(sizeofsubtree(node))
    '''
    yield node
    for child in children[node]:
        yield from each_subtree(child)

def each_path(a: int, b: int):
    '''
    a와 b를 잇는 경로(a, b 포함) 상에 있는 모든 정점들을 순회하는 generator를
    반환한다. 순서에는 아무런 보장이 없다.
    Time complexity: θ(distance(a, b))
    '''
    if depths[a] < depths[b]:
        a, b = b, a
    # assert depths[a] >= depths[b]
    for _ in range(depths[a] - depths[b]):
        yield a
        a = parents[a]
    # assert depths[a] == depths[b]
    while a != b:
        yield a
        yield b
        a = parents[a]
        b = parents[b]
    # assert a == b
    yield a

def is_parent_of(a: int, b: int) -> bool:
    '''
    a가 b의 부모인지 검사
    Time complexity: θ(|depth[a] - depth[b]|)
    '''
    depth_a = depths[a]
    while depth_a < depths[b]:
        b = parents[b]
    # assert depths[a] >= depths[b]
    return a == b


# 트리 부모자식관계 초기화
init_tree(root)

for _ in range(query_count):
    cmd, *args = map(int, input().split())
    if cmd == 0:
        # 0 x y: x의 서브트리에 있는 정점들의 가중치를 y로 바꾼다.
        x, y = args
        for node in each_subtree(x):
            values[node] = y
    elif cmd == 1:
        # 1 r: 트리의 루트를 r로 바꾼다.
        r, = args
        change_root(r)
    elif cmd == 2:
        # 2 x y z: x와 y를 잇는 경로에 있는 정점들의 가중치를 z로 바꾼다.
        x, y, z = args
        for node in each_path(x, y):
            values[node] = z
    elif cmd == 3:
        # 3 x: x의 서브트리에 있는 정점들의 가중치의 최솟값을 출력한다.
        x, = args
        print(min(values[node] for node in each_subtree(x)))
        # TODO: 서브트리에 부분min 미리 저장해서 최적화 가능
    elif cmd == 4:
        # 4 x: x의 서브트리에 있는 정점들의 가중치의 최댓값을 출력한다.
        x, = args
        print(max(values[node] for node in each_subtree(x)))
        # TODO: 서브트리에 부분max 미리 저장해서 최적화 가능
    elif cmd == 5:
        # 5 x y: x의 서브트리에 있는 정점들의 가중치를 y만큼 더한다.
        x, y = args
        for node in each_subtree(x):
            values[node] += y
    elif cmd == 6:
        # 6 x y z: x와 y를 잇는 경로에 있는 정점들의 가중치를 z만큼 더한다.
        x, y, z = args
        for node in each_path(x, y):
            values[node] += z
    elif cmd == 7:
        # 7 x y: x와 y를 잇는 경로에 있는 정점들의 가중치의 최솟값을 출력한다.
        x, y = args
        print(min(values[node] for node in each_path(x, y)))
    elif cmd == 8:
        # 8 x y: x와 y를 잇는 경로에 있는 정점들의 가중치의 최댓값을 출력한다.
        x, y = args
        print(max(values[node] for node in each_path(x, y)))
    elif cmd == 9:
        # 9 x y: x의 부모를 y로 바꾼다. 만약 x의 서브트리 안에 정점 y가 존재한다면 이 쿼리를 무시한다.
        x, y = args

        # x의 서브트리 안에 y가 존재하므로 이 쿼리 무시
        if is_parent_of(x, y):
            continue

        # 기존 부모로부터 x를 제거
        old_parent = parents[x]
        indices[x] -= {old_parent}
        indices[old_parent] -= {x}
        parents[x] = None
        children[old_parent] -= {x}

        # y의 자식에 x를 추가
        indices[x].add(y)
        indices[y].add(x)
        parents[x] = y
        children[y].add(x)

        # depth 정보 다시 초기화
        init_depth(x, depths[y] + 1)
    elif cmd == 10:
        # 10 x y: x와 y를 잇는 경로에 있는 정점들의 가중치의 합을 출력한다.
        x, y = args
        print(sum(values[node] for node in each_path(x, y)))
    elif cmd == 11:
        # 11 x: x의 서브트리에 있는 정점들의 가중치의 합을 출력한다.
        x, = args
        print(sum(values[node] for node in each_subtree(x)))
        # TODO: 서브트리에 부분합 미리 저장해서 최적화 가능
