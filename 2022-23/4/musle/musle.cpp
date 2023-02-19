#include <bits/stdc++.h>

#define ll long long

using namespace std;

void printArr(vector<int> v) {
  for (int i : v)
    cout << i << " ";
  cout << endl;
}

auto tahy(vector<int> arr, int sum) {
  vector<vector<int>> res;
  // printArr(arr);
  for (int i = 0; i < arr.size(); ++i) {
    if (arr[i] == sum) {
      vector<int> nArr = arr;
      nArr.erase(nArr.begin() + i);
      res.push_back(nArr);
      break;
    }
    // if (arr[i] > sum / 2)
    //   continue;
    for (int j = i + 1; j < arr.size(); ++j) {
      if (arr[i] + arr[j] == sum) {
        vector<int> nArr2 = arr;
        nArr2.erase(nArr2.begin() + j);
        nArr2.erase(nArr2.begin() + i);
        res.push_back(nArr2);
      }
    }
  }
  return res;
}

pair<ll, ll> taskUtil(vector<int> current, int result,
                      map<vector<int>, pair<ll, ll>> &data) {
  auto it = data.find(current);
  if (it != data.end())
    return it->second;

  map<int, vector<vector<int>>> available;
  ll all = 0;
  ll bigger = 0;
  bool ending = false;

  for (int i = 2; i < 13; i++)
    available[i] = tahy(current, i);

  for (int i = 1; i < 7; i++) {
    for (int j = 1; j < 7; j++) {
      double best = 0.0;
      pair<ll, ll> bestRes = make_pair(0, 0);
      for (vector<int> v : available[i + j]) {
        // printArr(v);
        // cout << result << endl;
        pair<ll, ll> res = taskUtil(v, result + i + j, data);
        bigger += res.first;
        all += res.second;
        // if (best < (double)res.first / res.second) {
        //   best = (double)res.first / res.second;
        //   bestRes = res;
        // }
      }
      if (available[i + j].size() == 0)
        ending = true;

      // else {
      //   bigger += bestRes.first;
      //   all += bestRes.second;
      // }
    }
  }
  if (ending) {
    all++;
    if (result > 22) {
      bigger++;
    }
  }
  data[current] = make_pair(bigger, all);
  return make_pair(bigger, all);
}

double task(int S, int N) {
  vector<int> start = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  map<vector<int>, pair<ll, ll>> data;
  pair<ll, ll> result = taskUtil(start, 0, data);
  cout << result.first << " " << result.second << endl;
  return (double)result.first / result.second;
}

signed main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    int S, N;
    cin >> S >> N;
    cout << task(S, N) * 100 << endl;
  }
}
