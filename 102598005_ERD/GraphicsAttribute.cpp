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

// 產生橢圓形
void GraphicsAttribute::doCreateItem()
{
	_item = new QGraphicsPolygonItem();
}

// 設定 primary key
void GraphicsAttribute::setPrimaryKey(bool flag)
{
	_isPrimaryKey = flag;
}

// 根據文字內容調整大小
void GraphicsAttribute::doAdjustSize(QFontMetrics fontMetrics)
{
	int width = fontMetrics.width(_text) + OFFSET;
	int height = fontMetrics.height() + OFFSET;

	QPolygonF _polygon;
	_polygon << QPointF(-width/2, height/2) << QPointF(width/2, height/2) << QPointF(width/2, -height/2) << QPointF(-width/2, -height/2) << QPointF(-width/2, height/2);
	((QGraphicsPolygonItem*)_item)->setPolygon(_polygon);
}

// 畫圖和字
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
	if (_isSelected)
	{
		painter->setPen(Qt::green);
		painter->drawRect(_item->boundingRect());
	}
	painter->setPen(Qt::black);
	painter->setBrush(Qt::white);
	painter->drawEllipse(_item->boundingRect());
	painter->setBrush(Qt::black);
	painter->drawText(_item->boundingRect(), Qt::AlignCenter, _text);
}
