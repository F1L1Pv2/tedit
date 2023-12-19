#include <stdio.h>
#include <stdlib.h>

#include "file.h"

const char* empty_file = "";

const char * get_file_contents(const char* filename, size_t *out_file_size){
    FILE* file = fopen(filename, "r");
    if(file == NULL){
       *out_file_size = 0;
       return empty_file;
    }

    fseek(file, 0, SEEK_END);
    size_t file_len = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char*)calloc(file_len, sizeof(char));
    fread(buffer, sizeof(char), file_len, file);
    if(out_file_size != NULL) *out_file_size = file_len;
    return buffer;
}

void save_file_contents(const char* filename, const char* contents, size_t content_len){
    FILE* file = fopen(filename, "w");
    if(file == NULL){
        return;
    }

    fwrite(contents, sizeof(char), content_len, file);
}