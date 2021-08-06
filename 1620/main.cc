#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
  int N, M;
  scanf("%d%d", &N, &M);

  vector<string> names;
  names.reserve(N);

  unordered_map<string, int> name_to_num;

  for (int i = 1; i <= N; ++i) {
    char buf[64];
    scanf("%s", buf);

    string name { buf };
    names.push_back(name);
    name_to_num[name] = i;
  }

  for (int i = 0; i < M; ++i) {
    char buf[64];
    scanf("%s", buf);

    string query { buf };
    if ('A' <= query[0] && query[0] <= 'Z') {
      printf("%d\n", name_to_num[query]);
    } else {
      printf("%s\n", names[stoi(query) - 1].c_str());
    }
  }
}
