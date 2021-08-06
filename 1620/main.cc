#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

int main() {
  ios::sync_with_stdio(false);

  int N, M;
  cin >> N >> M;

  vector<string> names;
  names.reserve(N);

  unordered_map<string, int> name_to_num;

  for (int i = 1; i <= N; ++i) {
    string name;
    cin >> name;

    names.push_back(name);
    name_to_num[name] = i;
  }

  for (int i = 0; i < M; ++i) {
    string query;
    cin >> query;

    if ('A' <= query[0] && query[0] <= 'Z') {
      cout << name_to_num[query] << '\n';
    } else {
      cout << names[stoi(query) - 1] << '\n';
    }
  }
}
