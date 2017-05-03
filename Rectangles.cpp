#include "Rectangles.h"

Rectangles::Rectangles()
{
}

//void Rectangles::setColor(COLORREF color)
//{
//	this->color = color;
//}
//
//void Rectangles::setFrameWidth(int width)
//{
//	this->nFrameWidth = width;
//}

void Rectangles::draw(HDC &hdc, HPEN &hPen)
{
	if (hPen) DeleteObject(hPen);
	hPen = CreatePen(PS_SOLID, nFrameWidth, color);
	SelectObject(hdc, hPen);
	Rectangle(hdc, pos.left, pos.top,  pos.right = pos.left + length, pos.bottom = pos.top + height);
}


void Rectangles::setX(int x)
{
	this->pos.left = x;
}

void Rectangles::setY(int y)
{
	this->pos.top = y;
}

void Rectangles::setSx(int lenght)
{
	this->length = lenght;
}

void Rectangles::setSy(int height)
{
	this->height = height;
}

int Rectangles::getX()
{
	return pos.left;
}

int Rectangles::getY()
{
	return pos.top;
}

RECT Rectangles::getPos()
{
	return this->pos;
}


Rectangles::~Rectangles()
{
}
