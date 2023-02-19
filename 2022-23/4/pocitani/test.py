import sys
import string
import re
from typing import Dict
import collections

basic = {
    # Zavorky
    "ᛋ": "(",
    "ᛪ": ")",

    # Odhad cisel
    "ᚷ": "0",
    "ᛧ": "1",
    "ᛶ": "2",
    "ᛸ": "3",
    "ᛴ": "4",
    "ᛟ": "5",
    "ᛒ": "6",

    # Citelne
    "=": "=",
    "\n": "\n",
    " ": " ",
    ",": ","
}

variables = {}

toChoose = string.ascii_letters

translated = ""

for line in sys.stdin:
    for ch in line:
        if ch not in basic:
            basic[ch] = toChoose[0] 
            toChoose = toChoose[1:]
        translated += basic[ch]


newTranslated = "\n".join(sorted(translated.split("\n"), key=lambda x: len(x)))

print(newTranslated)

print()

print("== Substitution ==")

print(basic)

print()

print("== Repeating patterns == ")

toReplace: Dict[str,str] = {}

for line in newTranslated.strip().split("\n"):
    con = True
    while con:
        print(line)
        con = False
        res = line.split("=")
        if (line.split("=")[1].strip() != ""):
            toReplace[res[0].strip()] = res[1].strip()
        for i, j in toReplace.items():
            newline = re.sub(re.escape(i), j, line)
            if newline != line:
                con = True
                line = newline

print()
print(toReplace)

for i in toReplace.keys():
    if collections.Counter(i)["("] == 1:
        print(i, "=", toReplace[i])



