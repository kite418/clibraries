#include "kfile.h"

/*
    TODO
    ERROR CHECKING
*/

size_t file_size(char* file_path) {
    FILE* fp = fopen(file_path, "r");
    fseek(fp, 0L, SEEK_END);
    size_t sz = ftell(fp);
    fclose(fp);

    return sz;
}