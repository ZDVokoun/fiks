#include <bits/stdc++.h>

#define ll long long

using namespace std;
const map<int, int> prob = {{1, 0}, {2, 1}, {3, 2}, {4, 3},  {5, 4},  {6, 5},
                            {7, 6}, {8, 5}, {9, 4}, {10, 3}, {11, 2}, {12, 1}};

void printArr(vector<int> v) {
  for (int i : v)
    cout << i << " ";
  cout << endl;
}

int getProb(vector<int> v) {
  int res = 0;
  for (int n = 2; n <= 12; n++) {
    bool exists = false;
    for (int i = 0; i < v.size(); i++) {
      if (exists)
        break;
      if (v[i] == n) {
        exists = true;
        break;
      }
      for (int j = i + 1; j < v.size(); j++) {
        if (v[i] + v[j] == n) {
          exists = true;
          break;
        }
      }
    }
    res += exists * prob.at(n) + 1;
  }
  return res;
}

void printProbSum(vector<int> v) {
  int sum = 0;
  for (int n : v)
    sum += prob.at(n);
  cout << sum << endl;
}

auto arMean(vector<double> v) {
  int len = v.size();
  ll first = 0;
  for (double n : v) {
    first += n;
  }
  return (double)first / len;
}

vector<vector<int>> tahy(vector<int> arr, int sum) {
  vector<vector<int>> res;
  for (int i = 0; i < arr.size(); ++i) {
    if (arr[i] == sum) {
      vector<int> nArr = arr;
      nArr.erase(nArr.begin() + i);
      res.push_back(nArr);
      break;
    }
    for (int j = i + 1; j < arr.size(); ++j) {
      if (arr[i] + arr[j] == sum) {
        vector<int> nArr2 = arr;
        nArr2.erase(nArr2.begin() + j);
        nArr2.erase(nArr2.begin() + i);
        res.push_back(nArr2);
        break;
      }
    }
  }
  return res;
}

vector<vector<int>> tahy2(vector<int> arr, int sum) {
  vector<vector<int>> res;
  int bestProb = 255;
  int bestProbb = 0;
  for (int i = 0; i < arr.size(); ++i) {
    if (arr[i] == sum) {
      vector<int> nArr = arr;
      nArr.erase(nArr.begin() + i);
      res = {nArr};
      // break;
    }
    for (int j = i + 1; j < arr.size(); ++j) {
      if (arr[i] + arr[j] == sum) {
        vector<int> nArr2 = arr;
        nArr2.erase(nArr2.begin() + j);
        nArr2.erase(nArr2.begin() + i);
        if (bestProbb < getProb(nArr2)) {
          bestProbb = getProb(nArr2);
          bestProb = prob.at(arr[i]) + prob.at(arr[j]);
          res = {nArr2};
        } else if (bestProbb == getProb(nArr2)) {
          if (bestProb > prob.at(arr[i]) + prob.at(arr[j])) {
            res = {nArr2};
            bestProb = prob.at(arr[i]) + prob.at(arr[j]);
          }
          // else if (bestProb == prob.at(arr[i]) + prob.at(arr[j])) {
          //   res.push_back(nArr2);
          // }
        }
        // bestProb = prob.at(arr[i]) + prob.at(arr[j]);
        // res = {nArr2};
        // res.push_back(nArr2);
      }
      // if (arr[i] + arr[j] == sum &&
      //     bestProb > prob.at(arr[i]) + prob.at(arr[j])) {
      //   vector<int> nArr2 = arr;
      //   nArr2.erase(nArr2.begin() + j);
      //   nArr2.erase(nArr2.begin() + i);
      //   // bestProb = prob.at(arr[i]) + prob.at(arr[j]);
      //   // res = {nArr2};
      //   res.push_back(nArr2);
      // }
    }
  }
  return res;
}

auto taskUtil(vector<int> current, int result, map<vector<int>, double> &data,
              int best) {
  auto it = data.find(current);
  if (it != data.end())
    return it->second;

  map<int, vector<vector<int>>> available;

  for (int i = 2; i < 13; i++)
    available[i] = tahy(current, i);

  vector<double> results;
  for (int i = 1; i < 7; i++) {
    for (int j = 1; j < 7; j++) {
      // if (available[i + j].size() > 1) {
      //   printArr(current);
      //   cout << i + j << endl;
      // }
      double bestRes = 0.0;
      for (vector<int> v : available[i + j]) {
        // if (available[i + j].size() > 1) {
        //   printArr(v);
        //   printProbSum(v);
        // }
        bestRes = max(bestRes, taskUtil(v, result + i + j, data, best));
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
  double mean = arMean(results);
  data[current] = mean;
  return mean;
}

double task(int S, int N) {
  vector<int> start = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  map<vector<int>, double> data;
  double result = taskUtil(start, 0, data, S);
  return result;
}

signed main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; i++) {
    int S, N;
    cin >> S >> N;
    cout << task(S, N) << endl;
  }
}
