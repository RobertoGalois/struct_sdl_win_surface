.PHONY: clean
.SUFFIXES:

prog: main.o simp_sdl.o
    gcc main.o simp_sdl.o -o prog `sdl-config --cflags --libs`
main.o: main.c simp_sdl.h
    gcc -c main.c
simp_sdl.o: simp_sdl.c simp_sdl.h
    gcc -c simp_sdl.c
clean:
    rm -f *.o prog
