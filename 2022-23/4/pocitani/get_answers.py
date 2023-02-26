import sys
import re

root = {'a': (1, 0), 'd': (0, 1, 1), 'b': (1, 1), 'c': (2, 0), 'k': (5, 3, 4, 3, 0), 'm': (5, 6, 1, 0, 0), 'e': (5, 0, 3, 4, 0), 'j': (3, 3, 6, 1, 0), 'h': (2, 2, 4, 0), 'i': (0, 3, 2, 0), 'g': (5, 0, 4, 0), 'f': (5, 1, 0), 'n': (4, 1, 0), 'l': (5, 4, 0)}

previous = []
lineList = []
for line in sys.stdin:
    striped = line.strip()
    if (striped != ""):
        lineList.append(striped)
        previous.append(striped)

run = True
while run:
    run = False
    for fn, r in root.items():
        reg = fn + r"\((\d)" + (r",(\d)" * (len(r) - 2)) + r"\)"
        for i in range(len(lineList)):
            match = re.search(reg, lineList[i])
            if match is not None:
                run = True
                left = r[-1]
                for j in range(len(match.groups())):
                    left += r[j] * int(match.groups()[j])
                left %= 7
                lineList[i] = lineList[i][:match.start()] + str(left) + lineList[i][match.end():]

for i in range(len(lineList)):
    line = lineList[i]
    sides = line.strip().split("=")
    if (sides[1].strip() == ""):
        print(previous[i].split("=")[0].strip(), "=", sides[0])
    else:
        if int(sides[0].strip()) != int(sides[1].strip()):
            print("Not equal")

