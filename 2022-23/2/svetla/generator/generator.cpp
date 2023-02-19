#include <iostream>
#include <random>
#include <stdlib.h>

struct difficulty {
  int test_count;
  int max_n;
  int max_l;
  int points;
};

difficulty difficulties[] = {{10, 20, 1, 2},
                             {10, 10000, 100, 5},
                             {1, 1000000, 1000, 7},
                             {1, 1000000, 1000000000, 10}};

using namespace std;

using ll = long long int;

namespace Random {
struct PRNG {
  const ll a, b, m;
  ll x;
  PRNG(ll a, ll b, ll m) : a(a), b(b), m(m), x(0) {}
  void seed(ll x0) { x = x0; }
  void next() { x = (a * x + b) % m; }
  // interval [min, max]
  ll uniform_dist(ll min, ll max) {
    ll val = x % (max - min + 1) + min;
    next();
    return val;
  }
};
PRNG _prng(4240399, 1519267, 9509609);
ll get(ll min, ll max) { return _prng.uniform_dist(min, max); }
} // namespace Random

void generate_problem(int max_n, int max_l) {
  int a, b, dist;
  int n = Random::get(1, max_n);
  printf("%d\n", n);
  for (int i = 1; i < n; ++i) {
    a = i;                     // adding new leaf node
    b = Random::get(0, i - 1); // connecting leaf node to random node in tree
    dist = Random::get(1, max_l);
    printf("%d %d %d\n", a, b, dist);
  }
}

int main(int argc, const char *argv[]) {

  uint32_t seed = argc > 1 ? atoi(argv[1]) : (unsigned int)time(0);
  Random::_prng.seed(seed);

  int tests = 0;
  int max_difficulty = sizeof(difficulties) / sizeof(*difficulties);
  if (argc > 2) {
    max_difficulty = atoi(argv[2]);
  }
  for (int i = 0; i < max_difficulty; ++i)
    tests += difficulties[i].test_count;
  printf("%d\n", tests);

  for (int i = 0; i < max_difficulty; ++i)
    for (int t = 0; t < difficulties[i].test_count; ++t)
      generate_problem(difficulties[i].max_n, difficulties[i].max_l);
}
