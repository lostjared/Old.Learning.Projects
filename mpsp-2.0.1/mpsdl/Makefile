
TARGET = mpsp
OBJS = mxfont.o pixelbuffer.o main.o

CFLAGS = -O2 -G0 -Wall
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

PSPBIN = $(PSPSDK)/../bin
CFLAGS += `$(PSPBIN)/sdl-config --cflags`
LIBS += `$(PSPBIN)/sdl-config --libs` -lSDL_image


EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = MasterPiecePSP
PSP_EBOOT_ICON = mpsp.png
# PSP_EBOOT_PIC1 = test.png

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
	


pc:
	echo "#define _PC_MODE_H_ 0" > compile_mode.h
	g++ mxfont.c -c `sdl-config --cflags`
	g++ pixelbuffer.c -c `sdl-config --cflags`
	g++ main.cpp -c `sdl-config --cflags`
	g++ main.o mxfont.o pixelbuffer.o -o masterpiece `sdl-config --libs`
pcc:
	echo "" > compile_mode.h
	rm -f *.o masterpiece

