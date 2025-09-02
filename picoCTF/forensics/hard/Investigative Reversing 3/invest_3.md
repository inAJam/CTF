# Investigative Reversing 3
Same as the previous ones, we check the binary using `cutter`. This binary is quite similar to the previous one.
```C
for (i = 0; i < 100; i = i + 1) {
    if ((i & 1U) == 0) {
        for (j = 0; (int32_t)j < 8; j = j + 1) {
            cStack_7d = codedChar((uint64_t)j, 
                                    (uint64_t)(uint32_t)(int32_t)*(char *)((int64_t)&flagBuf + (int64_t)(i / 2)), 
                                    (uint64_t)(uint32_t)(int32_t)origCharBuf);
            fputc((int32_t)cStack_7d, encoded);
            fread(&origCharBuf, 1, 1, original);
        }
    } else {
        fputc((int32_t)origCharBuf, encoded);
        fread(&origCharBuf, 1, 1, original);
    }
}
```
The only difference is that after every 8 bytes where the LSB of the original is modified, one byte is maintained as is. The character encoding however is exactly the same as the previous challenge.  
```C
uint8_t codedChar(unsigned long long j, int64_t modFlagBuf, int64_t origCharBuf)
{
    uint8_t a;
    unsigned long long b;
    int64_t c;
    
    a = (uint8_t)modFlagBuf;
    if ((int32_t)j != 0) {
        a = (uint8_t)((int32_t)(char)a >> ((uint8_t)j & 0x1f));
    }
    return (uint8_t)origCharBuf & 0xfe | a & 1;
}
```
So we just write a simple python script to recover the flag. We start from the **0x2d3** byte and then go through the characters to get the flag.  
```python
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
```
```bash
thermos@valkyrie:~/CTFs$ python3 picoCTF/forensics/hard/Investigative\ Reversing\ 3/recover_flag.py 
Recovered flag: picoCTF{4n0th3r_L5b_pr0bl3m_00000000000001f8ae184}
```  
Flag: **picoCTF{4n0th3r_L5b_pr0bl3m_00000000000001f8ae184}**