/* gcc -std=c89 pascal.c -O2 -Wall -Wextra -Wpedantic -Werror */
#include <stdio.h>

static long popcount(long input) {
  long w;

  w = 0;
  while (input) {
    w += 1;
    input &= input - 1;
  }
  return w;
}

int main() {
  long N, M, i, sum, j, bitset_guitars, bitset_songs, songs_max, guitars_min, count_guitars, count_songs;
  long DATA[10];
  char buffer[51];

  /* Handle input */
  scanf("%ld%ld", &N, &M);

  for (i = 0; i < N; ++i) {
    scanf("%*s%s", buffer);

    sum = 0;
    for (j = 0; j < M; ++j) {
      if (buffer[j] == 'Y') {
        sum += 1l << j;
      }
    }

    DATA[i] = sum;
  }

  /* Brute-force */
  songs_max = 0;
  guitars_min = -1;
  for (bitset_guitars = 0; bitset_guitars < 1 << N; ++bitset_guitars) {
    bitset_songs = 0;

    for (j = 0; j < N; ++j) {
      if (bitset_guitars & (1 << j)) {
        bitset_songs |= DATA[j];
      }
    }

    count_guitars = popcount(bitset_guitars);
    count_songs = popcount(bitset_songs);

    if (count_songs > songs_max) {
      songs_max = count_songs;
      guitars_min = count_guitars;
    } else if (count_songs == songs_max && count_guitars < guitars_min) {
      guitars_min = count_guitars;
    }
  }

  printf("%ld\n", guitars_min);
  return 0;
}
