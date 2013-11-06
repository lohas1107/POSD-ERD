#include "GraphicsAttribute.h"
#include <QGraphicsEllipseItem>
#include "..\src\gui\styles\qstyle.h"

const int OFFSET = 30;

GraphicsAttribute::GraphicsAttribute()
{
	doCreateItem();
	_isPrimaryKey = false;	
}

GraphicsAttribute::~GraphicsAttribute()
{
}

// ���;���
void GraphicsAttribute::doCreateItem()
{
	_item = new QGraphicsPolygonItem();
}

// �]�w primary key
void GraphicsAttribute::setPrimaryKey(bool flag)
{
	_isPrimaryKey = flag;
}

// �ھڤ�r���e�վ�j�p
void GraphicsAttribute::doAdjustSize(QFontMetrics fontMetrics)
{
	int width = fontMetrics.width(_text) + OFFSET;
	int height = fontMetrics.height() + OFFSET;

	QPolygonF _polygon;
	_polygon << QPointF(-width/2, height/2) << QPointF(width/2, height/2) << QPointF(width/2, -height/2) << QPointF(-width/2, -height/2) << QPointF(-width/2, height/2);
	((QGraphicsPolygonItem*)_item)->setPolygon(_polygon);
}

// �e�ϩM�r
void GraphicsAttribute::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QFont font;
	if (_isPrimaryKey)
	{
		font.setUnderline(true);
	}
	painter->setFont(font);
	QFontMetrics fontMetrics(painter->font());
	doAdjustSize(fontMetrics);
	painter->drawText(_item->boundingRect(), Qt::AlignCenter, _text);
	painter->drawEllipse(_item->boundingRect());

	if (_isSelected)
	{
		painter->drawRect(_item->boundingRect());
	}
}
