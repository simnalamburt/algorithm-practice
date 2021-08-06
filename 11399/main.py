N = int(input())

# a < b 인 상황에서 아래와 같은 두 수열이 있을때:
#     X = [... a b ...]
#     Y = [... b a ...]
#
# f(X) - f(Y) = a - b < 0, f(X) < f(Y) 이다.
# f(X)가 최소가 되려면 X가 오름차순 정렬되어야 한다.
P = sorted(map(int, input().split()))

answer = sum((N - i)*p for i, p in enumerate(P))
print(answer)
