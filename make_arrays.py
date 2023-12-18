import random

for i in range (400):
    made = set()
    perm = [*range(0, 10000)]
    for j in range(0, 10000):
        r = random.choice(perm)
        perm.remove(r)
        print(r, end=" ")
    print(end="\n")
