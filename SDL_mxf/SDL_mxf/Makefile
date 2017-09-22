all:
	gcc pixelbuffer.c -c `sdl-config --cflags`
	gcc mxfont.c -c `sdl-config --cflags`
	gcc main.c -c `sdl-config --cflags`
	gcc pixelbuffer.o mxfont.o main.o -o sdl-mxf `sdl-config --libs`

clean:
	rm -f *.o
