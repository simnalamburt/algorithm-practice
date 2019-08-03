```bash
xz -dk input4.xz

# 3 0 2 197 respectively
python3 solution.py < input1
python3 solution.py < input2
python3 solution.py < input3
python3 solution.py < input4

# C solution
clang -std=c11 -O2 solution.c -Wall -Wextra -Wpedantic -Werror
./a.out < input4
```
