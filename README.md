This is a editor written in C without using any editors

### HOW!?
 
you may be wondering how on earth could anyone write code without text edior?
Its preety simple actually (as long as you have bash shell)

you can use this syntax in terminal to effectivly write code
```bash
echo -n '#include <stdio.h>

int main(){
    printf("example code\n");
}
'>filename.c
```

you can add new lines by pressing `Ctrl+v Ctrl+j`
i also used xclip for copying contents of file contents and tmux.
i did this challange on Ubuntu in which i unsintalled every text editor i could think of
Vim Nano Ed etc...

#### limitations of echo:
- you cannot use `'` inside command i tried many things including `\'` or `'"'"'` but this did not work
- because of previous limitation i couldn't use character literals 'a' so i had to write every ascii value manually
- if file content is bigger than your terminal size commands start to work weirdly and cursor doesnt work properly (you can fix this by making characters smaller or splitting code into many files)

### last note
i just think it was a fun challange and i encourage anyone to do it themselves now i can expand tedit with tedit. I hope you will have a great day.