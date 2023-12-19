#include "common.h"
#include <string.h>
#include <ctype.h>
int main(int argc, char** argv){
    if(argc < 2 || argc > 2) die("You need to pass only filepath\n");
    struct winsize win;
    ioctl(0, TIOCGWINSZ, &win);
    size_t file_size = 0;
    const char* orig_buffer = get_file_contents(argv[1], &file_size);
    int c;
    enable_raw_mode(0);
    size_t cursor = file_size;
    size_t cur_x, cur_y = 0;
    char* buffer = (char*)calloc(1024*8, sizeof(char));
    memcpy(buffer, orig_buffer, file_size);
    size_t new_len = file_size;
    printf("%s", CUR_HIDE);
    while(1){
        clear();
        for(size_t i = 0; i<new_len;i++){
             if(i!=cursor) {printf("%c",*(buffer+i));}
             else{
                  if(*(buffer+i) == 10){
                       printf("\033[0;39;43m \033[0m\n");
                  }else{
                       printf("\033[0;39;43m%c\033[0m",*(buffer+i));
                  }
             }
        }
        if(cursor==new_len) printf("\033[0;39;43m \033[0m");        
        fflush(stdout);

        c = editorReadKey();
        if(c == CTRL_KEY(99)) break;
        if(c == CTRL_KEY(115)){
            save_file_contents(argv[1], buffer, new_len);
            break;
        }
        if(c == 127 && cursor > 0 && new_len > 0){
           memcpy(buffer+cursor-1, buffer+cursor, new_len-cursor);
           *(buffer+new_len) = 0;
           cursor--;
           new_len--;
        }
        if(c == DEL_KEY && new_len > 0){
           memcpy(buffer+cursor, buffer+cursor+1, new_len-cursor);
           *(buffer+new_len) = 0; new_len--;
        }
        if(c == ARROW_LEFT && cursor>0) {cursor--;}
        if(c == ARROW_RIGHT && cursor<new_len) {cursor++;}
        if(c == HOME_KEY) cursor = 0;
        if(c == END_KEY) cursor = new_len;
        if(c != 0 && !(iscntrl(c) && c != 10) && c<1000){
           memcpy(buffer+cursor+1,buffer+cursor, new_len-cursor);
           *(buffer+cursor) = (char)c;
           cursor++; new_len++;
        }
    }
    clear(); printf("%s", CUR_SHOW); disable_raw_mode(0);

}