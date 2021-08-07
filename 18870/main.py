N = int(input())
X = [*map(int, input().split())]
n_to_i = {n: i for i, n in enumerate(sorted({*X}))}
print(' '.join(str(n_to_i[n]) for n in X))

# NOTE:
#   bisect 사용법 기억안나서 한번 찾아봤음
#   bisect 쓸만한 문제 아니었음
#   .. for .. in .. 순서 바꿔썼음
#   join하기전에 str로 바꾸는거 까먹음
