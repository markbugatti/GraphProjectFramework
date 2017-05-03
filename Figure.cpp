#include "Figure.h"

Figure::Figure()
{
}

void Figure::setColor(COLORREF color)
{
	this->color = color;
}

void Figure::setFrameWidth(int width)
{
	this->nFrameWidth = width;
}

Figure::~Figure()
{
}
