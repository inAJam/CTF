
// WARNING: [rz-ghidra] Detected overlap for variable flag_len
// WARNING: [rz-ghidra] Detected overlap for variable temp
// WARNING: [rz-ghidra] Detected overlap for variable var_24h
// WARNING: [rz-ghidra] Detected overlap for variable var_9h

undefined8 main(int argc, char **argv)
{
    undefined8 uVar1;
    int64_t in_FS_OFFSET;
    char **var_98h;
    int var_8ch;
    char charBuf;
    char cStack_7d;
    int32_t iStack_7c;
    int32_t iStack_78;
    int i;
    int j;
    int counter;
    int limit;
    int32_t flag_len;
    FILE *flag;
    FILE *original_bmp;
    FILE *encoded_bmp;
    void *flagBuf;
    int64_t canary;
    
    canary = *(int64_t *)(in_FS_OFFSET + 0x28);
    counter = 0;
    flag = (FILE *)fopen("flag.txt", r);
    original_bmp = (FILE *)fopen("original.bmp", r);
    encoded_bmp = (FILE *)fopen("encoded.bmp", a);
    if (flag == (FILE *)0x0) {
        puts("No flag found, please make sure this is run on the server");
    }
    if (original_bmp == (FILE *)0x0) {
        puts("original.bmp is missing, please run this on the server");
    }
    iStack_7c = fread(&charBuf, 1, 1, original_bmp);
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
    fclose(encoded_bmp);
    fclose(original_bmp);
    fclose(flag);
    uVar1 = 0;
    if (canary != *(int64_t *)(in_FS_OFFSET + 0x28)) {
        uVar1 = __stack_chk_fail();
    }
    return uVar1;
}
