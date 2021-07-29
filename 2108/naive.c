#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int cmp(const void* a, const void* b) {
  // No INT_MIN in the inputs
  return *(const int*)a - *(const int*)b;
}

int main() {
  int N;
  scanf("%d", &N);

  int nums[N], sum = 0, min = 4001, max = -4001, buf[8001] = {0}, *freq = &buf[4000];
  for (int i = 0; i < N; ++i) {
    int n;
    scanf("%d", &n);

    nums[i] = n;
    sum += n;
    ++freq[n];
    if (n < min) { min = n; }
    if (max < n) { max = n; }
  }

  qsort(nums, N, sizeof(int), cmp);

  int max_freq = 0;
  for (int i = -4000; i <= 4000; ++i) {
    if (max_freq < freq[i]) {
      max_freq = freq[i];
    }
  }
  int mode1 = 4001, mode2 = 4001;
  for (int i = -4000; i <= 4000; ++i) {
    if (freq[i] != max_freq) { continue; }
    if (mode1 == 4001) { mode1 = i; }
    else if (mode2 == 4001) { mode2 = i; break; }
  }

  int mean = round((double)sum/(double)N);
  int median = nums[N/2];
  int mode = mode2 == 4001 ? mode1 : mode2;
  int range = max - min;

  printf("%d\n%d\n%d\n%d\n", mean, median, mode, range);
}
