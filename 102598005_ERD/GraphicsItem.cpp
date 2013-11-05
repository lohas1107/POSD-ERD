#include "GraphicsItem.h"
#include <QPainter>

GraphicsItem::GraphicsItem()
{
	_text = "";
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

GraphicsItem::~GraphicsItem()
{
}

QRectF GraphicsItem::boundingRect() const
{
	return _item->boundingRect();
}

QPainterPath GraphicsItem::shape() const
{
	return _item->shape();
}

void GraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QFontMetrics fontMetrics(painter->font());
	doAdjustSize(fontMetrics);
	painter->drawText(_item->boundingRect(), Qt::AlignCenter, _text);
	_item->paint(painter, option, widget);
}

void GraphicsItem::doAdjustSize(QFontMetrics fontMetrics)
{
	((QGraphicsRectItem*)_item)->setRect(_item->pos().rx(), _item->pos().ry(), fontMetrics.width(_text) + 30, fontMetrics.height() + 30);
	//int width = fontMetrics.width(_text) + 30;
	//int height = fontMetrics.height() + 30;

	//QPolygonF _polygon;
	//_polygon << QPointF(-width/2, height/2) << QPointF(width/2, height/2) << QPointF(width/2, -height/2) << QPointF(-width/2, -height/2) << QPointF(-width/2, height/2);
	//((QGraphicsPolygonItem*)_item)->setPolygon(_polygon);
}

void GraphicsItem::setText(string text)
{
	_text = QString::fromStdString(text);
}
