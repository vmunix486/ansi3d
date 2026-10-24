######################################################
# This is probably the only part you need to modify: #
######################################################
DISPLAY=sdl
PLATFORM=mingw32

############################################
# You probably don't need to go past here. #
############################################

ifeq ($(PLATFORM), mingw32)
	CC=i686-w64-mingw32-gcc
else ifeq ($(PLATFORM), posix)
	CC=gcc
endif

LD=$(CC)
AR=ar

ifeq ($(DISPLAY), sdl)
	CFLAGS += $(shell sdl-config --cflags) -D_SDL
endif

CFLAGS += -Iinclude -Wall -Wextra -pedantic -ansi -Ofast

ifeq ($(DISPLAY), sdl)
	LDFLAGS += $(shell sdl-config --libs)
endif

LDFLAGS += -flto

all: archive

graphics:	
	$(CC) $(CFLAGS) -c src/graphics.c -o build/graphics.o

3d:
	$(CC) $(CFLAGS) -c src/3d.c -o build/3d.o

archive: graphics 3d
	$(AR) rcs build/libansi3d.a build/3d.o build/graphics.o

example: archive
	$(CC) $(CFLAGS) examples/basic.c -o build/basic -Lbuild -lansi3d $(LDFLAGS)

clean:
	rm -fv build/*.o build/*.a build/*.exe
