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

// 產生橢圓形
void GraphicsAttribute::doCreateItem()
{
	_item = new QGraphicsEllipseItem();
}

// 設定 primary key
void GraphicsAttribute::setPrimaryKey(bool flag)
{
	_isPrimaryKey = flag;
}
