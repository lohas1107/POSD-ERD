#include "GraphicsConnector.h"

GraphicsConnector::GraphicsConnector()
{
	QGraphicsItem* toDelete = _item;
	delete toDelete;
	_item = new QGraphicsLineItem();
	//doCreateItem();
	setFlag(QGraphicsItem::ItemIsMovable, false);
}

GraphicsConnector::~GraphicsConnector()
{
}

// ���ͽu�q
//void GraphicsConnector::doCreateItem()
//{
//
//}

// �мg�վ�j�p
void GraphicsConnector::doAdjustSize(QFontMetrics fontMetrics)
{
}

// �]�w�u�q�_�I���I
void GraphicsConnector::setLine(QLineF line)
{
	((QGraphicsLineItem*)_item)->setLine(line);
}
