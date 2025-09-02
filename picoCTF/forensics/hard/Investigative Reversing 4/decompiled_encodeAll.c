// Ghidra decompiled code
void encodeAll(void)
{
    int64_t var_48h;
    int64_t var_40h;
    int64_t var_38h;
    int64_t var_28h;
    int64_t var_20h;
    int64_t var_18h;
    int64_t var_9h;
    
    var_28h = 0x635f31306d657449; // Hex for "Item01_c"
    var_20h = 0x706d622e70;       // Hex for "p.bmp"
    var_18h._0_4_ = 0;
    var_48h = 0x622e31306d657449; // Hex for "Item01.b"
    var_40h = 0x706d;             // Hex for "mp"
    var_38h._0_4_ = 0;
    for (var_9h._0_1_ = '5'; '0' < (char)var_9h; var_9h._0_1_ = (char)var_9h + -1) {
        encodeDataInFile((char *)&var_48h, (char *)&var_28h);
    }
    return;
}

// jsdec decompiled code
int64_t encodeAll (void) {
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
    return rax;
}
