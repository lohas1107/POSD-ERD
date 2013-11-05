#include "GraphicsAttribute.h"
#include <QGraphicsEllipseItem>

GraphicsAttribute::GraphicsAttribute()
{
	doCreateItem();
}

GraphicsAttribute::~GraphicsAttribute()
{
}

void GraphicsAttribute::doCreateItem()
{
	_item = new QGraphicsEllipseItem();
}
