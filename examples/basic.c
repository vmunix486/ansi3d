#include "graphics.h"
#include <unistd.h>

int main(void) {
	MkWnd("Test", 640, 480, 8);

	StartDraw();
		DrawPixel(100, 100, MkColor(255,255,255));
	Draw();

	sleep(10);

	return 0;
}
