#include <stdio.h>
#include <sys/ioctl.h>
#include <errno.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "file.h"
#include "term.h"

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))
#define CTRL_KEY(k) ((k) & 0x1f)
#define cursorforward(x) printf("\033[%dC", (x))
#define cursorbackward(x) printf("\033[%dD", (x))
#define CUR_HIDE "\x1b[?25l"
#define CUR_SHOW "\x1b[?25h"

void die(const char* why){
    perror(why);
    disable_raw_mode(0);
    exit(1);
}

#include "keyboard.h"

void convert_cur_pos(size_t cur, struct winsize* win, size_t *row, size_t* col){
   *row = cur / win->ws_col;
   *col = cur % win->ws_col;
}

char editorReadKey_old() {
  int nread;
  char c;
  while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
    if (nread == -1 && errno != EAGAIN) die("read");
  }
  if (c == 13) return 10;
  if (c == 27) {
    char seq[3];
    if (read(STDIN_FILENO, &seq[0], 1) != 1) return 27;
    if (read(STDIN_FILENO, &seq[1], 1) != 1) return 27;
    if (seq[0] == 91) {
      switch (seq[1]) {
        case  65: return CTRL_KEY(119);
        case  66: return CTRL_KEY(115);
        case  67: return CTRL_KEY(100);
        case  68: return CTRL_KEY(97);
      }
    }
    return 27;
  } else {
    return c;
  }
}
