[PI](https://algospot.com/judge/problem/read/PI)
========

- recursion.rs : 클로저 재귀 + 메모이제이션. Interior mutability 사용함.
- iter.rs : 재귀 없이 품.

```bash
# 실행
rustc -o a -O recursion.rs
rustc -o a -O iter.rs

time ./a < input
time ./a < input2
./inputgen | time ./a


# 유닛테스트 실행
rustc -o a --test recursion.rs && ./a
rustc -o a --test iter.rs && ./a
```
