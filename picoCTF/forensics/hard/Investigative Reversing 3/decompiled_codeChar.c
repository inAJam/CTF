
// WARNING: Variable defined which should be unmapped: c
// WARNING: [rz-ghidra] Detected overlap for variable a
// WARNING: [rz-ghidra] Detected overlap for variable var_24h
// WARNING: [rz-ghidra] Detected overlap for variable var_9h

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
