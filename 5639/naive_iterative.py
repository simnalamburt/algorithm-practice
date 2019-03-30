from sys import stdin

# 트리 초기화
TREE = [[int(line), None, None] for line in stdin]
for new_idx in range(1, len(TREE)):
    # TREE[0:idx - 1] 은 트리인 상태고 TREE[idx] 를 삽입해야함
    idx = 0
    while True:
        value, left, right = TREE[idx]
        new_value = TREE[new_idx][0]

        next_idx = left if new_value < value else right
        if next_idx is None:
            TREE[idx][1 if new_value < value else 2] = new_idx
            # Return
            break
        else:
            # Tail recursion
            idx = next_idx

# 트리 순회
tasks = [(False, 0)]
while tasks:
    is_print, val = tasks.pop()

    if val is None:
        continue
    if is_print:
        print(val)
        continue

    value, left, right = TREE[val]
    tasks.append((True, value))
    tasks.append((False, right))
    tasks.append((False, left))
