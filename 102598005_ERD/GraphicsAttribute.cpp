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
	//_item = new QGraphicsEllipseItem();
	_item = new QGraphicsPolygonItem();
}

void GraphicsAttribute::doAdjustSize(QFontMetrics fontMetrics)
{
	int width = fontMetrics.width(_text) + 30;
	int height = fontMetrics.height() + 30;

	QPolygonF _polygon;
	_polygon << QPointF(-width/2, height/2) << QPointF(width/2, height/2) << QPointF(width/2, -height/2) << QPointF(-width/2, -height/2) << QPointF(-width/2, height/2);
	((QGraphicsPolygonItem*)_item)->setPolygon(_polygon);
}

void GraphicsAttribute::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QFontMetrics fontMetrics(painter->font());
	doAdjustSize(fontMetrics);
	painter->drawText(_item->boundingRect(), Qt::AlignCenter, _text);
	painter->drawEllipse(_item->boundingRect());
	//_item->paint(painter, option, widget);
}