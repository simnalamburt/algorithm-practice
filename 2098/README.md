TSP
========
<https://www.acmicpc.net/problem/2098>

```bash
# Build
./inputgen > input2
gcc recursive.c -o recursive -O2 -Wall -Wextra -Wpedantic -Werror -std=c11
gcc iterative.c -o iterative -O2 -Wall -Wextra -Wpedantic -Werror -std=c11

# Run
time (python3 recursive.py < input2)                        # ~1600ms/ops
time (python3 iterative.py < input2)                        # ~3130ms/ops
time (for _ in {1..100}; do; ./recursive < input2; done)    # ~20ms/ops
time (for _ in {1..100}; do; ./iterative < input2; done)    # ~27ms/ops
```
