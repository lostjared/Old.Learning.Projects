 to build

requires:
libmxf
SDL


LDFLAGS="-lmxf `sdl-config --libs`" CPPFLAGS="`sdl-config --cflags`" ./configure
make
