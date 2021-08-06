N, M = map(int, input().split())
setA = {input() for _ in range(N)}
setB = {input() for _ in range(M)}
intersect = setA & setB
print(len(intersect))
print('\n'.join(sorted(intersect)))

# NOTE: set 연산자 확신 없었음, 입출력 스펙 똑바로 안봤음
