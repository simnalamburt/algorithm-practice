import string

line = input()
count_dict = {ch:0 for ch in string.ascii_uppercase}
for ch in line:
    count_dict[ch.upper()] += 1
result = sorted(count_dict.items(), reverse=True, key=lambda pair: pair[1])
print(result[0][0] if result[0][1] != result[1][1] else '?')
