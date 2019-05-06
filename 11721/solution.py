from math import ceil
msg = input()
for i in range(ceil(len(msg) / 10)):
    print(msg[i*10:(i+1)*10])
