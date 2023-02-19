#include <deque>
#include <iostream>
#include <map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

#define set unordered_set
#define int long long

void print_graph(map<int, int> graph[], int N) {
  for (int i = 0; i < N; i++) {
    cout << i << ":";
    for (auto it = graph[i].begin(); it != graph[i].end(); ++it) {
      cout << " " << it->first;
    }
    cout << endl;
  }
  cout << endl;
}

long getMin(map<int, int> graph[], int N, int v) {
  auto connections = graph[v];
  long minimal = 1000000000000000007;
  for (auto ite = connections.begin(); ite != connections.end(); ++ite) {
    if (minimal > ite->second && ite->second != 0) {
      minimal = ite->second;
    }
  }
  if (minimal == 1000000007)
    minimal = 0;

  return minimal;
}

int getMax(map<int, int> graph[], int N, int v) {
  auto connections = graph[v];
  int max;
  max = 0;
  for (auto ite = connections.begin(); ite != connections.end(); ++ite) {
    if (max < ite->second)
      max = ite->second;
  }
  return max;
}

vector<int> getLastVertices(map<int, int> graph[], int N) {
  vector<int> result;
  for (int i = 0; i < N; ++i) {
    if (graph[i].size() == 1)
      result.push_back(i);
  }
  return result;
}

bool graphEmpty(map<int, int> graph[], int N) {
  for (int i = 0; i < N; i++) {
    if (!graph[i].empty())
      return false;
  }
  return true;
}

int task(map<int, int> graph[], int N) {
  int result;
  result = 0;
  while (!graphEmpty(graph, N)) {
    vector<int> lastV;
    lastV = getLastVertices(graph, N);
    while (!lastV.empty()) {
      int c = lastV.back();
      lastV.pop_back();
      auto c_it = graph[c].begin();
      if (c_it == graph[c].end())
        continue;
      int v = c_it->first;
      int v_min = getMin(graph, N, v);
      result += v_min;
      vector<int> toDelete;
      for (auto it = graph[v].begin(); it != graph[v].end(); ++it) {
        if (v_min < it->second) {
          graph[v][it->first] -= v_min;
          graph[it->first][v] -= v_min;
        } else {
          graph[it->first].erase(v);
          toDelete.push_back(it->first);
        }
      }
      for (auto it = toDelete.rbegin(); it != toDelete.rend(); ++it)
        graph[v].erase(*it);
    }
  }
  return result;
}

signed main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    int N;
    cin >> N;
    map<int, int> graph[N];
    for (int j = 1; j < N; j++) {
      int A, B, L;
      cin >> A >> B >> L;
      graph[A][B] = L;
      graph[B][A] = L;
    }
    cout << task(graph, N) << endl;
  }
  return 0;
}
