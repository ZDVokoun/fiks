import sys
import string
import re
from typing import Dict
import collections

basic = {'ᛋ': '(', 'ᛪ': ')', 'ᚷ': '0', 'ᛧ': '1', 'ᛶ': '2', 'ᛸ': '3', 'ᛴ': '4', 'ᛟ': '5', 'ᛒ': '6', '=': '=', '\n': '\n', ' ': ' ', ',': ',', 'ᛜ': 'a', 'ᛃ': 'b', 'ᛝ': 'c', 'ᛦ': 'd', '𓁸': 'e', '𓂒': 'f', '𓂄': 'g', '𓃇': 'h', '𓂏': 'i', '𓂆': 'j', '𓂇': 'k', '𓇽': 'l', '𓄸': 'm', '𓈑': 'n'}
# basic = {
#     # Zavorky
#     "ᛋ": "(",
#     "ᛪ": ")",
#
#     # Odhad cisel
#     "ᚷ": "0",
#     "ᛧ": "1",
#     "ᛶ": "2",
#     "ᛸ": "3",
#     "ᛴ": "4",
#     "ᛟ": "5",
#     "ᛒ": "6",
#
#     # Citelne
#     "=": "=",
#     "\n": "\n",
#     " ": " ",
#     ",": ","
# }

toChoose = string.ascii_letters

translated = ""

for line in sys.stdin:
    for ch in line:
        if ch not in basic:
            basic[ch] = toChoose[0] 
            toChoose = toChoose[1:]
        translated += basic[ch]

# print(basic)

# print()

print(translated)
