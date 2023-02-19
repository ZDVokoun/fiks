#include <csignal>
#include <cstdint>
#include <deque>
#include <iostream>
#include <map>
#include <optional>
#include <set>
#include <thread>
#include <vector>

#define sh int

using namespace std;

// vector<pair<int, int>> *ptr;

// void signalHandler(int sig) {
//   for (auto it : *ptr) {
//     cout << it.first << " " << it.second;
//   }
// }

void topologicalSortUtil(int v, const vector<set<int>> &graph,
                         vector<int> &stack, bool visited[]) {
  visited[v] = true;

  for (auto ver : graph[v])
    if (!visited[ver])
      topologicalSortUtil(ver, graph, stack, visited);

  stack.push_back(v);
}

void topologicalSort(const vector<set<int>> &graph, vector<int> &stack) {
  bool visited[graph.size()];
  for (int i = 0; i < graph.size(); i++)
    visited[i] = false;
  for (int i = 0; i < graph.size(); i++)
    if (visited[i] == false && graph[i].size() > 0)
      topologicalSortUtil(i, graph, stack, visited);
}

struct QueueItem {
  int x;
  int y;
  int len;
  int part;
};

auto task(vector<vector<int>> map, int H, int W, pair<int, int> *result) {
  vector<set<int>> graph(H * W);
  vector<pair<int, int>> relNeigh = {
      pair<int, int>(0, 1),
      pair<int, int>(1, 0),
      pair<int, int>(0, -1),
      pair<int, int>(-1, 0),
  };
  vector<vector<int>> islands(H, vector<int>(W));
  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++)
      islands[y][x] = -1;
  }
  int cur_is = 0;
  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++) {
      if (islands[y][x] == -1) {
        deque<pair<int, int>> q;
        q.push_back(pair<int, int>(x, y));
        while (!q.empty()) {
          pair<int, int> cur = q.front();
          q.pop_front();
          int cur_x = cur.first, cur_y = cur.second;
          islands[cur_y][cur_x] = cur_is;
          for (auto n : relNeigh) {
            int dx = n.first, dy = n.second;
            if (cur_y + dy < 0 || cur_y + dy >= H || cur_x + dx < 0 ||
                cur_x + dx >= W)
              continue;
            if (map[cur_y + dy][cur_x + dx] == map[cur_y][cur_x] &&
                islands[cur_y + dy][cur_x + dx] == -1) {
              q.push_back(pair<int, int>(cur_x + dx, cur_y + dy));
            } else if (islands[cur_y + dy][cur_x + dx] != cur_is &&
                       islands[cur_y + dy][cur_x + dx] != -1) {
              if (map[cur_y + dy][cur_x + dx] > map[cur_y][cur_x]) {
                graph[islands[cur_y + dy][cur_x + dx]].insert(cur_is);
              } else if (map[cur_y + dy][cur_x + dx] < map[cur_y][cur_x]) {
                graph[cur_is].insert(islands[cur_y + dy][cur_x + dx]);
              }
            }
          }
        }
        cur_is++;
      }
    }
  }
  vector<int> topologicallySorted;
  topologicalSort(graph, topologicallySorted);
  vector<int> longest;
  for (int i = 0; i < graph.size(); i++) {
    vector<int> stack = topologicallySorted;
    vector<int> dist[graph.size()];
    dist[i].push_back(i);
    while (!stack.empty()) {
      int c = stack.back();
      stack.pop_back();
      if (dist[c].size() > 0) {
        for (int n : graph[c]) {
          if (dist[n].size() < dist[c].size() + 1) {
            dist[n] = dist[c];
            dist[n].push_back(n);
          }
        }
      }
    }
    for (int j = 0; j < graph.size(); j++)
      if (longest.size() < dist[j].size())
        longest = dist[j];
  }

  if (longest.size() == 0) {
    (*result) = pair<int, int>(0, 0);
    return;
  }
  // for (int i : longest)
  //   cout << i << " ";
  // cout << endl;
  // for (int y = 0; y < H; y++) {
  //   for (int x = 0; x < W; x++) {
  //     cout << islands[y][x] << " ";
  //   }
  //   cout << endl;
  // }
  // for (auto it : paths) {
  //   cout << it.first << " -";
  //   for (int i : it.second)
  //     cout << " " << i;
  //   cout << endl;
  // }
  int ans = INT32_MAX;
  for (int y = 0; y < H; y++) {
    for (int x = 0; x < W; x++) {
      if (islands[y][x] == longest[0]) {
        deque<QueueItem> q;
        vector<vector<bool>> visited(H, vector<bool>(W));
        q.push_back(QueueItem{x, y, 0, 1});
        visited[y][x] = true;
        while (!q.empty()) {
          QueueItem cur = q.front();
          q.pop_front();
          // cout << cur.x << " " << cur.y << endl;
          if (islands[cur.y][cur.x] == longest[longest.size() - 1]) {
            ans = min(ans, cur.len);
            continue;
          }
          for (pair<int, int> n : relNeigh) {
            int dx = n.first, dy = n.second;
            if (cur.y + dy < 0 || cur.y + dy >= H || cur.x + dx < 0 ||
                cur.x + dx >= W)
              continue;
            if (!visited[cur.y + dy][cur.x + dx]) {
              if (islands[cur.y + dy][cur.x + dx] == longest[cur.part]) {
                q.push_back(QueueItem{cur.x + dx, cur.y + dy, cur.len + 1,
                                      cur.part + 1});
                visited[cur.y + dy][cur.x + dx] = true;

              } else if (islands[cur.y][cur.x] ==
                         islands[cur.y + dy][cur.x + dx]) {
                q.push_back(
                    QueueItem{cur.x + dx, cur.y + dy, cur.len + 1, cur.part});
                visited[cur.y + dy][cur.x + dx] = true;
              }
            }
          }
        }
      }
    }
  }
  // cout << longest.size() - 1 << " " << ans << endl;
  (*result) = pair<int, int>(longest.size() - 1, ans);
  // return pair<int, int>(longest.size() - 1, ans);
}

signed main() {
  int N;
  cin >> N;
  thread threads[N];
  vector<pair<int, int>> results(N);
  // ptr = &results;
  // signal(SIGABRT, signalHandler);
  for (int i = 0; i < N; i++) {
    int H, W;
    cin >> H >> W;
    int numberOfWays = 0, partsDown = 0, flatParts = 0;
    vector<vector<int>> map(H, vector<int>(W));
    for (int y = 0; y < H; y++)
      for (int x = 0; x < W; x++)
        cin >> map[y][x];
    threads[i] = thread(task, map, H, W, &results[i]);
    // if (partsDown < res.first ||
    //     (partsDown == res.first && flatParts > res.second)) {
    //   // numberOfWays = res.numberOfWays;
    //   partsDown = res.first;
    //   flatParts = res.second;
    // }
  }
  for (int i = 0; i < N; i++)
    threads[i].join();
  for (int i = 0; i < N; i++)
    cout << results[i].first << " " << results[i].second << endl;
  return 0;
}
