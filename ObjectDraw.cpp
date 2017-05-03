#include "ObjectDraw.h"

void ObjectDraw(HDC &hMem, INT nTop, HPEN &hPen,  Rectangles *cWindow) {
	for (int i = 0; i <= nTop; i++)
		cWindow[i].draw(hMem, hPen);
}