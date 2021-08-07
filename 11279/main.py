# heap[i] is parent of heap[i*2 + 1] and heap[i*2 + 2]
heap = []

def heap_push(n: int) -> None:
    idx = len(heap)
    heap.append(n)

    # Fix heap
    while idx != 0:
        parent = (idx - 1)//2
        if heap[parent] < heap[idx]:
            heap[parent], heap[idx] = heap[idx], heap[parent]
            idx = parent
        else:
            return

def heap_pop() -> int:
    ret = heap[0]
    heap[0] = heap[-1]
    heap.pop()
    size = len(heap)

    # Fix heap
    idx = 0
    while True:
        l = idx*2 + 1
        r = idx*2 + 2
        if r < size:
            child = l if heap[l] > heap[r] else r
        elif r == size:
            child = l
        else: # r > size, no child
            break
        if heap[idx] < heap[child]:
            heap[idx], heap[child] = heap[child], heap[idx]
            idx = child
        else:
            break

    return ret

N = int(input())
for _ in range(N):
    n = int(input())
    if n == 0:
        print(heap_pop() if heap else 0)
    else:
        heap_push(n)
