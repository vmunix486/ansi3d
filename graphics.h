#ifndef _GRAPHICS_H_
#define _GRAPHICS_H_

#define ushort unsigned short

typedef struct {
	ushort r,g,b;
} ansicolor;

void MkWnd(const char *title, int width,
		int height, int depth);
void StartDraw(void);
int  Draw(void);

void DrawPixel(int x, int y, ansicolor c);
ansicolor MkColor(ushort r, ushort g, ushort b);

#endif
