alias b := build
build:
    gcc *.c -o bird -lX11 -lraylib -lpthread -lm -ldl
