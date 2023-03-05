#include <bits/stdc++.h>
#include <iomanip>

#define ll long long
#define ld long double

using namespace std;

void printArr(vector<int> v) {
  for (int i : v)
    cout << i << " ";
  cout << endl;
}

auto arMean(vector<ld> v) {
  int len = v.size();
  ll first = 0;
  for (ld n : v) {
    first += n;
  }
  return (ld)first / len;
}

vector<vector<int>> tahy(vector<int> arr, int sum) {
  vector<vector<int>> res;
  for (int i = 0; i < arr.size(); ++i) {
    if (arr[i] == sum) {
      vector<int> nArr = arr;
      nArr.erase(nArr.begin() + i);
      res.push_back(nArr);
    }
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

ld taskUtil(vector<int> current, int result, map<vector<int>, ld> &data,
            int best) {
  auto it = data.find(current);
  if (it != data.end())
    return it->second;

  map<int, vector<vector<int>>> available;

  for (int i = 2; i < 13; i++)
    available[i] = tahy(current, i);

  vector<ld> results;
  for (int i = 1; i < 7; i++) {
    for (int j = 1; j < 7; j++) {
      // if (available[i + j].size() > 1) {
      //   printArr(current);
      //   cout << i + j << endl;
      // }
      ld bestRes = 0.0;
      for (vector<int> v : available[i + j]) {
        // if (available[i + j].size() > 1) {
        //   printArr(v);
        //   printProbSum(v);
        // }
        ld res = taskUtil(v, result + i + j, data, best);
        if (res > bestRes)
          bestRes = res;
        // if (available[i + j].size() > 1)
        //   cout << res << endl;
        // results.push_back(res);
      }
      // if (available[i + j].size() > 1)
      //   cout << endl;
      if (available[i + j].size() == 0) {
        if (result > best)
          results.push_back(100.0);
        else
          results.push_back(0.0);
        continue;
      }
      results.push_back(bestRes);
    }
  }
  ld mean = arMean(results);
  data[current] = mean;
  return mean;
}

ld task(int S, int N) {
  vector<int> start = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  map<vector<int>, ld> data;
  ld result = taskUtil(start, 0, data, S);
  return result;
}

signed main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    int S, N;
    cin >> S >> N;
    cout << setprecision(9);
    cout << task(S, N) << endl;
  }
}
