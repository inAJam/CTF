
// WARNING: [rz-ghidra] Detected overlap for variable falg_len_check
// WARNING: [rz-ghidra] Detected overlap for variable j
// WARNING: [rz-ghidra] Detected overlap for variable a
// WARNING: [rz-ghidra] Detected overlap for variable var_24h
// WARNING: [rz-ghidra] Detected overlap for variable var_9h

undefined8 main(int argc, char **argv)
{
    undefined8 uVar1;
    int64_t in_FS_OFFSET;
    char **var_98h;
    int var_8ch;
    char origCharBuf;
    char cStack_7d;
    int32_t iStack_7c;
    int32_t iStack_78;
    int i;
    uint32_t j;
    int var_6ch;
    int loop_limit;
    int32_t falg_len_check;
    FILE *flag;
    FILE *original;
    FILE *encoded;
    void *flagBuf;
    int64_t canary;
    
    canary = *(int64_t *)(in_FS_OFFSET + 0x28);
    var_6ch = 0;
    flag = (FILE *)fopen("flag.txt", r);
    original = (FILE *)fopen("original.bmp", r);
    encoded = (FILE *)fopen("encoded.bmp", data.00002020);
    if (flag == (FILE *)0x0) {
        puts("No flag found, please make sure this is run on the server");
    }
    if (original == (FILE *)0x0) {
        puts("No output found, please run this on the server");
    }
    iStack_7c = fread(&origCharBuf, 1, 1, original);
    // 723 bytes copied from original to encoded
    loop_limit = 0x2d3;
    for (iStack_78 = 0; iStack_78 < loop_limit; iStack_78 = iStack_78 + 1) {
        fputc((int32_t)origCharBuf, encoded);
        iStack_7c = fread(&origCharBuf, 1, 1, original);
    }
    falg_len_check = fread(&flagBuf, 0x32, 1, flag);
    if (falg_len_check < 1) {
        puts("Invalid Flag");
        exit(0);
    }
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
    while (iStack_7c == 1) {
        fputc((int32_t)origCharBuf, encoded);
        iStack_7c = fread(&origCharBuf, 1, 1, original);
    }
    fclose(encoded);
    fclose(original);
    fclose(flag);
    uVar1 = 0;
    if (canary != *(int64_t *)(in_FS_OFFSET + 0x28)) {
        uVar1 = __stack_chk_fail();
    }
    return uVar1;
}
