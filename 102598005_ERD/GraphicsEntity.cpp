#include "GraphicsEntity.h"
#include <QPainter>

GraphicsEntity::GraphicsEntity()
{
	doCreateItem();
}

GraphicsEntity::~GraphicsEntity()
{
}

void GraphicsEntity::doCreateItem()
{
	_item = new QGraphicsRectItem();
}
