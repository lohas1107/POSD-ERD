#include "GraphicsEntity.h"
#include <QPainter>

const int OFFSET = 30;

GraphicsEntity::GraphicsEntity()
{
}

GraphicsEntity::~GraphicsEntity()
{
}

// 根據文字內容調整大小
void GraphicsEntity::doAdjustSize(QFontMetrics fontMetrics)
{
	int width = fontMetrics.width(data(textData).toString()) + OFFSET;
	int height = fontMetrics.height() + OFFSET;

	QPolygonF _polygon;
	_polygon << QPointF(-width/2, height/2) << QPointF(width/2, height/2) << QPointF(width/2, -height/2) << QPointF(-width/2, -height/2) << QPointF(-width/2, height/2);
	((QGraphicsPolygonItem*)_item)->setPolygon(_polygon);
}
