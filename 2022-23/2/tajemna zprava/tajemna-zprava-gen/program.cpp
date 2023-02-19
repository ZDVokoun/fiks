#include <iostream>
#include <string>
#include <vector>

const std::string encode_bytes(std::vector<unsigned char> data) {
  std::vector<std::string> alphabet{
      "a",   "i",  "u",  "e",  "o",  "ka",  "ki",  "ku", "ke", "ko", "sa",
      "shi", "su", "se", "so", "ta", "chi", "tsu", "te", "to", "na", "ni",
      "nu",  "ne", "no", "ha", "hi", "fu",  "he",  "ho", "ma", "mi", "mu",
      "me",  "mo", "ya", "yu", "yo", "ra",  "ri",  "ru", "re", "ro", "wa",
      "ga",  "gi", "gu", "ge", "go", "za",  "ji",  "zu", "ze", "zo", "ba",
      "bi",  "bu", "be", "bo", "pa", "pi",  "pu",  "pe", "po"};

  size_t len = data.size();
  std::string ret = "";

  unsigned char sum = 0;
  unsigned int pos = 0;
  while (pos < len) {
    if (sum > 64) {
      ret += " ";
    }

    sum += data[pos];
    ret += alphabet[(data[pos] & 0xfc) >> 2];

    if (pos + 1 < len) {
      ret +=
          alphabet[((data[pos] & 0x03) << 4) + ((data[pos + 1] & 0xf0) >> 4)];

      if (pos + 2 < len) {
        ret += alphabet[((data[pos + 1] & 0x0f) << 2) +
                        ((data[pos + 2] & 0xc0) >> 6)];
        ret += alphabet[data[pos + 2] & 0x3f];
      } else {
        ret += alphabet[(data[pos + 1] & 0x0f) << 2];
        ret += ".";
      }
    } else {
      ret += alphabet[(data[pos + 0] & 0x03) << 4];
      ret += sum > 128 ? "!" : "?";
    }

    pos += 3;
  }

  return ret;
}

const std::string encode_string(const std::string &input) {
  const unsigned char *input_bytes = (unsigned char *)input.c_str();

  std::vector<unsigned char> result_bytes;
  for (size_t i = 0; i < input.length() - 1; i++) {
    unsigned char next = input_bytes[i] ^ input_bytes[i + 1];
    result_bytes.push_back(next);
  }
  result_bytes.push_back(input_bytes[input.length() - 1]);

  return encode_bytes(result_bytes);
}

int main() {
  std::string input = "";
  do {
    std::getline(std::cin, input);

    if (input.length() < 3) {
      return 0;
    }

    std::cout << encode_string(input) << std::endl;
  } while (true);
}
