#include "GraphicsAttribute.h"
#include <QGraphicsEllipseItem>
#include "..\src\gui\styles\qstyle.h"

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
	_item = new QGraphicsEllipseItem();
}

// �]�w primary key
void GraphicsAttribute::setPrimaryKey(bool flag)
{
	_isPrimaryKey = flag;
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
	_item->paint(painter, option, widget);
}
