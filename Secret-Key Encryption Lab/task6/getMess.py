from sys import argv

p1 = bytearray("This is a known message!",encoding='utf-8')
c1 = bytearray.fromhex("a469b1c502c1cab966965e50425438e1bb1b5f9037a4c159")
c2 = bytearray.fromhex("bf73bcd3509299d566c35b5d450337e1bb175f903fafc159")

p2 = bytearray(x ^ y ^ z for x, y, z in zip(p1, c1, c2))

print(p2.decode('utf-8'))