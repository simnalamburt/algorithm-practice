// gcc solution.c -O2 -Wall -Wextra -Wpedantic -Werror
#include <stdio.h>

int main() {
  //
  // Handle input
  //
  int N, M;
  scanf("%d%d", &N, &M);

  long DATA[N];
  char buffer[M + 1];
  for (int i = 0; i < N; ++i) {
    scanf("%*s%s", buffer);

    long sum = 0;
    for (int n = 0; n < M; ++n) {
      if (buffer[n] == 'Y') {
        sum += 1l << n;
      }
    }

    DATA[i] = sum;
  }

  //
  // Brute-force
  //
  int songs_max = 0;
  int guitars_min = -1;
  for (int bitset_guitars = 0; bitset_guitars < 1 << N; ++bitset_guitars) {
    long bitset_songs = 0;

    for (int i = 0; i < N; ++i) {
      if (bitset_guitars & (1 << i)) {
        bitset_songs |= DATA[i];
      }
    }

    const int count_guitars = __builtin_popcount(bitset_guitars);
    const int count_songs = __builtin_popcountl(bitset_songs);

    if (count_songs > songs_max) {
      songs_max = count_songs;
      guitars_min = count_guitars;
    } else if (count_songs == songs_max && count_guitars < guitars_min) {
      guitars_min = count_guitars;
    }
  }

  printf("%d\n", guitars_min);
}
