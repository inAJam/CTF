# Investigative Reversing 0
We download the binary and try to run it to see if we can find anything.
```bash
thermos@valkyrie:~/CTFs$ ./mystery
No flag found, please make sure this is run on the server
Segmentation fault (core dumped)
```
If we examine the **png** image we find what looks like the flag.
```bash
thermos@valkyrie:~/CTFs$ exiftool mystery.png 
ExifTool Version Number         : 12.40
File Name                       : mystery.png
Directory                       : .
File Size                       : 122 KiB
File Modification Date/Time     : 2020:10:27 00:10:04+05:30
File Access Date/Time           : 2025:08:27 15:38:33+05:30
File Inode Change Date/Time     : 2025:08:27 15:38:06+05:30
File Permissions                : -rw-r--r--
File Type                       : PNG
File Type Extension             : png
MIME Type                       : image/png
Image Width                     : 1411
Image Height                    : 648
Bit Depth                       : 8
Color Type                      : RGB
Compression                     : Deflate/Inflate
Filter                          : Adaptive
Interlace                       : Noninterlaced
SRGB Rendering                  : Perceptual
Gamma                           : 2.2
Pixels Per Unit X               : 5669
Pixels Per Unit Y               : 5669
Pixel Units                     : meters
Warning                         : [minor] Trailer data after PNG IEND chunk
Image Size                      : 1411x648
Megapixels                      : 0.914
```
```bash
thermos@valkyrie:~/CTFs$ zsteg mystery.png 
[?] 26 bytes of extra data after image end (IEND), offset = 0x1e873
extradata:0         .. 
    00000000: 70 69 63 6f 43 54 4b 80  6b 35 7a 73 69 64 36 71  |picoCTK.k5zsid6q|
    00000010: 5f 33 64 36 35 39 66 35  37 7d                    |_3d659f57}      |
imagedata           .. text: "PPP@@@@@@@@@@@@"
```
If we further look into the ***mystery*** binary, we find some strings stating to run this program on the server.
```bash
thermos@valkyrie:~/CTFs$ strings mystery
/lib64/ld-linux-x86-64.so.2
libc.so.6
exit
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
No flag found, please make sure this is run on the server
mystery.png is missing, please run this on the server
at insert
```
From all of this it seems like the flag was encrypted and appended to the end of the png via the ***mystery*** program.
**Note:** This binary can be fed to **ghidra** to find the code itself, but I used **gdb-peda** to solve it. The below steps used **gdb**, they can be skipped and directly replaced via the use of **ghidra**  
The starting parts of the binary just checks for the presence of the **flag.txt** file. Once it finds that it opens the file in **read** mode and the ***mystery.png*** in **append** mode. 

Now there are a few locations and regiters to keep note of:
- `rbp-0x38` -> this stores the location of the file pointer of the ***mystery.png***
- `eax` -> this mainly stores the 
  - current letter of the original flag
  - and later the encrypted letter
  - sometimes it stores the number of letters processed

Next there are a few commands which are repeated as is throughout the code.
```bash
   0x000000000000123c <+167>:	movzx  eax,BYTE PTR [rbp-0x30]
   0x0000000000001240 <+171>:	mov    BYTE PTR [rbp-0x4d],al
   0x0000000000001243 <+174>:	movsx  eax,BYTE PTR [rbp-0x4d]
   0x0000000000001247 <+178>:	mov    rdx,QWORD PTR [rbp-0x38]
   0x000000000000124b <+182>:	mov    rsi,rdx
   0x000000000000124e <+185>:	mov    edi,eax
   0x0000000000001250 <+187>:	call   0x1070 <fputc@plt>
```
The first line changes slightly, but all this part of the code does is that it takes one letter from the ***flag.txt***, encrypts it and appends it to the end of the **png**. This part add the letter as is.
```bash
   0x00000000000012e0 <+331>:	movzx  eax,BYTE PTR [rbp+rax*1-0x30]
   0x00000000000012e5 <+336>:	mov    BYTE PTR [rbp-0x4d],al
   0x00000000000012e8 <+339>:	movzx  eax,BYTE PTR [rbp-0x4d]
   0x00000000000012ec <+343>:	add    eax,0x5
   0x00000000000012ef <+346>:	mov    BYTE PTR [rbp-0x4d],al
   0x00000000000012f2 <+349>:	movsx  eax,BYTE PTR [rbp-0x4d]
   0x00000000000012f6 <+353>:	mov    rdx,QWORD PTR [rbp-0x38]
   0x00000000000012fa <+357>:	mov    rsi,rdx
   0x00000000000012fd <+360>:	mov    edi,eax
   0x00000000000012ff <+362>:	call   0x1070 <fputc@plt>
```
This part adds **5** to the letter and then appends it, the start of the code basically treats it as an array, iterating over the letters.
Once we follow this pattern through a run via gdb we realise that there are stages in which the letters are encrypted and appended.
* The first six letters are appended as is
* The 7th-15th letters are first ceaser shifted by 5 and then appended.
  * `zsteg` shows the letters as **.** if it's not in the printable range, but the ascii shows the proper value
  * `{ -> .` is actually `0x7b -> 0x80` 
* The 16th letter ir reverse shifted by 3
* The remaining are added as is
So now we just need to reverse the shift to get the decrypted flag.  
`picoCTK.k5zsid6q_3d659f57}` -> `picoCT` + `K.k5zsid6` + `q` + `_3d659f57}` -> `picoCT` + `F{f0und_1` + `t` + `_3d659f57}`

Flag: **picoCTF{f0und_1t_3d659f57}**