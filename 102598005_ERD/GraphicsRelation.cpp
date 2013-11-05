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
	int width = fontMetrics.width(_text) + 5;
	int height = width * 0.8;

	QPolygonF _polygon;
	_polygon << QPointF(-width, 0) << QPointF(0, height) << QPointF(width, 0) << QPointF(0, -height) << QPointF(-width, 0);
	((QGraphicsPolygonItem*)_item)->setPolygon(_polygon);
}
