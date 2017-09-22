all:
	gcc -c mxfont.c pixelbuffer.c `sdl-config --cflags`
	ar cru libmxf.a mxfont.o pixelbuffer.o
	ranlib libmxf.a	
	gcc mxf2c.c -o mxf2c `sdl-config --cflags --libs`
install: all
	cp mxfont.h /usr/local/include/SDL/SDL_mxf.h
	cp libmxf.a /usr/local/lib/libmxf.a
clean:
	rm -f *.o