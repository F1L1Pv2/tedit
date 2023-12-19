set -xe
#/bin/sh
clang -o build/tedit src/main.c src/file.c src/term.c -I src -L src
