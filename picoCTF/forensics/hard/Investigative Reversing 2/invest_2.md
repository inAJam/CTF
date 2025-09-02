# Investigative Reversing 2
Same as before, we feed the binary to `cutter` and then after some clean up we get the decompiled code. In the code we this is the part where the flag is being hidden.
```C
limit = 2000;
    for (iStack_78 = 0; iStack_78 < limit; iStack_78 = iStack_78 + 1) {
        fputc((int32_t)charBuf, encoded_bmp);
        iStack_7c = fread(&charBuf, 1, 1, original_bmp);
    }
    flag_len = fread(&flagBuf, 0x32, 1, flag);
    if (flag_len < 1) {
        puts("flag is not 50 chars");
        exit(0);
    }
    for (i = 0; i < 0x32; i = i + 1) {
        for (j = 0; j < 8; j = j + 1) {
            cStack_7d = codedChar((uint64_t)(uint32_t)j, 
                                  (uint64_t)(uint32_t)(int32_t)(char)(*(char *)((int64_t)&flagBuf + (int64_t)i) + -5), 
                                  (uint64_t)(uint32_t)(int32_t)charBuf);
            fputc((int32_t)cStack_7d, encoded_bmp);
            fread(&charBuf, 1, 1, original_bmp);
        }
    }
    while (iStack_7c == 1) {
        fputc((int32_t)charBuf, encoded_bmp);
        iStack_7c = fread(&charBuf, 1, 1, original_bmp);
    }
```
The above code copies the first 2000 bytes from the **original.bmp** and then pastes it in to the **encoded.bmp**. After this for each byte for the next 50 bytes, it iterates over each bit and encodes them and writes this modified byte to the **encoded.bmp**. Once this is done, it then pastes the remainder of the original onto the encoded image. The below function is used for the encoding.
```C
uint8_t codedChar(unsigned long long j, int64_t modFlagChar, int64_t charBuf)
{
    uint8_t temp;
    unsigned long long var_1ch;
    int64_t var_ah;
    
    temp = (uint8_t)modFlagChar;
    if ((int32_t)j != 0) {
        temp = (uint8_t)((int32_t)(char)temp >> ((uint8_t)j & 0x1f));
    }
    return (uint8_t)charBuf & 0xfe | temp & 1;
}
```
The encoding over here is pretty simple. It first takes the original character and then subtracts it with 5 to get a new character before passing it to the above function.  
The function takes in the new character, the bit position and the byte from the orginal image. It then extracts that bit from the original character and embeds it into the **LSB** of the original image byte before appending the byte to the encoded image. In tghis way it hides the 8 bits for each modified byte of the flag into the 8 bytes of the images, doing so for 50 flag characters.  
The below python code was used to reverse this process and decode the flag.  
```python
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
```
![alt text](image.png)  
Flag: **picoCTF{n3xt_0n300000000000000000000000000394060c}**