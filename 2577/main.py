A = int(input())
B = int(input())
C = int(input())
s = str(A*B*C)
for i in range(10):
    print(s.count(str(i)))
