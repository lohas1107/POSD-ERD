#include "GraphicsRelation.h"

GraphicsRelation::GraphicsRelation()
{
	doCreateItem();
}

GraphicsRelation::~GraphicsRelation()
{
}

void GraphicsRelation::doCreateItem()
{
	_item = new QGraphicsPolygonItem();
}

void GraphicsRelation::doAdjustSize(QFontMetrics fontMetrics)
{
	int width = fontMetrics.width(_text);
	int height = fontMetrics.height() + 20;

	QPolygonF _polygon;
	_polygon << QPointF(-width, 0) << QPointF(0, height) << QPointF(width, 0) << QPointF(0, -height) << QPointF(-width, 0);
	((QGraphicsPolygonItem*)_item)->setPolygon(_polygon);
}
