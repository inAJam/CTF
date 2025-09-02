void encodeDataInFile(char *original, char *modified)
{
    char *var_48h;
    char *filename;
    void *ptr;
    FILE *stream;
    uint32_t var_18h;
    int32_t var_14h;
    int32_t var_10h;
    char var_ch;
    
    stream = (FILE *)fopen(original, 0xbc8);
    *(undefined8 *)0x0 = fopen(modified, 0xbca);
    if (stream != (FILE *)0x0) {
        _var_ch = fread(&ptr, 1, 1, stream);
        ptr._2_4_ = 0x7e3;
        for (var_10h = 0; var_10h < ptr._2_4_; var_10h = var_10h + 1) {
            fputc((int32_t)(char)ptr, stack0xffffffffffffffd8);
            _var_ch = fread(&ptr, 1, 1, stream);
        }
        for (var_14h = 0; var_14h < 0x32; var_14h = var_14h + 1) {
            if (var_14h % 5 == 0) {
                for (var_18h = 0; (int32_t)var_18h < 8; var_18h = var_18h + 1) {
                    ptr._1_1_ = codedChar((uint64_t)var_18h, 
                                          (uint64_t)(uint32_t)(int32_t)*(char *)(*_flag_index + _flag), 
                                          (uint64_t)(uint32_t)(int32_t)(char)ptr);
                    fputc((int32_t)ptr._1_1_, stack0xffffffffffffffd8);
                    fread(&ptr, 1, 1, stream);
                }
                *_flag_index = *_flag_index + 1;
            } else {
                fputc((int32_t)(char)ptr, stack0xffffffffffffffd8);
                fread(&ptr, 1, 1, stream);
            }
        }
        while (_var_ch == 1) {
            fputc((int32_t)(char)ptr, stack0xffffffffffffffd8);
            _var_ch = fread(&ptr, 1, 1, stream);
        }
        fclose(stack0xffffffffffffffd8);
        fclose(stream);
        return;
    }
    puts(0xbd0);
    // WARNING: Subroutine does not return
    exit(0);
}
