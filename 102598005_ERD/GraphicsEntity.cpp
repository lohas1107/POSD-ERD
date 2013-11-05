#include "GraphicsEntity.h"
#include <QPainter>

GraphicsEntity::GraphicsEntity()
{
	doCreateItem();
}

GraphicsEntity::~GraphicsEntity()
{
}

void GraphicsEntity::doCreateItem()
{
	//_item = new QGraphicsRectItem();
	_item = new QGraphicsPolygonItem();
}

void GraphicsEntity::doAdjustSize(QFontMetrics fontMetrics)
{
	int width = fontMetrics.width(_text) + 30;
	int height = fontMetrics.height() + 30;

	QPolygonF _polygon;
	_polygon << QPointF(-width/2, height/2) << QPointF(width/2, height/2) << QPointF(width/2, -height/2) << QPointF(-width/2, -height/2) << QPointF(-width/2, height/2);
	((QGraphicsPolygonItem*)_item)->setPolygon(_polygon);
}
