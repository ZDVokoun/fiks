import re
from typing import Dict
import collections
import sys

def getAllTuples(length):
    res = []
    for i in range(7):
        if length == 1:
            res.append((i,))
        else:
            for tpl in getAllTuples(length - 1):
                res.append((*tpl, i))
    return res


lineList = []
for line in sys.stdin:
    lineList.append(line)

newTranslated = sorted(lineList, key=lambda x: len(x))

print("== Repeating patterns == ")

toReplace: Dict[str,str] = {}
run = True

done = []

while run:
    run = False
    for ind in range(len(newTranslated)):
        res = newTranslated[ind].split("=")
        if len(res) < 2:
            continue
        if (newTranslated[ind].split("=")[1].strip() != ""):
            toReplace[res[0].strip()] = res[1].strip()
        for i, j in toReplace.items():
            if len(i) > len(newTranslated[ind]):
                continue
            newline = re.sub(re.escape(i), j, newTranslated[ind])
            if newline != newTranslated[ind]:
                run = True
                newTranslated[ind] = newline

ress = {}

for i in toReplace.keys():
    if collections.Counter(i)["("] == 1:
        print(i)

regexs = []
symbols = []

for i in ress.keys():
    temp = eval(i[1:])
    if type(temp) == "int":
        regexs.append((re.compile(i[0] + r"\(([^\(\)]+)\)"), r"{\g<1> * " + i[0] + "_1 + " + i[0] + "_2}"))
        symbols.append(*[i[0] + "_1", i[0] + "_2"])
    else:
        reText = i[0] + r"\(([^\(\)]+)"
        subText = r"{\g<1> * " + i[0] + "_1"
        symbols.append(i[0] + "_1")
        for j in range(len(temp) - 1):
            reText += r",([^\(\)]+)"
            subText += " + " + i[0] + "_" + str(j + 2)
            symbols.append(i[0] + "_" + str(j + 2))
        reText += r"\)"
        subText += " + " + i[0] + "_" + str(len(temp) + 1) + "}"
        symbols.append(i[0] + "_" + str(len(temp) + 1))
        regexs.append((re.compile(reText), subText))

run = True
while run:
    run = False
    for reg, sub in regexs:
        reg.sub()
        pass

#
# best = ""
# bestN = 0
#
# for i,j in ress:
#     if len(j) > bestN and i not in done:
#         bestN = len(j)
#         best = i
# for tpl in getAllTuples(len(ress[best][0]) + 1):
#     isGood = True
#     for eq in ress[best]:
#         left = tpl[-1]
#         for i in range(len(eq[0])):
#             left += tpl[i] * eq[0][i]
#         if left != eq[1]:
#             isGood = False
#             break;
#     if (isGood):
#         pass
#
#
#
#
# print(ress)
