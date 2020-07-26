// gcc solution.c -O2 -Wall -Wextra -Wpedantic -Werror
#include <stdio.h>
#include <inttypes.h>

static int8_t total_guitar_count;
static uint64_t DATA[10];
static int8_t result_songs = 0;
static int8_t result_guitars = -1;

static void callback(uint16_t guitar_bitset);
static void for_each_combination(int8_t pos, uint16_t guitar_bitset);

int main() {
  int8_t song_count;
  scanf("%" SCNi8 "%" SCNi8, &total_guitar_count, &song_count);

  char buffer[song_count + 1];

  for (int8_t i = 0; i < total_guitar_count; ++i) {
    scanf("%*s%s", buffer);

    uint64_t sum = 0;
    for (int8_t n = 0; n < song_count; ++n) {
      char x = buffer[n];
      if (x == 'Y') {
        sum += 1ull << n;
      }
    }

    DATA[i] = sum;
  }

  for_each_combination(total_guitar_count, 0);

  printf("%d\n", result_guitars);
}

// pos:           [0, 10] 범위의 정수
// guitar_bitset: [0, 2^10) 범위의 정수
static void for_each_combination(int8_t pos, uint16_t guitar_bitset) {
  if (pos == 0) {
    callback(guitar_bitset);
    return;
  }

  for_each_combination(pos - 1, guitar_bitset);
  for_each_combination(pos - 1, guitar_bitset + (1 << (pos - 1)));
}

// 매 조합마다 실행되는 함수
static void callback(uint16_t guitar_bitset) {
  uint64_t bits_union = 0;

  for (int8_t i = 0; i < total_guitar_count; ++i) {
    if (guitar_bitset & (1 << i)) {
      bits_union |= DATA[i];
    }
  }

  const int8_t count_guitars = __builtin_popcount(guitar_bitset);
  const int8_t count_songs = __builtin_popcountll(bits_union);

  if (count_songs > result_songs) {
    result_songs = count_songs;
    result_guitars = count_guitars;
  } else if (count_songs == result_songs && count_guitars < result_guitars) {
    result_guitars = count_guitars;
  }
}
