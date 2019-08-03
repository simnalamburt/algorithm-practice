```bash
./inputgen > input2

python3 solution.py < input2

clang -O2 solution.c -Wall -Wextra -Wpedantic -Werror
./a.out < input2
```
