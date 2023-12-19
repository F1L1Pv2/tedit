enum editorKey {
  ARROW_LEFT = 1000,
  ARROW_RIGHT,
  ARROW_UP,
  ARROW_DOWN,
  DEL_KEY,
  HOME_KEY,
  END_KEY,
  PAGE_UP,
  PAGE_DOWN
};

int editorReadKey() {
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
      if (seq[1] >= 48 && seq[1] <= 57) {
        if (read(STDIN_FILENO, &seq[2], 1) != 1) return 27;
        if (seq[2] == 126) {
          switch (seq[1]) {
            case 49: return HOME_KEY;
            case 51: return DEL_KEY;
            case 52: return END_KEY;
            case 53: return PAGE_UP;
            case 54: return PAGE_DOWN;
            case 55: return HOME_KEY;
            case 56: return END_KEY;
          }
        }
      } else {
        switch (seq[1]) {
          case 65: return ARROW_UP;
          case 66: return ARROW_DOWN;
          case 67: return ARROW_RIGHT;
          case 68: return ARROW_LEFT;
          case 72: return HOME_KEY;
          case 70: return END_KEY;
        }
      }
    } else if (seq[0] == 79) {
      switch (seq[1]) {
        case 72: return HOME_KEY;
        case 70: return END_KEY;
      }
    }
    return 27;
  } else {
    return c;
  }
}