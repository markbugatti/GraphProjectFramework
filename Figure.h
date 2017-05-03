#pragma once
#include "stdafx.h"
class Figure
{
public:
	Figure();
	void setColor(COLORREF color);
	void setFrameWidth(int width);
	//virtual void draw(HDC & hdc, HPEN &hPen) = 0;
	virtual ~Figure();
protected:
	int nFrameWidth;
	COLORREF color;
};

