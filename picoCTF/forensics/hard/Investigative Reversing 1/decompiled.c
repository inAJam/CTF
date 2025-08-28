
// WARNING: [rz-ghidra] Detected overlap for variable var_5ch
// WARNING: [rz-ghidra] Detected overlap for variable var_69h
// WARNING: [rz-ghidra] Detected overlap for variable var_68h
// WARNING: [rz-ghidra] Detected overlap for variable var_64h
// WARNING: [rz-ghidra] Detected overlap for variable var_60h

void main(void)
{
    int64_t iVar1;
    int64_t iVar2;
    int64_t iVar3;
    undefined8 uVar4;
    undefined8 uVar5;
    int64_t in_FS_OFFSET;
    char tmpChar;
    int c;
    int32_t var_64h;
    int32_t var_60h;
    FILE *flagVal;
    FILE *mystery;
    FILE *mystery2;
    FILE *mystery3;
    char flagBuf [26];
    int64_t canary;
    
    iVar1 = *(int64_t *)(in_FS_OFFSET + 0x28);
    iVar2 = fopen("flag.txt", data.0002008);
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
}
