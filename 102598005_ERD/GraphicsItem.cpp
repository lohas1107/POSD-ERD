#include "GraphicsItem.h"
#include <QPainter>

const string STRING_EMPTY = "";
const int OFFSET = 30;

GraphicsItem::GraphicsItem()
{
	_text = QString::fromStdString(STRING_EMPTY);
	_isSelected = false;
	setFlag(QGraphicsItem::ItemIsMovable, true);
	setFlag(QGraphicsItem::ItemIsSelectable, true);
	setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
}

GraphicsItem::~GraphicsItem()
{
}


// �^�ǹϧ����
QRectF GraphicsItem::boundingRect() const
{
	return _item->boundingRect();
}

// �^�ǧΪ�
QPainterPath GraphicsItem::shape() const
{
	return _item->shape();
}

// �e�ϩM�r
void GraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QFontMetrics fontMetrics(painter->font());
	doAdjustSize(fontMetrics);
	painter->drawText(_item->boundingRect(), Qt::AlignCenter, _text);
	_item->paint(painter, option, widget);
}

// �ϧΤj�p�վ�
void GraphicsItem::doAdjustSize(QFontMetrics fontMetrics)
{
	((QGraphicsRectItem*)_item)->setRect(_item->pos().rx(), _item->pos().ry(), fontMetrics.width(_text) + OFFSET, fontMetrics.height() + OFFSET);
}

// �]�w��r
void GraphicsItem::setText(string text)
{
	_text = QString::fromStdString(text);
}

// �]�w�I�窱�A����
QVariant GraphicsItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if (change == QGraphicsItem::ItemSelectedChange)
	{
		if (value == true)
		{
			if (_isSelected)
			{
				_isSelected = false;
			}
			else
			{
				_isSelected = true;
			}
		}
		else
		{
			_isSelected = false;
		}
	}

	return QGraphicsItem::itemChange(change, value);
}
