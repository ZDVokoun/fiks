import re
from typing import Dict, Tuple
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

done = []

def task(state: Dict[str,str] = {}, root: Dict[str, Tuple[int,int,int]] = {}):
    # print("test")
    newTranslated = sorted(lineList, key=lambda x: len(x))

    run = True
    while run:
        run = False
        for fn, r in root.items():
            reg = fn + r"\((\d)" + (r",(\d)" * (len(r) - 1)) + r"\)"
            for i in range(len(newTranslated)):
                match = re.match(reg, newTranslated[i])
                if match is not None:
                    run = True
                    left = r[-1]
                    for j in range(len(match.groups())):
                        left += r[j] * int(match.groups()[j])
                    left %= 7
                    newTranslated[i] = newTranslated[i][:match.start()] + str(left) + newTranslated[i][match.end():]


    toReplace: Dict[str,str] = state.copy()
    run = True

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
            if i[0] not in ress.keys():
                ress[i[0]] = []
            tpl = eval(i[1:])
            if type(tpl) == type(1):
                tpl = (tpl,)
            ress[i[0]].append((tpl,toReplace[i]))

    print(len(ress))
    if len(ress) == 0:
        print(root)
        return 

    best = ""
    bestN = 0

    for i,j in ress.items():
        if len(j) > bestN and i not in done:
            bestN = len(j)
            best = i

    done.append(best)
    # print(best)

    if best == "":
        print(root)
        return
    roots = []
    for tpl in getAllTuples(len(ress[best][0][0]) + 1):
        # print(tpl)
        isGood = True
        for eq in ress[best]:
            left = tpl[-1]
            for i in range(len(eq[0])):
                left += tpl[i] * eq[0][i]
            left = left % 7
            if left != int(eq[1]):
                isGood = False
                break;
        if (isGood):
            roots.append(tpl)

    for r in roots:
        newRoot = root.copy()
        newRoot[best] = r
        newState = state.copy()
        # for tpl in getAllTuples(len(r) - 1):
        #     res = r[-1]
        #     for i in range(len(tpl)):
        #         res += tpl[i] * r[i]
        #     res = res % 7
        #     newState[best + str(tpl)] = str(res)
        task(newState, newRoot)

task()
