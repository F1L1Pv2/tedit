#include <termios.h>
#include <unistd.h>
#include <stdbool.h>

#include "term.h"

bool in_raw_mode = false;

struct termios old_state;

void enable_raw_mode(int fd){
   if(!in_raw_mode){
       tcgetattr(fd,&old_state);
       struct termios new_state=old_state;
       new_state.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
       //new_state.c_oflag &= ~(OPOST);
       new_state.c_oflag |= OPOST;
       new_state.c_cflag |= (CS8);
       new_state.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
       new_state.c_cc[VMIN]= 0;
       new_state.c_cc[VTIME]= 1;
       tcsetattr(fd, TCSAFLUSH, &new_state);
       in_raw_mode = true;
   }
}

void disable_raw_mode(int fd){
   if(in_raw_mode){
      tcsetattr(fd, TCSAFLUSH, &old_state);
      in_raw_mode = false;
   }
}
