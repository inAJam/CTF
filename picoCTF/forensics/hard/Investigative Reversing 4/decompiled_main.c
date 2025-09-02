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
