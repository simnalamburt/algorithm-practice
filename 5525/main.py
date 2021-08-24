from typing import List

def getPI(query: str) -> List[int]:
    length = len(query)
    pi = [0]*length
    begin = 1
    matched = 0
    while begin + matched < length:
        if query[matched] == query[begin + matched]:
            matched += 1
            pi[begin + matched - 1] = matched
        elif matched == 0:
            begin += 1
        else:
            begin = begin + matched - pi[matched - 1]
            matched = pi[matched - 1]
    return pi

def count_occurrence(string: str, query: str) -> int:
    pi = getPI(query)
    begin = 0
    matched = 0
    count = 0
    while begin + matched < len(string):
        if query[matched] == string[begin + matched]:
            matched += 1
            if matched == len(query):
                count += 1
                begin += matched - pi[matched - 1]
                matched = pi[matched - 1]
        elif matched == 0:
            begin += 1
        else:
            begin += matched - pi[matched - 1]
            matched = pi[matched - 1]
    return count

N = int(input())
input()
S = input()

print(count_occurrence(S, 'I' + 'OI'*N))
