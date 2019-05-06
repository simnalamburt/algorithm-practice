A,B,C=map(int,input().split());print(f'''{(A+B)%C}
{(A%C+B%C)%C}
{(A*B)%C}
{(A%C*B%C)%C}''')
