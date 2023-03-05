#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

#define ll long long
#define ld long double

using namespace std;

struct Druh {
  ld C;
  ld T;
  ld B;
  int i;
};

// Porovnavaci funkce pro sort a lower_bound
bool compare(const Druh &a, const Druh &b) { return a.T / a.B > b.T / b.B; }

// Funkce na reseni Gaussovou eliminaci pro matici 2x2 (par druhu masa
// se chova zde jako matice)
pair<ld, vector<pair<int, ld>>> solve(Druh a, Druh b, ld ZT, ld ZB) {
  vector<pair<int, ld>> res;
  ld bCoefficient = (a.T * ZB - a.B * ZT) / (a.T * b.B - b.T * a.B);
  ld aCoefficient = (ZT - b.T * bCoefficient) / a.T;
  if (aCoefficient < 0.0 || bCoefficient < 0.0)
    return make_pair(10e8, res);
  res.push_back(make_pair(b.i + 1, bCoefficient));
  res.push_back(make_pair(a.i + 1, aCoefficient));
  ld cost = a.C * aCoefficient + b.C * bCoefficient;
  return make_pair(cost, res);
}

pair<ld, vector<pair<int, ld>>> task(vector<Druh> &druhy, ld ZT, ld ZB) {
  ld minCost = 10e8;
  vector<pair<int, ld>> bestType;
  bool idealTypeExists = false;

  // Nalezeni indexu k rozdeleni do dvou skupin
  auto it = lower_bound(druhy.begin(), druhy.end(), Druh{0.0, ZT, ZB}, compare);
  if (it == druhy.end())
    return make_pair(0.0, vector<pair<int, ld>>());
  int ind = it - druhy.begin();
  // Jestli lze pouzit jen jeden druh masa
  if (it->T / it->B == ZT / ZB) {
    idealTypeExists = true;
    bestType = vector<pair<int, ld>>{make_pair(ind + 1, ZT / it->T)};
    minCost = ZT / it->T * it->C;
  }
  for (int i = idealTypeExists ? ind + 1 : ind; i < druhy.size(); i++) {
    for (int j = 0; j < ind; j++) {
      auto res = solve(druhy[i], druhy[j], ZT, ZB);
      if (res.first < minCost) {
        minCost = res.first;
        bestType = res.second;
      }
    }
  }

  return make_pair(minCost, bestType);
}

int main(int argc, char *argv[]) {
  int N, K;
  cin >> N >> K;
  vector<Druh> druhy;
  for (int i = 0; i < N; i++) {
    Druh maso;
    cin >> maso.C >> maso.T >> maso.B;
    maso.i = i;
    druhy.push_back(maso);
  }
  sort(druhy.begin(), druhy.end(), compare);
  for (int i = 0; i < K; i++) {
    ld ZT, ZB;
    cin >> ZT >> ZB;

    pair<ld, vector<pair<int, ld>>> res = task(druhy, ZT, ZB);
    if (res.second.size() == 0)
      cout << "Nelze" << endl;
    else {
      cout << res.first << " " << res.second.size();
      for (pair<int, ld> vybrane : res.second)
        cout << " " << vybrane.first << " " << vybrane.second;
      cout << endl;
    }
  }
  return 0;
}
