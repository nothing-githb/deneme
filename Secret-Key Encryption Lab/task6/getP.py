from sys import argv

p1 = bytearray("Yes", encoding='utf-8')
padding = 16 - len(p1) % 16  # padding to match the block size as 128 bit
p1.extend([padding]*padding)
IV = bytearray.fromhex("31323334353637383930313233343536")
IV_NEXT = bytearray.fromhex("31323334353637383930313233343537")
p2 = bytearray(x ^ y ^ z for x, y, z in zip(p1, IV, IV_NEXT))
print(p2.decode('utf-8'), end='')