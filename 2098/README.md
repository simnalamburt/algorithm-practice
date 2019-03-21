TSP
========
[`recursive-opt.c`](recursive-opt.c)가 제일 빠른 솔루션이다.
문제 링크: <https://www.acmicpc.net/problem/2098>

```bash
# Build
gcc recursive-opt.c -o recursive-opt -O2 -Wall -Wextra -Wpedantic -Werror -lm -static -std=c11
gcc recursive.c -o recursive -O2 -Wall -Wextra -Wpedantic -Werror -lm -static -std=c11
gcc iterative.c -o iterative -O2 -Wall -Wextra -Wpedantic -Werror -lm -static -std=c11
./inputgen > input2

# Run
time (for _ in {1..100}; do ./recursive-opt < input2 > /dev/null; done)  #
time (for _ in {1..100}; do ./recursive < input2 > /dev/null; done)      # ~20ms/ops
time (for _ in {1..100}; do ./iterative < input2 > /dev/null; done)      # ~27ms/ops
time (python3 recursive.py < input2)                                      # ~1600ms/ops
time (python3 iterative.py < input2)                                      # ~3130ms/ops
```
