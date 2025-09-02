
// WARNING: Variable defined which should be unmapped: var_ah
// WARNING: [rz-ghidra] Detected overlap for variable temp
// WARNING: [rz-ghidra] Detected overlap for variable var_24h
// WARNING: [rz-ghidra] Detected overlap for variable var_9h

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
