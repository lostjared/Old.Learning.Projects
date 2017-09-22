all:
	gcc main.c -o example -lmxf `sdl-config --cflags --libs` -I/usr/local/include -L/usr/local/lib
	gcc sdl-mxf.c -o sdl-mxf -lmxf `sdl-config --cflags --libs` -I/usr/local/include -L/usr/local/lib
clean:
	rm -f *.o
