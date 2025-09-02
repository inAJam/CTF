def decode_flag(encoded_bmp_path):
    with open(encoded_bmp_path, "rb") as f:
        data = f.read()

    flag = []
    curr_word=0x2d3
    for i in range(100):
        if i%2==0:
            ch = 0
            for j in range(8):
                # Each encoded byte carries 1 LSB bit
                ch |= (data[curr_word] & 1) << j
                curr_word+=1
            flag.append(chr(ch))  # undo the shift from encoder
        else:
            curr_word+=1

    return "".join(flag)


if __name__ == "__main__":
    flag = decode_flag("encoded.bmp")
    print("Recovered flag:", flag)