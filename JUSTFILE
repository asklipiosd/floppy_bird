alias b := build
build:
    gcc *.c *.h -o bird -lX11 -lraylib -lpthread -lm -ldl
