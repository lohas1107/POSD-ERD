#include "GraphicsEntity.h"
#include <QPainter>

const int OFFSET = 30;

GraphicsEntity::GraphicsEntity()
{
}

GraphicsEntity::~GraphicsEntity()
{
}

// �ھڤ�r���e�վ�j�p
void GraphicsEntity::doAdjustSize(QFontMetrics fontMetrics)
{
	int width = fontMetrics.width(data(textData).toString()) + OFFSET;
	int height = fontMetrics.height() + OFFSET;

	QPolygonF _polygon;
	_polygon << QPointF(-width/2, height/2) << QPointF(width/2, height/2) << QPointF(width/2, -height/2) << QPointF(-width/2, -height/2) << QPointF(-width/2, height/2);
	((QGraphicsPolygonItem*)_item)->setPolygon(_polygon);
}
