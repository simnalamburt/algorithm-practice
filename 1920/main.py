input()
A = {*input().split()}
input()
print('\n'.join(
    ('1' if X in A else '0')
    for X in input().split()
))
