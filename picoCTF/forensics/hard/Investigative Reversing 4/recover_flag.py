def decode_flag(encoded_bmp_path):
    with open(encoded_bmp_path, "rb") as f:
        data = f.read()

    flag = []
    curr_word=0x7e3
    for i in range(50):
        if i%5==0:
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
    # flag = decode_flag("Item03_cp.bmp")
    pics = ["Item01_cp.bmp", "Item02_cp.bmp", "Item03_cp.bmp", "Item04_cp.bmp", "Item05_cp.bmp"]
    decoded_parts = [decode_flag(pic) for pic in pics]
    flag = "".join(reversed(decoded_parts))
    print("Recovered flag:", flag)