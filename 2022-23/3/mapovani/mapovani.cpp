/*
 * V této úloze šlo o implementaci datové struktury trie, která přesně
 * požadavek úlohy umožňuje splnit v lineárním čase
 * */

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>

using namespace std;

struct trieNode {
  struct trieNode *child[500];
  int freq;
};

struct trieNode *getNode(void) {
  struct trieNode *node = new trieNode;
  node->freq = 1;
  for (int i = 0; i < 256; ++i)
    node->child[i] = NULL;
  return node;
}

void insert(struct trieNode *root, string str) {
  int len = str.length();
  struct trieNode *current = root;

  for (int i = 0; i < len; ++i) {
    // cout << current->freq;
    int index = str[i];
    if (!current->child[index])
      current->child[index] = getNode();
    else
      (current->child[index]->freq)++;
    current = current->child[index];
  }
}

struct StackItem {
  struct trieNode *root;
  string prefix;
  int cost;
};

void printPrefixes(map<int, vector<string>> *prefixes) {
  for (auto i = prefixes->begin(); i != prefixes->end(); ++i) {
    cout << i->first;
    for (auto it = i->second.begin(); it != i->second.end(); ++it) {
      cout << " " << *it;
    }
    cout << "\n";
  }
}

map<int, vector<string>> findPrefixes(string arr[], int n,
                                      map<char, int> alphabetCost) {
  map<int, vector<string>> result;
  struct trieNode *root = getNode();
  string prefix;
  root->freq = 0;
  for (int i = 0; i < n; ++i)
    insert(root, arr[i]);
  // cout << root->child['i'] << endl;
  vector<StackItem> queue;
  queue.push_back(StackItem{root, prefix, 0});
  while (!queue.empty()) {
    StackItem current = queue.back();
    queue.pop_back();
    // cout << stack[0].prefix;
    // cout << current.root->freq;
    if (current.root == NULL) {
      // cout << "test" << endl;
      continue;
    }

    if (current.root->freq == 1) {
      // cout << "test2" << endl;
      result[current.cost].push_back(current.prefix);
      continue;
    }

    for (int i = 0; i < 256; ++i) {
      if (current.root->child[i] != NULL) {
        // cout << current.root->freq << " test3" << endl;
        queue.push_back(StackItem{current.root->child[i],
                                  current.prefix + char(i),
                                  current.cost + alphabetCost[char(i)]});
      }
    }
  }
  return result;
}

signed main() {
  int T;
  cin >> T;
  for (int i = 0; i < T; ++i) {
    int I, M, P;
    map<char, int> alphabet;
    cin >> I >> M;
    string strs[M];
    for (int j = 0; j < M; ++j)
      cin >> strs[j];
    cin >> P;
    for (int j = 0; j < P; ++j) {
      char Z;
      int Y;
      cin >> Z >> Y;
      alphabet[Z] = Y;
    }
    vector<string> results;
    map<int, vector<string>> prefixes = findPrefixes(strs, M, alphabet);
    // printPrefixes(&prefixes);
    int size = 0;
    // if (prefixes.find(37) != prefixes.end())
    //   cout << prefixes[37][1] << endl;
    for (auto it = prefixes.begin(); it != prefixes.end(); ++it) {
      sort(it->second.begin(), it->second.end());
      for (auto itt = it->second.begin(); itt != it->second.end(); ++itt) {
        size += it->first;
        if (size > I)
          goto theend;
        else
          results.push_back(*itt);
      }
    }
  theend:
    cout << results.size() << endl;
    for (int j = 0; j < results.size(); ++j)
      cout << results[j] << endl;
  }
  return 0;
}
