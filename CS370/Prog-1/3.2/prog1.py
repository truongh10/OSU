# this code uses python3 which the flip server does not contain.

from Crypto.Cipher import AES
from sys import argv
from Crypto.Util.Padding import pad 

_, one, two, three = argv 

# check the length of the plaintext if its 21
assert len(one) == 21
data = bytearray(one, encoding = 'utf-8')
ciphertext = bytearray.fromhex(two)
initialiaztionVector = bytearray.fromhex(three)

# read the text file line by line and then get the key
with open('words.txt') as f:
    for i, line in enumerate(f):
        key = line.strip() 

for k in keys:
    k = k.rstrip('\n')
    if len(k) <= 16:
        ke = k + '#'*(16-len(k))
        cipher = AES.new(ke = bytearray(key,encoding = 'utf-8'), mode = AES.MODE_CBC, initialiaztionVector=initialiaztionVector)
        assumption = cipher.encrypt(pad(data,16))
        if assumption == ciphertext:
            print("Found Key: ", ke)
            exit(0)


