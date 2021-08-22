#include <stdio.h>

int main() {
  int N, M;
  scanf("%d%d", &N, &M);
  int partialSums[N + 1];
  int partialSum = 0;
  partialSums[0] = 0;
  for (int i = 0; i < N; ++i) {
    int num;
    scanf("%d", &num);
    partialSum += num;
    partialSums[i + 1] = partialSum;
  }
  // Invariant: partialSums[i] = sum(nums[..i])
  for (int i = 0; i < M; ++i) {
    int i, j;
    scanf("%d%d", &i, &j);
    int start = i - 1, end = j;
    int answer = partialSums[end] - partialSums[start];
    printf("%d\n", answer);
  }
}
