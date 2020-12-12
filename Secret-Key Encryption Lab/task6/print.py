import sys

with open(sys.argv[1], 'rb') as f:
    f1 = f.read()

for i in range(0, len(f1)):
    print(f1[i]),
