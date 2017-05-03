#pragma once

#include "stdafx.h"
#include "Figure.h"
class Rectangles
	: public Figure
{
private:
	RECT pos;
	int length, height;
	//int nFrameWidth;
	//COLORREF color;
public:	
	Rectangles();
	//void setColor(COLORREF color);
	//void setFrameWidth(int width);
	void draw(HDC & hdc, HPEN &hPen);
	void setX(int x);
	void setY(int y);
	void setSx(int length);
	void setSy(int height);
	int getX();
	int getY();
	RECT getPos();
	~Rectangles();
};

