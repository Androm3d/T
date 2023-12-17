import random

for i in range (20):
    for j in range(2**4):
        print(random.randint(0, 9), end=" ")
    print(end="\n")

for i in range (20):
    for j in range(2**10):
        print(random.randint(0, 9), end=" ")
    print(end="\n")

for i in range (20):
    for j in range(2**14):
        print(random.randint(0, 9), end=" ")
    print(end="\n")
    
