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

bool compare(Druh a, Druh b) {
  if ((ld)a.T / a.B > (ld)b.T / b.B)
    return true;
  else
    return false;
}

pair<ld, vector<pair<int, ld>>> task(vector<Druh> &druhy, ld ZT, ld ZB) {
  ld minCost = 10e8;
  vector<pair<int, ld>> bestType;
  bool idealTypeExists = false;

  auto it = lower_bound(druhy.begin(), druhy.end(), Druh{ZT, ZB}, compare);
  if (it == druhy.begin() || it == druhy.end())
    return make_pair(0.0, vector<pair<int, ld>>());
  int ind = it - druhy.begin();
  if (it->T / it->B == ZT / ZB) {
    idealTypeExists = true;
    bestType = vector<pair<int, ld>>{make_pair(ind + 1, ZT / it->T)};
    minCost = ZT / it->T * it->C;
  }

  // TODO

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
