# Investigative Reversing 4
Similar to before we try to analyze the binary using `cutter`. However the `ghidra` decompiler in `cutter` is not very clear in what exactly the code does. So keep switching between the `jsdec` and `ghidra` decompilers. This gives us a better picture of whats happening.  
```C
// Ghidra decompiled result

undefined8 main(int argc, char **argv)
{
    undefined8 in_R8;
    undefined8 in_R9;
    char **var_68h;
    int var_5ch;
    undefined4 var_4ch;
    int64_t var_48h;
    int32_t var_14h;
    FILE *stream;
    
    _flag = &var_48h;
    var_4ch = 0;
    _flag_index = &var_4ch;
    stream = (FILE *)fopen(0xbff, 0xbc8);
    if (stream == (FILE *)0x0) {
        puts(0xc08);
    }
    var_14h = fread(_flag, 0x32, 1, stream, in_R8, in_R9, argv);
    if (var_14h < 1) {
        puts(0xc42);
    // WARNING: Subroutine does not return
        exit(0);
    }
    fclose(stream);
    encodeAll();
    return 0;
}

// jsdec decompiled result

int32_t main (int32_t argc, char ** argv) {
    char ** var_68h;
    int32_t var_5ch;
    int64_t var_4ch;
    int64_t var_48h;
    long long signed int var_14h;
    FILE * stream;
    rdi = argc;
    rsi = argv;
    var_5ch = edi;
    var_68h = rsi;
    rax = &var_48h;
    *(flag) = rax;
    var_4ch = 0;
    rax = &var_4ch;
    *(flag_index) = rax;
    rax = fopen ("flag.txt", data.00000bc8);
    stream = rax;
    if (stream == 0) {
        puts ("No flag found, please make sure this is run on the server");
    }
    rax = flag;
    rdx = stream;
    eax = fread (rax, 0x32, 1, stream);
    var_14h = eax;
    if (var_14h <= 0) {
        puts ("Invalid Flag");
        exit (0);
    }
    rax = stream;
    fclose (stream);
    eax = 0;
    encodeAll ();
    eax = 0;
    return rax;
}
```
The main difference lies in the **encodeALL** function.
```C
// Ghidra result
    var_28h = 0x635f31306d657449; // Hex for "Item01_c"
    var_20h = 0x706d622e70;       // Hex for "p.bmp"
    var_18h._0_4_ = 0;
    var_48h = 0x622e31306d657449; // Hex for "Item01.b"
    var_40h = 0x706d;             // Hex for "mp"
    var_38h._0_4_ = 0;
    for (var_9h._0_1_ = '5'; '0' < (char)var_9h; var_9h._0_1_ = (char)var_9h + -1) {
        encodeDataInFile((char *)&var_48h, (char *)&var_28h);
    }
```
```C
// jsdec result
    int64_t var_48h;
    int64_t var_43h;
    int64_t var_40h;
    int64_t var_38h;
    int64_t var_28h;
    int64_t var_23h;
    int64_t var_20h;
    int64_t var_18h;
    int64_t var_9h;
    rax = 0x635f31306d657449;    // Hex for "Item01_c"
    rdx = 0x706d622e70;          // Hex for "p.bmp"
    var_28h = rax;
    var_20h = rdx;
    var_18h = 0;
    rax = 0x622e31306d657449;    // Hex for "Item01.b"
    edx = 0x706d;                // Hex for "mp"
    var_48h = rax;
    var_40h = rdx;
    var_38h = 0;
    var_9h = 0x35;
    while (var_9h > 0x30) {
        eax = (int32_t) var_9h;
        var_43h = al;
        eax = (int32_t) var_9h;
        var_23h = al;
        rdx = &var_28h;
        rax = &var_48h;
        rsi = rdx;
        rdi = rax;
        encodeDataInFile ();
        eax = (int32_t) var_9h;
        eax--;
        var_9h = al;
    }
```
What the loop does is simply replace the ***01*** in **Item01_cp.bmp** and **Item01.bmp** and iterates over it from 1 to 5. Simplified, it looks like the following C code.
```C
for (char digit = '5'; digit > '0'; digit--) {
    sprintf(local_48, "Item0%c.bmp", digit);
    sprintf(local_28, "Item0%c_cp.bmp", digit);
    encodeDataInFile(local_48, local_28);
}
```
After that the program is pretty similar to the previous ones. It starts with a offset of **0x7e3** for each of the files, only this time it hides the flag in the LSB of 8 bytes followed by 4 unchanged bytes. It does this for all 5 images, hiding parts of the flag in each of the images.   
To get the flag we simply reverse the process and append the flag from each image to get the final flag.  
```python
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
```
```bash
thermos@valkyrie:~/CTFs$ python3 picoCTF/forensics/hard/Investigative\ Reversing\ 4/recover_flag.py 
Recovered flag: picoCTF{N1c3_R3ver51ng_5k1115_00000000000b93ee6e2}
```

Flag: **picoCTF{N1c3_R3ver51ng_5k1115_00000000000b93ee6e2}**