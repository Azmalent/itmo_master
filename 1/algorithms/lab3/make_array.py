import random, os

with open('array.txt', 'w') as f:
    for i in range(1000):
        n = random.randint(-1000, 1000)
        f.write(str(n) + '\n')