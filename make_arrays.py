import random

for i in range (100):
    for j in range(100):
        print(random.randint(0, 9), end=" ")
    print(end="\n")