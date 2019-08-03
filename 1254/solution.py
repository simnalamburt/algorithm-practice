#!/usr/bin/env python3

def is_palindrome(string: str) -> bool:
    length = len(string)
    for i in range(length//2):
        if string[i] != string[length - i - 1]:
            return False
    return True

string = input()
length = len(string)

minimum = length - 1
for i in range(length -1):
    if is_palindrome(string[i:]):
        minimum = i
        break

answer = minimum + length
print(answer)
