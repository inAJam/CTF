def decode_flag(encoded_bmp_path):
    with open(encoded_bmp_path, "rb") as f:
        data = f.read()

    # Skip the first 2000 bytes (unchanged copy of original.bmp)
    data = data[2000:]

    flag = []
    for i in range(50):  # flag is always 50 chars
        ch = 0
        for j in range(8):
            # Each encoded byte carries 1 LSB bit
            ch |= (data[i*8 + j] & 1) << j
        flag.append(chr(ch + 5))  # undo "-5" shift from encoder

    return "".join(flag)


if __name__ == "__main__":
    flag = decode_flag("encoded.bmp")
    print("Recovered flag:", flag)