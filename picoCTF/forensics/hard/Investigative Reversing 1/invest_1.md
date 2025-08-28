# Investigative Reversing 1
Similar to the previous challenge we go through the binary and see that it requires a **flag.txt** file.
```bash
thermos@valkyrie:~/CTFs$ ./mystery
No flag found, please make sure this is run on the server
Segmentation fault (core dumped)
```
The `strings` command reveals that the binary needs all three of the **png** images.
```bash
thermos@valkyrie:~/CTFs$ strings mystery
/lib64/ld-linux-x86-64.so.2
libc.so.6
fopen
puts
__stack_chk_fail
fputc
fclose
fread
__cxa_finalize
__libc_start_main
GLIBC_2.4
GLIBC_2.2.5
_ITM_deregisterTMCloneTable
__gmon_start__
_ITM_registerTMCloneTable
u/UH
[]A\A]A^A_
flag.txt
mystery.png
mystery2.png
mystery3.png
No flag found, please make sure this is run on the server
mystery.png is missing, please run this on the server
;*3$"
GCC: (Ubuntu 8.2.0-7ubuntu1) 8.2.0
```
Puuting the binary in cutter and renaming the required variables we get the following decompiled code.
```C
    iVar1 = *(int64_t *)(in_FS_OFFSET + 0x28);
    iVar2 = fopen("flag.txt", data.00002008);
    iVar3 = fopen("mystery.png", data.00002013);
    uVar4 = fopen("mystery2.png", data.00002013);
    uVar5 = fopen("mystery3.png", data.00002013);
    if (iVar2 == 0) {
        puts("No flag found, please make sure this is run on the server");
    }
    if (iVar3 == 0) {
        puts("mystery.png is missing, please run this on the server");
    }
    fread(flagBuf, 0x1a, 1, iVar2);
    fputc((int32_t)flagBuf[1], uVar5);
    fputc((int32_t)(char)(flagBuf[0] + '\x15'), uVar4);
    fputc((int32_t)flagBuf[2], uVar5);
    tmpChar = flagBuf[3];
    fputc((int32_t)flagBuf[5], uVar5);
    fputc((int32_t)flagBuf[4], iVar3);
    for (stack0xffffffffffffff98 = 6; stack0xffffffffffffff98 < 10; unique0x00005780 = stack0xffffffffffffff98 + 1) {
        tmpChar = tmpChar + '\x01';
        fputc((int32_t)flagBuf[stack0xffffffffffffff98], iVar3);
    }
    fputc((int32_t)tmpChar, uVar4);
    for (var_64h = 10; var_64h < 0xf; var_64h = var_64h + 1) {
        fputc((int32_t)flagBuf[var_64h], uVar5);
    }
    for (var_60h = 0xf; var_60h < 0x1a; var_60h = var_60h + 1) {
        fputc((int32_t)flagBuf[var_60h], iVar3);
    }
    fclose(iVar3);
    fclose(iVar2);
    if (iVar1 != *(int64_t *)(in_FS_OFFSET + 0x28)) {
        __stack_chk_fail();
    }
    return;
```
Using `zsteg` on the images reveal the strings attached at the end of the images.
```bash
thermos@valkyrie:~/CTFs$ zsteg mystery.png 
[?] 16 bytes of extra data after image end (IEND), offset = 0x1e873
extradata:0         .. text: "CF{An1_9a47141}`"
imagedata           .. text: "PPP@@@@@@@@@@@@"
thermos@valkyrie:~/CTFs$ zsteg mystery2.png 
[?] 2 bytes of extra data after image end (IEND), offset = 0x1e873
extradata:0         .. 

    00000000: 85 73                                             |.s              |
imagedata           .. text: "PPP@@@@@@@@@@@@"
thermos@valkyrie:~/CTFs$ zsteg mystery3.png 
[?] 8 bytes of extra data after image end (IEND), offset = 0x1e873
extradata:0         .. text: "icT0tha_"
imagedata           .. text: "PPP@@@@@@@@@@@@"
thermos@valkyrie:~/CTFs$ 
```
Now all we need to do is iterate over the code and reverse engineer the flag itself. 
| mystery1(ivar3) | myster2(uvar4) | myster3(uvar5) | tmpChar | Flag(26) |comments|
|---|---|---|---|---|---|
||`0x85`|ic|o|pico______________________|till temp variable is set up|
|C|`0x85`|icT|o|picoCT____________________|before the loop|
|CF|`0x85`|icT|p|picoCTF___________________|loop iteration for 6|
|CF{|`0x85`|icT|q|picoCTF{__________________|loop iteration for 7|
|CF{A|`0x85`|icT|r|picoCTF{A__________________|loop iteration for 8|
|CF{An|`0x85`|icT|s|picoCTF{An________________|loop iteration for 9|
|CF{An|`0x85 0x73`|icT|s|picoCTF{An________________|tmpChar added to mystery2|
|CF{An|`0x85 0x73`|icT|s|picoCTF{An________________|new loop starts with 10|
|CF{An|`0x85 0x73`|icT0|s|picoCTF{An0_______________|loop value 10|
|CF{An|`0x85 0x73`|icT0t|s|picoCTF{An0t______________|loop value 11|
|CF{An|`0x85 0x73`|icT0th|s|picoCTF{An0th_____________|loop value 12|
|CF{An|`0x85 0x73`|icT0tha|s|picoCTF{An0tha____________|loop value 13|
|CF{An|`0x85 0x73`|icT0tha_|s|picoCTF{An0tha____________|loop value 14|
|CF{An|`0x85 0x73`|icT0tha_|s|picoCTF{An0tha____________|new loop for variables 15 till the rest|
|CF{An1|`0x85 0x73`|icT0tha_|s|picoCTF{An0tha_1__________|loop value 15|
|CF{An1_|`0x85 0x73`|icT0tha_|s|picoCTF{An0tha_1__________|loop value 16|
|CF{An1_9|`0x85 0x73`|icT0tha_|s|picoCTF{An0tha_1_9________|loop value 17|
|CF{An1_9a|`0x85 0x73`|icT0tha_|s|picoCTF{An0tha_1_9a_______|loop value 18|
|CF{An1_9a47141}`|`0x85 0x73`|icT0tha_|s|picoCTF{An0tha_1_9a47141}`|loop value 25|

Flag: **picoCTF{An0tha_1_9a47141}**