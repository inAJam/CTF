import string
ALPHABET = string.ascii_lowercase[:16]  # 'abcdefghijklmnop'
LOWERCASE_OFFSET = ord("a")

def b16_decode(encoded):
    assert len(encoded) % 2 == 0
    decoded = ""
    for i in range(0, len(encoded), 2):
        first = format(ALPHABET.index(encoded[i]), '04b')
        second = format(ALPHABET.index(encoded[i + 1]), '04b')
        byte = first + second
        decoded += chr(int(byte, 2))
    return decoded

def unshift(c, k):
    t1 = ord(c) - LOWERCASE_OFFSET
    t2 = ord(k) - LOWERCASE_OFFSET
    return ALPHABET[(t1 - t2) % len(ALPHABET)]

enc = 'dcebcmebecamcmanaedbacdaanafagapdaaoabaaafdbapdpaaapadanandcafaadbdaapdpandcac'

for key in ALPHABET:
    decrypt = ""
    for i, c in enumerate(enc):
        decrypt += unshift(c, key[i % len(key)])
    print(key,'->',b16_decode(decrypt))