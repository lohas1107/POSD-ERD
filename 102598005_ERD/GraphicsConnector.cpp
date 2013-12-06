#include "GraphicsConnector.h"

GraphicsConnector::GraphicsConnector(PresentationModel* presentationModel) : GraphicsItem(presentationModel)
{
	QGraphicsItem* toDelete = _item;
	delete toDelete;
	_item = new QGraphicsLineItem();
	setFlag(QGraphicsItem::ItemIsMovable, false);
}

GraphicsConnector::~GraphicsConnector()
{
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
