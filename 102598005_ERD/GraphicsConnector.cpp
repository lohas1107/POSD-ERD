#include "GraphicsConnector.h"

GraphicsConnector::GraphicsConnector()
{
	doCreateItem();
}

GraphicsConnector::~GraphicsConnector()
{
}

void GraphicsConnector::doCreateItem()
{
	_item = new QGraphicsLineItem();
}

void GraphicsConnector::doAdjustSize(QFontMetrics fontMetrics)
{
	((QGraphicsLineItem*)_item)->setLine(0, 0, fontMetrics.width(_text) + 30, fontMetrics.height() + 30);
}
