#include <cstdio>
#include <set>

int main() {
  int T;
  scanf("%d", &T);
  for (int _ = 0; _ < T; ++_) {
    std::multiset<int> bst;

    int k;
    scanf("%d", &k);
    for (int i = 0; i < k; ++i) {
      char cmd;
      int n;
      scanf(" %c%d", &cmd, &n);
      if (cmd == 'I') {
        // insert n
        bst.insert(n);
      } else if (n == 1) {
        // pop max
        if (!bst.empty()) {
          bst.erase(std::prev(bst.cend()));
        }
      } else {
        // pop min
        if (!bst.empty()) {
          bst.erase(bst.cbegin());
        }
      }
    }

    if (bst.empty()) {
      puts("EMPTY");
    } else {
      printf("%d %d\n", *bst.crbegin(), *bst.cbegin());
    }
  }
}
