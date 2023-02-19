import random
import sys

seed = int(sys.argv[1])

random.seed(seed)

alphabet = "qwertzuiopasdfghjklyxcvbnm"

print("15")

for diff in range(1, 4):
    for _ in range(5):
        memory_size = random.randint(10,10 * 10*diff)
        print(memory_size)
        words = random.randint(50*(10**diff), 100*(10**diff))
        # if diff == 3:
            # words *= 6
        print(words)
        consts = [
            "".join([random.choice(alphabet) for _ in range(random.randint(1 + 2*diff, 1+2**diff))]) for _ in range(random.randint(2, 10))
        ]
        for _ in range(words):
            print(random.choice(consts) + "".join([random.choice(alphabet) for _ in range(random.randint(1 + 2*diff, 1 + 3*diff))]))

        print(len(alphabet))
        for a in alphabet:
            print(a, random.randint(1, 10))
