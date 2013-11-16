#include "ERPoint.h"

ERPoint::ERPoint()
{
	_x = 0;
	_y = 0;
}

ERPoint::ERPoint(float x, float y)
{
	setPoint(x, y);
}

ERPoint::~ERPoint()
{
}

void ERPoint::setPoint(float x, float y)
{
	_x = x;
	_y = y;
}

float ERPoint::getX()
{
	return _x;
}

float ERPoint::getY()
{
	return _y;
}
