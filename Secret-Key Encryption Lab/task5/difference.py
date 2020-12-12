#!/usr/bin/python3
with open('file.txt', 'rb') as f:
    f1 = f.read()
with open('dec_cbc.txt', 'rb') as f:
    f2 = f.read()
with open('dec_ecb.txt', 'rb') as f:
    f3 = f.read()
with open('dec_cfb.txt', 'rb') as f:
    f4 = f.read()
with open('dec_ofb.txt', 'rb') as f:
    f5 = f.read()

res = 0

for i in range(min(len(f1), len(f2))):
    if f1[i] != f2[i]:
        res += 1
print("CBC : "+str(res+abs(len(f1)-len(f2))))

res = 0

for i in range(min(len(f1), len(f3))):
    if f1[i] != f3[i]:
        res += 1
print("ECB : "+str(res+abs(len(f1)-len(f3))))

res = 0

for i in range(min(len(f1), len(f4))):
    if f1[i] != f4[i]:
        res += 1
print("CFB : "+str(res+abs(len(f1)-len(f4))))

res = 0

for i in range(min(len(f1), len(f5))):
    if f1[i] != f5[i]:
        res += 1
print("OFB : "+str(res+abs(len(f1)-len(f5))))
