#include "GraphicsConnector.h"

GraphicsConnector::GraphicsConnector()
{
	doCreateItem();
}

GraphicsConnector::~GraphicsConnector()
{
}

// ���ͽu�q
void GraphicsConnector::doCreateItem()
{
	_item = new QGraphicsLineItem();
}

// �мg�վ�j�p
void GraphicsConnector::doAdjustSize(QFontMetrics fontMetrics)
{
}

// �]�w�u�q�_�I���I
void GraphicsConnector::setLine(QLineF line)
{
	((QGraphicsLineItem*)_item)->setLine(line);
}
