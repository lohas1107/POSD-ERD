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

// 產生線段
//void GraphicsConnector::doCreateItem()
//{
//
//}

// 覆寫調整大小
void GraphicsConnector::doAdjustSize(QFontMetrics fontMetrics)
{
}

// 設定線段起點終點
void GraphicsConnector::setLine(QLineF line)
{
	((QGraphicsLineItem*)_item)->setLine(line);
}
