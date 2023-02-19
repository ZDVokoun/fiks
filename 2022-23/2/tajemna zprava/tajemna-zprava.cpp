#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

string bytes_to_string(vector<char> input) {
  string result(input.begin(), input.end());
  return result;
}

vector<char> decode_bytes(vector<char> input) {
  vector<char> result;
  int pos = 0;
  int len = input.size();
  while (pos < len) {
    result.push_back(((input[pos + 1] & 0b110000) >> 4) +
                     ((input[pos] & 0b111111) << 2));
    if (pos + 2 < len) {
      result.push_back(((input[pos + 2] & 0b111100) >> 2) +
                       ((input[pos + 1] & 0b1111) << 4));
      if (pos + 3 < len) {
        result.push_back(input[pos + 3] + ((input[pos + 2] & 0b11) << 6));
      }
    }
    pos += 4;
  }
  for (int i = result.size() - 1; i > 0; i--) {
    result[i - 1] = result[i - 1] ^ result[i];
  }
  return result;
}

string decode_string(string input) {
  vector<string> alphabet{
      "a",   "i",  "u",  "e",  "o",  "ka",  "ki",  "ku", "ke", "ko", "sa",
      "shi", "su", "se", "so", "ta", "chi", "tsu", "te", "to", "na", "ni",
      "nu",  "ne", "no", "ha", "hi", "fu",  "he",  "ho", "ma", "mi", "mu",
      "me",  "mo", "ya", "yu", "yo", "ra",  "ri",  "ru", "re", "ro", "wa",
      "ga",  "gi", "gu", "ge", "go", "za",  "ji",  "zu", "ze", "zo", "ba",
      "bi",  "bu", "be", "bo", "pa", "pi",  "pu",  "pe", "po"};
  unordered_map<string, char> decode_map;
  vector<char> bytes;

  // Init hashmap
  for (char i = 0; i < alphabet.size(); i++) {
    decode_map[alphabet[i]] = i;
  }

  // Convert string to bytes
  int i = 0, j = 1;
  int len = input.size();
  while (i < len) {
    string part = input.substr(i, j);
    if (j == 1 && (part == " " || part == "." || part == "!" || part == "?")) {
      i++;
      continue;
    }
    auto it = decode_map.find(input.substr(i, j));
    if (it == decode_map.end()) {
      j++;
    } else {
      bytes.push_back(it->second);
      i += j, j = 1;
    }
  }
  return bytes_to_string(decode_bytes(bytes));
}

signed main() {
  std::string input = "";
  do {
    std::getline(std::cin, input);

    if (input.length() < 3) {
      return 0;
    }

    std::cout << decode_string(input) << std::endl;
  } while (true);
}
