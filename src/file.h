#ifndef FILE_HEADER
#define FILE_HEADER
const char * get_file_contents(const char* filename, size_t *out_file_size);
void save_file_contents(const char* filename, const char* contents, size_t content_len);
#endif
