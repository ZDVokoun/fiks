#include <algorithm>
#include <bits/stdc++.h>
#include <utility>

#define mapvec map<string, vector<string>>
#define mapset map<string, set<string>>
#define pairstr pair<string, string>
#define vecpair vector<pairstr>
#define setstr set<string>

using namespace std;

bool areDisjoint(const set<string> &set1, const set<string> &set2) {
  auto it1 = set1.begin();
  auto it2 = set2.begin();

  while (it1 != set1.end() && it2 != set2.end()) {
    if (*it1 < *it2) {
      ++it1;
    } else if (*it2 < *it1) {
      ++it2;
    } else {
      return false;
    }
  }

  return true;
}

bool addItem(const mapset &notBoth, const mapset &both, setstr &currentSet,
             string item) {
  auto itnot = notBoth.find(item);
  auto it = both.find(item);
  if (itnot == notBoth.end() || areDisjoint(itnot->second, currentSet)) {
    currentSet.insert(item);
    if (it != both.end()) {
      for (auto required : it->second)
        if (!addItem(notBoth, both, currentSet, required))
          return false;
    }
    return true;
  } else
    return false;
}

pair<bool, set<string>> task(const vecpair &pairs, const mapset &notBoth,
                             const mapset &both, setstr &currentSet,
                             int current) {
  if (current >= pairs.size())
    return make_pair(true, currentSet);
  setstr first, second;
  pair<bool, set<string>> firstRes, secondRes;
  first = currentSet, second = currentSet;
  if (addItem(notBoth, both, first, pairs[current].first))
    firstRes = task(pairs, notBoth, both, first, current + 1);
  if (addItem(notBoth, both, second, pairs[current].second))
    secondRes = task(pairs, notBoth, both, second, current + 1);
  if (firstRes.first)
    return firstRes;
  else if (secondRes.first)
    return secondRes;
  else
    return make_pair(false, currentSet);
}

int main(int argc, char *argv[]) {
  int t;
  cin >> t;
  for (int i = 0; i < t; i++) {
    int n, m, k, l;
    cin >> n >> m >> k >> l;
    set<string> items;
    for (int j = 0; j < n; j++) {
      string item;
      cin >> item;
      items.insert(item);
    }
    vecpair pairs;
    for (int j = 0; j < m; j++) {
      pairstr itempair;
      cin >> itempair.first >> itempair.second;
      pairs.push_back(itempair);
    }
    mapset notBoth;
    for (int j = 0; j < k; j++) {
      string first, second;
      cin >> first >> second;
      notBoth[first].insert(second);
      notBoth[second].insert(first);
    }
    mapset both;
    for (int j = 0; j < l; j++) {
      string first, second;
      cin >> first >> second;
      both[first].insert(second);
    }
    setstr start;
    auto result = task(pairs, notBoth, both, start, 0);
    if (result.first) {
      cout << "ANO";
      for (auto item : result.second)
        cout << " " << item;
    } else
      cout << "NE";
    cout << endl;
  }

  return 0;
}
