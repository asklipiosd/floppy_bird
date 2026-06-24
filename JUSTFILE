alias b := build
alias r := run
build:
    gcc *.c *.h -o bird -lX11 -lraylib -lpthread -lm -ldl
run:
    gcc *.c *.h -o bird -lX11 -lraylib -lpthread -lm -ldl
    ./bird
