#include <stdio.h>

typedef unsigned short ushort;

typedef struct {
	ushort r,g,b;
} ansicolor;


 /****************************\
 * Stuff for SDL 1.2 graphics *
 *                            *
 \****************************/

#ifdef _SDL
#include <SDL/SDL.h>

SDL_Surface *screen;

void MkWnd(const char *title, int width,
		int height, int depth) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		fprintf(stderr,
			"Couldn't initialize SDL: %s\n",
			SDL_GetError());
		exit(1);
	}

	screen = SDL_SetVideoMode(width, height, 
			    depth, SDL_SWSURFACE);

	if (screen == NULL) {
		fprintf(stderr,
			"Couldn't set a %dx%d %d-bit color video mode: %s\n",
			width, height, depth,
			SDL_GetError());
		exit(1);
	}

	SDL_WM_SetCaption(title, title);
}

/* Rewritten from 
 * libsdl.org/release/SDL-1.2.15/docs/html/guidevideo.html#AEN90
*/
void DrawPixel(int x, int y, ansicolor c) {
	Uint32 color=SDL_MapRGB(screen->format,c.r,c.g,c.b);
	Uint8 *p = (Uint8 *)screen->pixels + y *
		    screen->pitch + x * screen->format->BytesPerPixel;
	/* No clue why this works but it does. ;_; */

	switch(screen->format->BytesPerPixel) {
		case 1:
			*p = color;
			break;
		case 2:
			*(Uint16 *)p = color;
			break;
		case 3:
			if(SDL_BYTEORDER==SDL_BIG_ENDIAN){
				p[0]=(color>>16) & 0xff;
				p[1]=(color>>8)  & 0xff;
				p[2]=color       & 0xff;
			} else {
				p[0]=color       & 0xff;
				p[1]=(color>>8)  & 0xff;
				p[2]=(color>>16) & 0xff;
			} break;
		case 4:
			*(Uint32 *)p = color;
			break;
	}
}

ansicolor MkColor(ushort r, ushort g, ushort b) {
	ansicolor ret;

	if (r > 255 || g > 255 || b > 255)
		fprintf(stderr,
			"Make sure your RGB values don't go over 255!");

	ret.r=r;
	ret.g=g;
	ret.b=b;
	return ret; 
}

void StartDraw(void) {
	SDL_LockSurface(screen);
}

int Draw(void) {
	SDL_LockSurface(screen);
	return SDL_Flip(screen);
}

#endif
