#include "GraphicsItem.h"
#include <QPainter>

const string STRING_EMPTY = "";
const int OFFSET = 30;

GraphicsItem::GraphicsItem(PresentationModel* presentationModel)
{
	_presentationModel = presentationModel;
	_item = new QGraphicsPolygonItem();
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

	painter->setPen(Qt::black);
	painter->setBrush(Qt::white);
	painter->drawPath(_item->shape());
	painter->setBrush(Qt::black);
	painter->drawText(_item->boundingRect(), Qt::AlignCenter, data(textData).toString());
	if (_isSelected)
	{
		painter->setPen(Qt::green);
		painter->setBrush(Qt::transparent);
		painter->drawRect(_item->boundingRect());
	}
}

// �ϧΤj�p�վ�
void GraphicsItem::doAdjustSize(QFontMetrics fontMetrics)
{
	((QGraphicsRectItem*)_item)->setRect(_item->pos().rx(), _item->pos().ry(), fontMetrics.width(data(textData).toString()) + OFFSET, fontMetrics.height() + OFFSET);
}

// �]�w�I�窱�A����
QVariant GraphicsItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
	if (change == QGraphicsItem::ItemSelectedChange)
	{
		if (value == true)
		{
			if (!_isSelected)
			//{
			//	_isSelected = false;
			//	
			//}
			//else
			{
				_isSelected = true;
				//_presentationModel->setDeleteEnabled(true);
				_presentationModel->setNodeSelected(data(idData).toInt(), true);
				_presentationModel->notifyButtonEnabled();
			}
		}
		else
		{
			_isSelected = false;
			//_presentationModel->setDeleteEnabled(false);
			_presentationModel->setNodeSelected(data(idData).toInt(), false);
			_presentationModel->notifyButtonEnabled();
		}
	}
	return QGraphicsItem::itemChange(change, value);
}
