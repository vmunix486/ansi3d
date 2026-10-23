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

CFLAGS += -Wall -Wextra -pedantic -ansi -Ofast

ifeq ($(DISPLAY), sdl)
	LDFLAGS += $(shell sdl-config --libs)
endif

LDFLAGS += -flto

all: archive

graphics:	
	$(CC) $(CFLAGS) -c graphics.c

3d:
	$(CC) $(CFLAGS) -c 3d.c

archive: graphics 3d
	$(AR) rcs libansi3d.a 3d.o graphics.o

example: archive
	$(CC) $(CFLAGS) example.c -o example -L. -lansi3d $(LDFLAGS)

clean:
	rm -fv *.o *.a *.exe
